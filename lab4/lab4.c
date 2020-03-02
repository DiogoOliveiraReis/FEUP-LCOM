// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab4.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <mouse.h>
#include <i8254.h>
#include <lcom/timer.h>

// Any header files included below this line should have been created by you
struct packet mouse_packet;
int bytes_count = 0;
extern unsigned int counter_global;

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(mouse_test_packet)(uint32_t cnt)
{
  int ipc_status;
  message msg;
  uint32_t irq_set = BIT(12);
  uint32_t r;
  unsigned int packet_count = 0;

  /* Mouse Subscribe With Bit_No = 12 */
  uint8_t bit_no = 12;
  if (mouse_subscribe_int(&bit_no) != 0)
    return 1;
  /* */

  mouse_enable_data_reporting();

  /* Device Driver Loop Start */
  while (packet_count < cnt)
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
          mouse_ih();
          bytes_count++;
          if (bytes_count == 3)
          {
            packet_count++;
            bytes_count = 0;
            mouse_print_packet(&mouse_packet);
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

  /* Mouse Unsubscribe */
  if (mouse_unsubscribe_int() == 1)
    return 1;
  /* */

  /* Re-Enable Mouse Interrupts */
  if (re_enable_mouse_interrupts() == 1)
    return 1;
  /* */

  return 0;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt)
{
  /*
  1. Desativar Interrupts
  2. Desativar Data Reporting
  3. Ativar Remote Mode
  4. Print Mouse Packets
  5. Re-Ativar Mouse Interrupts
  6. Reativar Data Reporting
  */
  printf("%s(%u, %u): under construction\n", __func__, period, cnt);
  return 1;
}

int(mouse_test_async)(uint8_t idle_time)
{
  int ipc_status;
  message msg;
  uint32_t irq_set_timer = BIT(0);
  uint32_t irq_set_mouse = BIT(12);
  uint32_t r;

  /* Timer Subscribe With Bit_No = 0 */
  uint8_t bit_no_timer = 0;
  if (timer_subscribe_int(&bit_no_timer) != 0)
    return 1;
  /* */

  /* Mouse Subscribe With Bit_No = 12 */
  uint8_t bit_no_mouse = 12;
  if (mouse_subscribe_int(&bit_no_mouse) != 0)
    return 1;
  /* */

  mouse_enable_data_reporting();

  /* Device Driver Loop Start */
  while (counter_global < idle_time * 60)
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
        }
        if (msg.m_notify.interrupts & irq_set_mouse)
        { /* subscribed Mouse interrupt */
          /* process it */
          mouse_ih();
          counter_global = 0;
          bytes_count++;
          if (bytes_count == 3)
          {
            bytes_count = 0;
            mouse_print_packet(&mouse_packet);
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

  /* Mouse Unsubscribe */
  if (mouse_unsubscribe_int(&bit_no_mouse) == 1)
    return 1;
  /* */

  /* Timer Unsubscribe */
  if (timer_unsubscribe_int() == 1)
    return 1;
  /* */

  /* Re-Enable Mouse Interrupts */
  if (re_enable_mouse_interrupts() == 1)
    return 1;
  /* */

  return 0;
}

int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance)
{
  int ipc_status;
  message msg;
  uint32_t irq_set = BIT(12);
  uint32_t r;

  /* Mouse Subscribe With Bit_No = 12 */
  uint8_t bit_no = 12;
  if (mouse_subscribe_int(&bit_no) != 0)
    return 1;
  /* */

  mouse_enable_data_reporting();

  /* Device Driver Loop Start */
  while (1)
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

  /* Mouse Unsubscribe */
  if (mouse_unsubscribe_int() == 1)
    return 1;
  /* */

  /* Re-Enable Mouse Interrupts */
  if (re_enable_mouse_interrupts() == 1)
    return 1;
  /* */

  return 0;
}
