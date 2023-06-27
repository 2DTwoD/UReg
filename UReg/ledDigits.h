#ifndef _LED_DIGITS_H
#define _LED_DIGITS_H
#include <stdio.h>
//Получить код для семисегментного индикатора (Для регистра ODR) в зависимости от строки str
void getLEDcodeArray(uint8_t* digits, char* str);

#endif
