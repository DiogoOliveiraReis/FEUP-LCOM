// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include <stdint.h>
#include <stdio.h>
#include <vbe.h>
#include <keyboard.h>
#include <lcom/timer.h>
#include <i8254.h>

unsigned int counter_global = 0;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay)
{
  /* Initialize Graphics Mode */
  vg_init(mode);

  /* Waits delay */
  sleep(delay);

  /* Exit Graphics Mode */
  vg_exit();

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color)
{
  int ipc_status;
  message msg;
  uint32_t irq_set = BIT(1);
  uint32_t r;

  /* Initialize Graphics Mode */
  vg_init(mode);

  /* Draw Rectangle */
  if (vg_draw_rectangle(x, y, width, height, color) != 0)
  {
    scancode = ESC_KEY;
  }

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

  /* Exit Graphics Mode */
  vg_exit();

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step)
{
  int ipc_status;
  message msg;
  uint32_t irq_set = BIT(1);
  uint32_t r;

  /* Initialize Graphics Mode */
  vg_init(mode);

  /* Draw Pattern */
  if (vg_draw_pattern(no_rectangles, first, step) != 0)
  {
    scancode = ESC_KEY;
  }

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

  /* Exit Graphics Mode */
  vg_exit();

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y)
{
  int ipc_status;
  message msg;
  uint32_t irq_set = BIT(1);
  uint32_t r;

  /* Initialize Graphics Mode On Mode 0x105 */
  vg_init(0x105);

  /* Draw Pixmap */
  if (vg_draw_pixmap(xpm, x, y) != 0)
  {
    scancode = ESC_KEY;
  }

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

  /* Exit Graphics Mode */
  vg_exit();

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate)
{
  int ipc_status, firstX, firstY;
  message msg;
  uint32_t irq_set_timer = BIT(0);
  uint32_t irq_set_keyboard = BIT(1);
  uint32_t r;
  uint32_t counter = 0;

  if (speed < 0)
    speed = fr_rate;

  firstX = xi;
  firstY = yi;

  /* Initialize Graphics Mode On Mode 0x105 */
  vg_init(0x105);

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
        if (msg.m_notify.interrupts & irq_set_timer)
        { /* subscribed timer interrupt */
          /* process it */
          counter++;
          if (counter % (60 / fr_rate) == 0)
          {
            if (counter != 0) // Draws first frame in correct position, doesnt increment beforehand
            {
              if (xi != xf || yi != yf) // Avoids flashing in last position
                vg_erase_pixmap(xpm, xi, yi);
              if (firstX < xf && xi < xf) // Moves in x-axis, to the right
              {
                if (speed < 0 && counter % speed == 0)
                  xi++; // When speed<0, increment is diferent
                else
                {
                  if (xi + speed > xf) // Avoids overshooting
                  {
                    xi += xf - xi;
                  }
                  else
                  {
                    xi += speed;
                  }
                }
              }
              if (firstX > xf && xi > xf)
              {
                if (speed < 0 && counter % speed == 0)
                  xi--;

                else
                {
                  if (xi - speed < xf)
                  {
                    xi -= xi - xf;
                  }
                  else
                  {
                    xi -= speed;
                  }
                }
              }
              if (firstY < yf && yi < yf)
              {
                if (speed < 0 && counter % speed == 0)
                  yi++;

                else
                {
                  if (yi + speed > yf)
                  {
                    yi += yf - yi;
                  }
                  else
                  {
                    yi += speed;
                  }
                }
              }
              if (firstY > yf && yi > yf)
              {
                if (speed < 0 && counter % speed == 0)
                  yi--;

                else
                {
                  if (yi - speed < yf)
                  {
                    yi -= yi - yf;
                  }
                  else
                  {
                    yi -= speed;
                  }
                }
              }
            }
            if (vg_draw_pixmap(xpm, xi, yi) != 0)
            {
              scancode = ESC_KEY;
            }
          }
        }
        if (msg.m_notify.interrupts & irq_set_keyboard)
        { /* subscribed keyboard interrupt */
          /* process it */
          counter = 0;
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
  if (keyboard_unsubscribe_int(&bit_no_keyboard) == 1)
    return 1;
  /* */

  /* Timer Unsubscribe */
  if (timer_unsubscribe_int() == 1)
    return 1;
  /* */

  /* Exit Graphics Mode */
  vg_exit();

  return 0;
}

int test_controller()
{
  /* Set VBE graphics mode */
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86)); // Zero the structure
  reg86.ax = 0x4F02;                // VBE call, function 02: set VBE mode
  reg86.bx = 1 << 14 | 0x0;         // Set bit 14: linear framebuffer
  reg86.intno = 0x0;
  if (sys_int86(&reg86) != OK)
  {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }
  /* */

  vg_vbe_contr_info_t contr_info;

  if (vg_display_vbe_contr_info(&contr_info) == 0)
    return 0;

  return 1;
}
