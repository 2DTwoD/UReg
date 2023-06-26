#ifndef _MISC_H
#define _MISC_H

//Число значений для усреднения (1-256)
#define MAX_AVG_NUM 200

#include <stm32f30x.h>

#include "globals.h"
#include "twoPos.h"
#include "threePos.h"
#include "pid.h"

//Сброс всех регуляторов
void resetRegulators();
//Получить усредненное значение с АЦП
uint16_t getAvgRawPv();
//Функция обновления состояния таймера
void timerUpdater(onDelay* timer);
//Изменить состояние пинов выхода
void changeDO(GPIO_TypeDef* gpio, uint16_t mask, uint16_t value);

#endif
