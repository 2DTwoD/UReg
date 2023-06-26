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

//Настройка пинов ввода/вывода
void GPIOinit();
//Настройка внешних прерываний(от кнопок)
void EXTIinit();
//Настройка приоритетов прерываний
void NVICinit();
//Настройка таймеров
void TIMinit();
//Настройка АЦП
void ADCinit();
//Настройка прямого доступа в память
void DMAinit();
//Настройка ШИМ
void PWMinit();

#endif
