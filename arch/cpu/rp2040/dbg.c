#include "contiki.h"
#include "uart0.h"




#ifndef DBG_CONF_USB
#define DBG_CONF_USB 0
#endif

#if DBG_CONF_USB
#define write_byte(b) usb_serial_writeb(b)
#define flush()       usb_serial_flush()
#else
#define write_byte(b) uart0_writeb(b)
#define flush()
#endif


int
dbg_putchar(int c)
{
  write_byte(c);

  return c;
}
/*---------------------------------------------------------------------------*/
unsigned int
dbg_send_bytes(const unsigned char *s, unsigned int len)
{
  unsigned int i = 0;

  while(s && *s != 0) {
    if(i >= len) {
      break;
    }
    dbg_putchar(*s++);
    i++;
  }

  return i;
}
/*---------------------------------------------------------------------------*/
/**
 * @}
 */