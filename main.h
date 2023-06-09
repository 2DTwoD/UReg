#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>

#include "init.h"
#include "globals.h"
#include "menu.h"
#include "ledDigits.h"
#include "twoPos.h"
#include "threePos.h"
#include "pid.h"

//Режим (0 - 2-позиционный, 1 - 3-позиционный, 2 - ПИД)
uint16_t mode = 0;
//Автоматический режим (0 - выкл. 1 - вкл.)
int8_t AUTO = 0;
//Переменная процесса
double pv = 0.0;
//Уставка
double sp = 0.0;
//Выход регулятора
double out = 0.0;
//Разгон датчика
Scale scale = {0.0, 100.0};
//Пределы срабатывания
Limit limit = {95.0, 90.0, 10.0, 5.0};
//Параметры 2-позиционного регулятора
TwoPosSet twoPosSet = {0.0, 0.0, 0, 0};
//Параметры 3-позиционного регулятора
ThreePosSet threePosSet = {5.0, 1.0, 200, 200, 0, 1, {0, 0}, 0};
//Параметры ПИД регулятора
PIDset pidSet = {1.0, 10.0, 0.0, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0};

#endif
