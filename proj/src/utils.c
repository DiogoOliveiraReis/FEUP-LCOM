/** @defgroup VBE VBE
 * @{
 * Lab2 utilities
 */

#include <lcom/lcf.h>
#include <stdint.h>

/**
 * @brief Grabs LSB
 *
 * @return 0 if sucess
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb)
{
  *lsb = val & 255;
  return 0;
}

/**
 * @brief Grabs MSB
 *
 * @return 0 if sucess
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb)
{
  *msb = val >> 8;
  return 0;
}

/**
 * @brief Modified sys_inb
 *
 * @return 0 if sucess
 */
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
