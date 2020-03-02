#include <rtc.h>

unsigned int BCD2Binary(unsigned int *bcd)
{
    return (((*bcd) & 0xF0) >> 4) * 10 + ((*bcd) & 0x0F);
}

int getDate(unsigned int *day, unsigned int *month, unsigned int *year)
{
    if (sys_outb(RTC_ADDR_REG, RTC_DAYMONTH) == OK &&
        sys_inb(RTC_DATA_REG, day) == OK &&
        sys_outb(RTC_ADDR_REG, RTC_MONTH) == OK &&
        sys_inb(RTC_DATA_REG, month) == OK &&
        sys_outb(RTC_ADDR_REG, RTC_YEAR) == OK &&
        sys_inb(RTC_DATA_REG, year) == OK)
    {
        (*day) = BCD2Binary(day);
        (*month) = BCD2Binary(month);
        (*year) = BCD2Binary(year);
        return 0;
    }
    return 1;
}

int getTime(unsigned int *hours, unsigned int *minutes, unsigned int *seconds)
{
    if (sys_outb(RTC_ADDR_REG, RTC_HRS) == OK &&
        sys_inb(RTC_DATA_REG, hours) == OK &&
        sys_outb(RTC_ADDR_REG, RTC_MIN) == OK &&
        sys_inb(RTC_DATA_REG, minutes) == OK &&
        sys_outb(RTC_ADDR_REG, RTC_SEC) == OK &&
        sys_inb(RTC_DATA_REG, seconds) == OK)
    {
        (*hours) = BCD2Binary(hours);
        (*minutes) = BCD2Binary(minutes);
        (*seconds) = BCD2Binary(seconds);
        return 0;
    }
    return 1;
}
