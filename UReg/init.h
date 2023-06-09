#ifndef _INIT_H
#define _INIT_H

#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>
#include <stm32f30x_misc.h>

void GPIOinit();
void NVICinit();
void TIMinit();

#endif
