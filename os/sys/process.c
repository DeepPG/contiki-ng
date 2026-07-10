/*
 * Copyright (c) 2005, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \addtogroup process
 * @{
 */

/**
 * \file
 *         Implementation of the Contiki process kernel.
 * \author
 *         Adam Dunkels <adam@sics.se>
 *
 */

#include <stdio.h>

#include "contiki.h"
#include "sys/process.h"
#include "pico.h"
  #include "pico/stdlib.h"


#include "sys/log.h"
#define LOG_MODULE "Processing"
#define LOG_LEVEL LOG_LEVEL_INFO


/*
 * The process_num_events_t type is an uint8_t. It must be able to store
 * the value of PROCESS_CONF_NUMEVENTS + 1, for the additional
 * boolean value indicating whether a poll has been requested.
 */
static_assert(PROCESS_CONF_NUMEVENTS > 0 && PROCESS_CONF_NUMEVENTS <= 128,
  "PROCESS_CONF_NUMEVENTS must be a positive value of at most 128.");

/* Require that PROCESS_CONF_NUMEVENTS is a power of 2 to allow
   optimization of modulo operations. */
static_assert(!(PROCESS_CONF_NUMEVENTS & (PROCESS_CONF_NUMEVENTS - 1)),
  "PROCESS_CONF_NUMEVENTS must be a power of 2.");

/*
 * A configurable function called after a process poll been requested.
 */
#ifdef PROCESS_CONF_POLL_REQUESTED
#define PROCESS_POLL_REQUESTED PROCESS_CONF_POLL_REQUESTED
void PROCESS_POLL_REQUESTED(void);
#else
#define PROCESS_POLL_REQUESTED()
#endif

/*
 * Pointer to the currently running process structure.
 */
struct process *process_list[2];
struct process *process_current[2];

static process_event_t lastevent[2];

// #define process_list[core_id] (process_list[core_id]_[get_core_num()])
// #define process_current (process_current_[get_core_num()])

// #define lastevent (lastevent_[get_core_num])




/*
 * Structure used for keeping the queue of active events.
 */
struct event_data {
  process_data_t data;
  struct process *p;
  process_event_t ev;
};

static process_num_events_t nevents[2], fevent[2];
static struct event_data events[2][PROCESS_CONF_NUMEVENTS];

#if PROCESS_CONF_STATS
process_num_events_t process_maxevents;
#endif

static volatile bool poll_requested[2];

#define PROCESS_STATE_NONE        0
#define PROCESS_STATE_RUNNING     1
#define PROCESS_STATE_CALLED      2


static void call_process(struct process *p, process_event_t ev, process_data_t data);
/*---------------------------------------------------------------------------*/
process_event_t
process_alloc_event(void)
{
  if(lastevent[core_id] == (process_event_t)~0U) {
    LOG_WARN("Cannot allocate another event number\n");
    return PROCESS_EVENT_NONE;
  }
  return lastevent[core_id]++;
}
/*---------------------------------------------------------------------------*/
void
process_start(struct process *p, process_data_t data)
{

  struct process *q;
  int core_id = get_core_num();

  p->core = core_id;
  

  /* First make sure that we don't try to start a process that is
     already running. */
  for(q = process_list[core_id]; q != p && q != NULL; q = q->next);

  /* If we found the process on the process list, we bail out. */
  if(q == p) {
    return;
  }
  /* Put on the procs list.*/
  p->next = process_list[core_id];
  process_list[core_id] = p;
  p->state = PROCESS_STATE_RUNNING;
  PT_INIT(&p->pt);

  LOG_DBG("starting '%s'\n", PROCESS_NAME_STRING(p));

  /* Post a synchronous initialization event to the process. */
  process_post_synch(p, PROCESS_EVENT_INIT, data);
}
/*---------------------------------------------------------------------------*/
static void
exit_process(struct process *p, const struct process *fromprocess)
{
  register struct process *q;
  uint8_t core_id = get_core_num();

  struct process *old_current = process_current[core_id];

  LOG_DBG("exit_process '%s'\n", PROCESS_NAME_STRING(p));

  /* Make sure the process is in the process list before we try to
     exit it. */
  for(q = process_list[core_id]; q != p && q != NULL; q = q->next);
  if(q == NULL) {
    return;
  }

  if(process_is_running(p)) {
    /* Process was running */

    if(p->thread != NULL && p != fromprocess) {
      /* Post the exit event to the process that is about to exit. */
      process_current[core_id] = p;
      p->thread(&p->pt, PROCESS_EVENT_EXIT, NULL);
    }
  }

  if(p == process_list[core_id]) {
    process_list[core_id] = process_list[core_id]->next;
  } else {
    for(q = process_list[core_id]; q != NULL; q = q->next) {
      if(q->next == p) {
        q->next = p->next;
        break;
      }
    }
  }

  if(process_is_running(p)) {
    /* Process was running */
    p->state = PROCESS_STATE_NONE;

    /*
     * Post a synchronous event to all processes to inform them that
     * this process is about to exit. This will allow services to
     * deallocate state associated with this process.
     */
    for(q = process_list[core_id]; q != NULL; q = q->next) {
        call_process(q, PROCESS_EVENT_EXITED, (process_data_t)p);
    }
  }

  process_current[core_id] = old_current;
}
/*---------------------------------------------------------------------------*/
static void
call_process(struct process *p, process_event_t ev, process_data_t data)
{
  uint8_t core_id = get_core_num();




  if(p->state == PROCESS_STATE_CALLED) {
    LOG_DBG("process '%s' called again with event %d\n",
            PROCESS_NAME_STRING(p), ev);
  }

  if((p->state & PROCESS_STATE_RUNNING) &&
     p->thread != NULL) {
    LOG_DBG("calling process '%s' with event %d\n",
            PROCESS_NAME_STRING(p), ev);
    process_current[core_id] = p;
    p->state = PROCESS_STATE_CALLED;
    int ret = p->thread(&p->pt, ev, data);
    if(ret == PT_EXITED || ret == PT_ENDED || ev == PROCESS_EVENT_EXIT) {
      exit_process(p, p);
    } else {
      p->state = PROCESS_STATE_RUNNING;
    }
  }
}
/*---------------------------------------------------------------------------*/
void
process_exit(struct process *p)
{
  exit_process(p, PROCESS_CURRENT());
}
/*---------------------------------------------------------------------------*/
void
process_init(void)
{
  uint8_t core_id = get_core_num();
  lastevent[core_id] = PROCESS_EVENT_MAX;
}
/*---------------------------------------------------------------------------*/
/*
 * Call each process' poll handler.
 */
/*---------------------------------------------------------------------------*/
static void
do_poll(void)
{
  uint8_t core_id = get_core_num();

  poll_requested[core_id] = false;
  /* Call the processes that needs to be polled. */
  for(struct process *p = process_list[core_id]; p != NULL; p = p->next) {
    if(p->needspoll) {
      p->state = PROCESS_STATE_RUNNING;
      p->needspoll = false;
      call_process(p, PROCESS_EVENT_POLL, NULL);
    }
  }
}
/*---------------------------------------------------------------------------*/
/*
 * Process the next event in the event queue and deliver it to
 * listening processes.
 */
/*---------------------------------------------------------------------------*/
static void
do_event(void)
{
  /*q
   * If there are any events in the queue, take the first one and walk
   * through the list of processes to see if the event should be
   * delivered to any of them. If so, we call the event handler
   * function for the process. We only process one event at a time and
   * call the poll handlers inbetween.
   */
  uint8_t core_id = get_core_num();

  if(nevents[core_id] > 0) {

    /* There are events that we should deliver. */
    process_event_t ev = events[core_id][fevent[core_id]].ev;
    process_data_t data = events[core_id][fevent[core_id]].data;
    struct process *receiver = events[core_id][fevent[core_id]].p;

    /* Since we have seen the new event, we move pointer upwards
       and decrease the number of events. */
    fevent[core_id] = (fevent[core_id] + 1) % PROCESS_CONF_NUMEVENTS;
    --nevents[core_id];

    /* If this is a broadcast event, we deliver it to all events, in
       order of their priority. */
    if(receiver == PROCESS_BROADCAST) {
      for(struct process *p = process_list[core_id]; p != NULL; p = p->next) {
        /* If we have been requested to poll a process, we do this in
           between processing the broadcast event. */
        if(poll_requested[core_id]) {
          do_poll();
        }
        call_process(p, ev, data);
      }
    } else {
      /* This is not a broadcast event, so we deliver it to the
         specified process. */
      /* If the event was an INIT event, we should also update the
         state of the process. */
      if(ev == PROCESS_EVENT_INIT) {
        receiver->state = PROCESS_STATE_RUNNING;
      }

      /* Make sure that the process actually is running. */
      call_process(receiver, ev, data);
    }
  }
}
/*---------------------------------------------------------------------------*/
process_num_events_t
process_run(void)
{

  uint8_t core_id = get_core_num();
  
  /* Process poll events. */
  if(poll_requested[core_id]) {
    do_poll();
  }


  /* Process one event from the queue */
  do_event();


  return nevents[core_id] + poll_requested[core_id];
}
/*---------------------------------------------------------------------------*/
process_num_events_t
process_nevents(void)
{
  return nevents[core_id] + poll_requested[core_id];
}
/*---------------------------------------------------------------------------*/
int
process_post(struct process *p, process_event_t ev, process_data_t data)
{
  uint8_t core_id = p->core;


  if(nevents[core_id] == PROCESS_CONF_NUMEVENTS) {
    LOG_WARN("Cannot post event %d to %s from %s because the queue is full\n",
             ev,
             p == PROCESS_BROADCAST ? "<broadcast>" : PROCESS_NAME_STRING(p),
             PROCESS_NAME_STRING(process_current[core_id]));
    return PROCESS_ERR_FULL;
  }

  LOG_DBG("Process '%s' posts event %d to process '%s', nevents %d\n",
          PROCESS_NAME_STRING(PROCESS_CURRENT()),
          ev, p == PROCESS_BROADCAST ? "<broadcast>" : PROCESS_NAME_STRING(p),
          nevents[core_id]);

  process_num_events_t snum =
    (process_num_events_t)(fevent[core_id] + nevents[core_id]) % PROCESS_CONF_NUMEVENTS;
  events[core_id][snum].ev = ev;
  events[core_id][snum].data = data;
  events[core_id][snum].p = p;
  ++nevents[core_id];

#if PROCESS_CONF_STATS
  if(nevents[core_id] > process_maxevents) {
    process_maxevents = nevents[core_id];
  }
#endif /* PROCESS_CONF_STATS */

  return PROCESS_ERR_OK;
}
/*---------------------------------------------------------------------------*/
void
process_post_synch(struct process *p, process_event_t ev, process_data_t data)
{
  uint8_t core_id = get_core_num();

  struct process *caller = process_current[core_id];

  call_process(p, ev, data);
  process_current[core_id] = caller;
}
/*---------------------------------------------------------------------------*/
void
process_poll(struct process *p)
{
  uint8_t core_id = get_core_num();

  if(p != NULL &&
     (p->state == PROCESS_STATE_RUNNING || p->state == PROCESS_STATE_CALLED)) {
    p->needspoll = true;
    poll_requested[core_id] = true;
    PROCESS_POLL_REQUESTED();
  }
}
/*---------------------------------------------------------------------------*/
bool
process_is_running(struct process *p)
{
  return p->state != PROCESS_STATE_NONE;
}
/*---------------------------------------------------------------------------*/
/** @} */
