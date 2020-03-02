#include "i8254.h"
#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

int bit_no_global_timer;
unsigned int counter_global;

int(timer_set_frequency)(uint8_t timer, uint32_t freq)
{
  if (timer > 2 || freq == 0 || (TIMER_FREQ / freq) >= 0xFFFF)
  {
    return 1;
  }
  /* Ler a status do timer usando o readBackCommand e alterar os bits 4 a 7 */
  uint8_t controlWord;
  uint8_t tmr = TIMER_0 + timer;
  if (timer_get_conf(timer, &controlWord) == 0)
  {
    controlWord = controlWord & 15;
    switch (timer)
    {
    case 0:
      controlWord = TIMER_SEL0 | TIMER_LSB_MSB | controlWord;
      break;
    case 1:
      controlWord = TIMER_SEL1 | TIMER_LSB_MSB | controlWord;
      break;
    case 2:
      controlWord = TIMER_SEL2 | TIMER_LSB_MSB | controlWord;
      break;
    }
    sys_outb(TIMER_CTRL, controlWord);
  }
  /* Carregar o valor do counter, primeiro os 8 lsb e depois os restantes 8 msb */
  uint8_t lsb;
  if (util_get_LSB((TIMER_FREQ / freq), &lsb) == 0)
    sys_outb(tmr, lsb);
  uint8_t msb;
  if (util_get_MSB((TIMER_FREQ / freq), &msb) == 0)
    sys_outb(tmr, msb);
  return 0;
}

int(timer_subscribe_int)(uint8_t *bit_no)
{
  bit_no_global_timer = *bit_no;
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &bit_no_global_timer) == OK)
    return 0;
  return 1;
}

int(timer_unsubscribe_int)()
{
  if (sys_irqrmpolicy(&bit_no_global_timer) == OK)
    return 0;
  return 1;
}

void(timer_int_handler)()
{
  counter_global++;
}

int(timer_get_conf)(uint8_t timer, uint8_t *st)
{
  if (timer > 2)
    return 1;
  /* Escrever o readBackCommand para o registo TIMER_CTRL */
  uint8_t readBackCommand =
      TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  uint8_t tmr = TIMER_0 + timer;
  if (sys_outb(TIMER_CTRL, readBackCommand) == OK)
  {
    /* Obter a configuraÃ§Ã£o do timer que queremos */
    if (util_sys_inb(tmr, st) == OK)
    {
      return 0;
    }
  }
  return 1;
}

int(timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field)
{
  if (timer > 2)
    return 1;
  union timer_status_field_val config;
  if (field == tsf_all)
  {
    config.byte = st;
  }
  if (field == tsf_initial)
  {
    config.in_mode = (st & (BIT(4) | BIT(5))) >> 4;
  }
  if (field == tsf_mode)
  {
    config.count_mode = (st & (BIT(1) | BIT(2) | (BIT(3)))) >> 1;
    /* Para haver compatibilidade com futuros produtos Intel */
    switch ((st & (BIT(1) | BIT(2) | (BIT(3)))) >> 1)
    {
    case 6:
      config.count_mode = 2;
      break;
    case 7:
      config.count_mode = 3;
      break;
    }
  }
  if (field == tsf_base)
  {
    config.bcd = (st & BIT(0)) >> 0;
  }
  if (timer_print_config(timer, field, config))
    return 0;
  return 1;
}
