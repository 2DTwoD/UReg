#ifndef _INIT_H
#define _INIT_H

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>
#include <stm32f30x_misc.h>
#include <stm32f30x_exti.h>
#include <stm32f30x_syscfg.h>
#include <stm32f30x_adc.h>
#include <stm32f30x_dma.h>

void GPIOinit();
void EXTIinit();
void NVICinit();
void TIMinit();
void ADCinit();
void DMAinit();
void PWMinit();

#endif
