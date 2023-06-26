#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>

#include "misc.h"
#include "globals.h"
#include "threePos.h"
#include "pid.h"
#include "menuAux.h"

//Навигация в меню - обработка нажатия кнопки вверх
void naviUp();
//Навигация в меню - обработка нажатия кнопки вниз
void naviDown();
//Навигация в меню - обработка нажатия кнопки вправо
void naviRight();
//Навигация в меню - обработка нажатия кнопки влево
void naviLeft();
//Получить строку для 1 индикатора (зависит от выбранного пункта в меню)
char* getDisp1();
//Получить строку для 2 индикатора (зависит от выбранного пункта в меню)
char* getDisp2();
//Сброс меню в начальное положение
void exitMenu();
//Получить текущую позицию курсора
uint8_t getCursor();
#endif
