#include <lcom/lcf.h>
#include <keyboard.h>
#include <stdint.h>
#include <i8254.h>
#include <lcom/timer.h>

int(keyboard_subscribe_int)(uint8_t *bit_no)
{
  bit_no_global_keyboard = *bit_no;
  if ((sys_irqsetpolicy(1, IRQ_REENABLE | IRQ_EXCLUSIVE, &bit_no_global_keyboard) == OK))
    return 0;
  return 1;
}

int(keyboard_unsubscribe_int)()
{
  if (sys_irqrmpolicy(&bit_no_global_keyboard) == OK)
    return 0;
  return 1;
}

void(kbc_ih)()
{
  if (sys_inb(KEYBOARD_STATUS_REG, &status) == OK)
    sys_inb(KEYBOARD_OUT_BUF, &scancode);
}

bool(keyboard_scan_code)()
{
  /* Returns true if it's a Makecode, false if Breakcode */
  if (scancode != 224)
  {
    bytes[0] = scancode;
    size = 1;
  }
  else
  {
    bytes[0] = scancode;
    size = 2;
  }
  makeorbreakcode = ((scancode >> 7) == 0);
  return !(scancode & 0);
}
