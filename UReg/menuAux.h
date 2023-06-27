#ifndef _MENU_AUX_H
#define _MENU_AUX_H

#include <stdio.h>
#include <math.h>

#include "globals.h"
#include "misc.h"
//Получить значение параметра в зависимости от положения в меню
double getMenuParameter(int8_t* navi);
//Получить шаблон для отображения параметра (число разрядов, знаков после запятой)
char* getTemplate(int8_t* navi);
//Получить значение выхода регулятора в зависимости от выбранного режима
void getCurrentModeOut(char* field);
//Установить разряд дробного параметра
void setMenuDigitDbl(double* value, int8_t digit, int8_t step);
//Установить разряд целочисленного параметра
void setMenuDigitInt(uint16_t* value, int8_t digit, int8_t step, uint16_t upLim);
//Установить параметр выбранный в меню
void setMenuParameter(int8_t afterDot, int8_t step, int8_t* navi, int8_t cursor);
//Изменить уставку в зависимости от направления dir
void changeSP(int8_t dir);
//Изменить выход регулятора в зависимости от направления dir
void changeOUT(int8_t dir);
//Ограничить параметр в зависимости от пределов
void cutAround(double* parameter, double downLimit, double upLimit);

#endif
