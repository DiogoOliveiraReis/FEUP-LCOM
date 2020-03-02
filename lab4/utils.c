#include <lcom/lcf.h>
#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb)
{
  *lsb = val & 255;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb)
{
  *msb = val >> 8;
  return 0;
}

int(util_sys_inb)(int port, uint8_t *value)
{
  uint32_t value2;
  if (sys_inb(port, &value2) == OK)
  {
    *value = value2 & 255;
    return 0;
  }
  return 1;
}
