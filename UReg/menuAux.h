#ifndef _MENU_AUX_H
#define _MENU_AUX_H

#include <stdio.h>
#include <math.h>

#include "globals.h"
#include "misc.h"
//Получить значение параметра в зависимости от выбранного пункта в меню
double getMenuParameter(int8_t* navi);
//Получить шаблон отображения параметра в меню (количество разрядов до и после запятой)
char* getTemplate(int8_t* navi);
//Получить текущий выходной параметр регулятора (зависит от режима)
void getCurrentModeOut(char* field);
//Установить разряд параметра в меню (для дробных параметров)
void setMenuDigitDbl(double* value, int8_t digit, int8_t step);
//Установить разряд параметра в меню (для целочисленных параметров)
void setMenuDigitInt(uint16_t* value, int8_t digit, int8_t step, uint16_t upLim);
//Установить параметр в меню
void setMenuParameter(int8_t afterDot, int8_t step, int8_t* navi, int8_t cursor);
//Изменить уставку регулятора в направлении dir
void changeSP(int8_t dir);
//Изменить выход регулятора в направлении dir
void changeOUT(int8_t dir);
//Ограничить величину в зависимости от пределов
void cutAround(double* parameter, double downLimit, double upLimit);

#endif
