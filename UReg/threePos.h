#ifndef _THREEPOS_H
#define _THREEPOS_H
#include <stdio.h>
#include <stm32f30x.h>

#include "misc.h"
#include "globals.h"
//Сброс выхода регулятора в 0
void resetThreePos();
//Обновить текущий счетчик времени для регулятора
void setThreePosCurrentTime();
//Рассчитать выход регулятора
void calculateThreePosOut();

#endif
