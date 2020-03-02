#ifndef RTC_H
#define RTC_H

/** @defgroup RTC RTC
 * @{
 * Real Time Clock functions
 */

#include <i8254.h>
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include <lcom/timer.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Converts value from bcd to binary
 *
 * @return Value in binary
 */
unsigned int BCD2Binary(unsigned int *bcd);

/**
 * @brief Gets current Day, Month and Year from RTC
 *
 * @return 0 if sucess
 */
int getDate(unsigned int *day, unsigned int *month, unsigned int *year);

/**
 * @brief Gets current Hours, Minutes and Seconds from RTC
 *
 * @return 0 if sucess
 */
int getTime(unsigned int *hours, unsigned int *minutes, unsigned int *seconds);

#endif /* RTC_H */
