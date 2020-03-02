#include <game.h>
#include <i8254.h>
#include <keyboard.h>
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include <lcom/timer.h>
#include <screens.h>
#include <sprite.h>
#include <stdbool.h>
#include <stdint.h>
#include <vbe.h>
#include <mouse.h>
#include <stdio.h>
#include <string.h>
#include <db.h>

struct packet mouse_packet;
int bytes_count = 0;

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char *argv[])
{
  /* Initialize Graphics Mode On Mode 0x105 */
  vg_init(0x105);

  xpm_map_t xpm_si = spaceInvaders;
  xpm_image_t img_si;
  uint8_t *sprite_si = vg_create_sprite(xpm_si, &img_si);
  vg_draw_sprite(sprite_si, img_si, 390, 50);

  xpm_map_t xpm_si2 = play;
  xpm_image_t img_si2;
  uint8_t *sprite_si2 = vg_create_sprite(xpm_si2, &img_si2);
  vg_draw_sprite(sprite_si2, img_si2, 392, 250);

  xpm_map_t xpm_si22 = lcom1920;
  xpm_image_t img_si22;
  uint8_t *sprite_si22 = vg_create_sprite(xpm_si22, &img_si22);
  vg_draw_sprite(sprite_si22, img_si22, 450, 700);

  int ipc_status;
  message msg;
  uint32_t irq_set_timer = BIT(0);
  uint32_t irq_set_keyboard = BIT(1);
  uint32_t irq_set_mouse = BIT(12);
  uint32_t r;

  /* Timer Subscribe With Bit_No = 0 */
  uint8_t bit_no_timer = 0;
  if (timer_subscribe_int(&bit_no_timer) != 0)
    return 1;
  /* */

  /* Keyboard Subscribe With Bit_No = 1 */
  uint8_t bit_no_keyboard = 1;
  if (keyboard_subscribe_int(&bit_no_keyboard) != 0)
    return 1;
  /* */

  /* Mouse Subscribe With Bit_No = 12 */
  uint8_t bit_no_mouse = 12;
  if (mouse_subscribe_int(&bit_no_mouse) != 0)
    return 1;
  /* */

  mouse_enable_data_reporting();

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
        { /* subscribed interrupt */
          /* process it */
          memcpy(video_mem, double_buffer, 1024 * 768);
        }
        if (msg.m_notify.interrupts & irq_set_keyboard)
        { /* subscribed interrupt */
          /* process it */
          kbc_ih();
          if (scancode == 0x19)
          {
            clearScreen();
            if (gameScreen(3, 1))
              gameOverScreen();
          }
        }
        if (msg.m_notify.interrupts & irq_set_mouse)
        { /* subscribed interrupt */
          /* process it */
          mouse_ih();
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

  /* Timer Unsubscribe */
  if (timer_unsubscribe_int() == 1)
    return 1;
  /* */

  /* Keyboard Unsubscribe */
  if (keyboard_unsubscribe_int() == 1)
    return 1;
  /* */

  /* Mouse Unsubscribe */
  if (mouse_unsubscribe_int() == 1)
    return 1;
  /* */

  vg_exit();
  printf("Successfully Exited Space Invaders\n");

  return 0;
}
