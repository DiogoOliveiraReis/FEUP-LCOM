#include <lcom/lab3.h>
#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include <keyboard.h>
#include <i8254.h>
#include <lcom/timer.h>

unsigned int counter_global = 0;

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)()
{
  int ipc_status;
  message msg;
  uint32_t irq_set = BIT(1);
  uint32_t r;

  /* Keyboard Subscribe With Bit_No = 1 */
  uint8_t bit_no = 1;
  if (keyboard_subscribe_int(&bit_no) != 0)
    return 1;
  /* */

  /* Device Driver Loop Start */
  while (scancode != ESC_KEY)
  { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { /* received notification */
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & irq_set)
        { /* subscribed interrupt */
          /* process it */
          kbc_ih();
          if (keyboard_scan_code())
            kbd_print_scancode(makeorbreakcode, size, bytes);
        }
        break;
      default:
        break; /* no other notifications expected: do nothing */
      }
    }
    else
    { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }
  /* Device Driver Loop End */

  /* Keyboard Unsubscribe */
  if (keyboard_unsubscribe_int() == 1)
    return 1;
  /* */

  return 0;
}

int(kbd_test_poll)()
{
  while (scancode != ESC_KEY)
  {
    kbc_ih();
    tickdelay(micros_to_ticks(20000));
    if (keyboard_scan_code())
    {
      if (makeorbreakcode == true)
        kbd_print_scancode(makeorbreakcode, size, bytes);
    }
  }

  /* Volta a permitir interrupts do teclado */
  /* Criar uma função genérica para isto (?) */
  sys_outb(0x64, 0x20);
  uint32_t commandByte;
  sys_inb(KEYBOARD_OUT_BUF, &commandByte);
  sys_outb(0x64, 0x60);
  commandByte = commandByte | BIT(0);
  sys_outb(KEYBOARD_OUT_BUF, commandByte);
  /* */

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n)
{
  int ipc_status;
  message msg;
  uint32_t irq_set_timer = BIT(0);
  uint32_t irq_set_keyboard = BIT(1);
  uint32_t r;
  uint32_t counter = 0;

  /* Keyboard Subscribe With Bit_No = 1 */
  uint8_t bit_no_keyboard = 1;
  if (keyboard_subscribe_int(&bit_no_keyboard) != 0)
    return 1;
  /* */

  /* Timer Subscribe With Bit_No = 0 */
  uint8_t bit_no_timer = 0;
  if (timer_subscribe_int(&bit_no_timer) != 0)
    return 1;
  /* */

  /* Device Driver Loop Start */
  while ((scancode != ESC_KEY) && (counter < n))
  { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { /* received notification */
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & irq_set_timer)
        { /* subscribed timer interrupt */
          /* process it */
          timer_int_handler();
          if (counter_global == 60)
          {
            counter++;
            counter_global = 0;
          }
        }
        if (msg.m_notify.interrupts & irq_set_keyboard)
        { /* subscribed keyboard interrupt */
          /* process it */
          kbc_ih();
          if (keyboard_scan_code())
          {
            counter_global = 0;
            counter = 0;
            kbd_print_scancode(makeorbreakcode, size, bytes);
          }
        }
        break;
      default:
        break; /* no other notifications expected: do nothing */
      }
    }
    else
    { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }
  /* Device Driver Loop End */

  /* Keyboard Unsubscribe */
  if (keyboard_unsubscribe_int(&bit_no_keyboard) == 1)
    return 1;
  /* */

  /* Timer Unsubscribe */
  if (timer_unsubscribe_int() == 1)
    return 1;
  /* */

  return 0;
}
