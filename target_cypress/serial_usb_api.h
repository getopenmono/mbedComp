// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt

#ifndef serial_usb_api_h
#define serial_usb_api_h

#ifdef __cplusplus
extern "C" {
#endif

#include <serial_api.h>
#include <us_ticker_api.h>
#include <objects.h>

static char serial_usbuart_is_powered;
static uint32_t serial_usbuart_first_enumeration_timeout_ms;
static uint32_t serial_usbuart_enumeration_delay_ms;

static struct serial_port_s serial_ports[2];

/**
 * try to enumerate (configure the USB endpoint on host)
 * this is an internal function
 * @return true (1) on enumeration
 */
char serial_usbuart_try_enumeration(struct serial_port_s *port);

/**
 * try to init / setup the usb port for CDC
 */
char serial_usbuart_init_cdc(serial_t *obj);


char serial_usbuart_is_started();

void serial_usbuart_stopped();

char serial_usbuart_dtr(serial_t *obj);

#ifdef __cplusplus
}
#endif

#endif /* serial_usb_api_h */