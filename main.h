#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>

#include "init.h"
#include "globals.h"
#include "misc.h"
#include "menu.h"
#include "ledDigits.h"
#include "twoPos.h"
#include "threePos.h"
#include "pid.h"
#include "flash.h"

//Режим регулятора (0 - двупозиционный, 1 - трехпозиционный, 2 - ПИД)
uint16_t mode = 0;
//Режим управления (0 - ручной, 1 - автоматический)
int8_t AUTO = 0;
//Режим параметризации (0 - выключен, 1 - включен)
int8_t prog = 0;
//Сигнал с датчика необработанный (0 - 4095)
uint16_t pvRaw = 0;
//Выходной сигнал для ШИМ (0 - 1000)
uint16_t outRaw = 0;
//Сигнал с датчика (переменная процесса)
double pv = 0.0;
//Уставка
double sp = 0.0;
//Пределы шкалирования
Scale scale = {100.0, 0.0};
//Пределы для отображения предупреждений
Limit limit = {95.0, 90.0, 10.0, 5.0};
//Параметры двупозиционного регулятора
TwoPosSet twoPosSet = {5.0, 5.0, 0, 0};
//Параметры трехпозиционного регулятора
ThreePosSet threePosSet = {5.0, 1.0, 200, 200, 1, {0, 0}};
//Параметры ПИД регулятора
PIDset pidSet = {1.0, 10.0, 0.0, 0.05, 0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0};
//Отслеживание изменений параметров в меню
uint8_t menuParChanged = 0;

#endif
