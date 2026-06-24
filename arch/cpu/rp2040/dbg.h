#ifndef DBG_H__
#define DBG_H__
#include "contiki.h"


// unsigned int dbg_send_bytes(const unsigned char *s, unsigned int len);
int dbg_putchar(int c);
unsigned int dbg_send_bytes(const unsigned char *s, unsigned int len);

#endif