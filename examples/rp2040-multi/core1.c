

#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"


#include "sys/log.h"

#define LOG_MODULE "CORE1"
#define LOG_LEVEL LOG_LEVEL_INFO 





static int scan_result(void *env, const cyw43_ev_scan_result_t *result) {
    if (result) {
        LOG_INFO("ssid: %-32s rssi: %4d chan: %3d mac: %02x:%02x:%02x:%02x:%02x:%02x sec: %u\n\r",
            result->ssid, result->rssi, result->channel,
            result->bssid[0], result->bssid[1], result->bssid[2], result->bssid[3], result->bssid[4], result->bssid[5],
            result->auth_mode);
    }
    return 0;
}


static void scan_worker_fn(async_context_t *context, async_at_time_worker_t *worker) {
    cyw43_wifi_scan_options_t scan_options = {0};
    int err = cyw43_wifi_scan(&cyw43_state, &scan_options, NULL, scan_result);
    if (err == 0) {
        bool *scan_started = (bool*)worker->user_data;
        *scan_started = true;
        LOG_INFO("Performing wifi scan\n\r");
    } else {
        LOG_INFO("Failed to start scan: %d\n", err);
    }
}










volatile void core1_entry(void){
   if (cyw43_arch_init()) {
        LOG_INFO("failed to initialise\n\r");

    }


    cyw43_arch_enable_sta_mode();



    bool scan_started = false;
    async_at_time_worker_t scan_worker = { .do_work = scan_worker_fn, .user_data = &scan_started };
    hard_assert(async_context_add_at_time_worker_in_ms(cyw43_arch_async_context(), &scan_worker, 0));

    bool exit = false;
    while(!exit) {
        if (!cyw43_wifi_scan_active(&cyw43_state) && scan_started) {
            // Start a scan in 10s
            scan_started = false;
            hard_assert(async_context_add_at_time_worker_in_ms(cyw43_arch_async_context(), &scan_worker, 10000));
        }

        cyw43_arch_poll();

        
        cyw43_arch_wait_for_work_until(at_the_end_of_time);
    }

}



