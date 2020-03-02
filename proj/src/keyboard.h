#ifndef __KEYBOARD_H
#define __KEYBOARD_H

/** @defgroup Keyboard Keyboard
 * @{
 * Keyboard functions done in lab3
 */

int bit_no_global_keyboard;
unsigned int counter_global;
uint32_t scancode;
uint32_t status;
uint8_t size;
uint8_t bytes[2];
bool makeorbreakcode;

/**
 * @brief Subscribes keyboard interrupts
 *
 * @return 0 if sucess
 */
int(keyboard_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes keyboard interrupts
 *
 * @return 0 if sucess
 */
int(keyboard_unsubscribe_int)();

/**
 * @brief Keyboard interrupt handler
 *
 * @return 0 if sucess
 */
void(kbc_ih)();

/**
 * @brief Keyboard code scanner
 *
 * @return True if it's a Makecode, false if Breakcode
 */
bool(keyboard_scan_code)();

#endif /* __KEYBOARD_H */
