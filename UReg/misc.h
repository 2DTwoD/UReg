#ifndef _MISC_H
#define _MISC_H

//Число для усреднения сигнала с датчика (1-256)
#define MAX_AVG_NUM 200

#include <stm32f30x.h>

#include "globals.h"
#include "twoPos.h"
#include "threePos.h"
#include "pid.h"

//Сбросить все регйляторы
void resetRegulators();
//Получить усредненный сигнал с датчика
uint16_t getAvgRawPv();
//Функция для обновления таймеров задержки включения
void timerUpdater(onDelay* timer);
//Изменить состояние выходного пина
void changeDO(GPIO_TypeDef* gpio, uint16_t mask, uint16_t value);

#endif
