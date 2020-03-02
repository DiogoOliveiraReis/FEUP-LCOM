#ifndef __MOUSE_H
#define __MOUSE_H

#include <i8254.h>

extern struct packet mouse_packet;
uint32_t mouse_status;
extern int bytes_count;
int bit_no_global_mouse;
uint32_t packet_byte;

int(mouse_subscribe_int)(uint8_t *bit_no);
int(mouse_unsubscribe_int)();
int(mouse_get_status)();
int(mouse_check_status)();
void(parse)();
void(mouse_ih)();
int (re_enable_mouse_interrupts)();

#endif /* __MOUSE_H */
