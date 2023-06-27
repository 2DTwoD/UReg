#ifndef _TWOPOS_H
#define _TWOPOS_H
#include <stdio.h>
#include <stm32f30x.h>

#include "misc.h"
#include "globals.h"

//Сброс выхода регулятора в 0
void resetTwoPos();
//Расчет выхода регулятора
void calculateTwoPosOut();

#endif
