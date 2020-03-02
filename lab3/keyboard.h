#ifndef __KEYBOARD_H
#define __KEYBOARD_H

int bit_no_global_keyboard;
unsigned int counter_global;
uint32_t scancode;
uint32_t status;
uint8_t size;
uint8_t bytes[2];
bool makeorbreakcode;

int(keyboard_subscribe_int)(uint8_t *bit_no);
int(keyboard_unsubscribe_int)();
void(kbc_ih)();
bool(keyboard_scan_code)();

#endif /* __KEYBOARD_H */
