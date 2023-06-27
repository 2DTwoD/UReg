#ifndef _PID_H
#define _PID_H
#include <stdio.h>
#include <math.h>
#include "globals.h"

//Сброс выхода регулятора в 0
void resetPID();
//Обновление коэффициентов регулятора
void updatePID();
//Расчет выхода регулятора
void calculatePIDout();

#endif
