#ifndef __MOUSE_H
#define __MOUSE_H

#include <i8254.h>

/** @defgroup Mouse Mouse
 * @{
 * Mouse functions
 */

extern struct packet mouse_packet;
uint32_t mouse_status;
extern int bytes_count;
int bit_no_global_mouse;
uint32_t packet_byte;

/**
 * @brief Subscribe mouse interrupts
 *
 * @return 0 if sucess
 */
int(mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribe mouse interrupts
 *
 * @return 0 if sucess
 */
int(mouse_unsubscribe_int)();

/**
 * @brief Gets mouse status
 *
 * @return 0 if sucess
 */
int(mouse_get_status)();

/**
 * @brief Checks mouse status
 *
 * @return 0 if sucess
 */
int(mouse_check_status)();

/**
 * @brief Mouse interrupt handler, parses information
 *
 * @return 0 if sucess
 */
void(mouse_ih)();

#endif /* __MOUSE_H */
