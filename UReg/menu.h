#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>

#include "misc.h"
#include "globals.h"
#include "threePos.h"
#include "pid.h"
#include "menuAux.h"

//Действие при нажатии кнопки управления меню вверх
void naviUp();
//Действие при нажатии кнопки управления меню вниз
void naviDown();
//Действие при нажатии кнопки управления меню вправо
void naviRight();
//Действие при нажатии кнопки управления меню влево
void naviLeft();
//Получить строку для отображения на 1 индикаторе
char* getDisp1();
//Получить строку для отображения на 2 индикаторе
char* getDisp2();
//Сброс меню в начальное положение
void exitMenu();
//Полечить положение курсора
uint8_t getCursor();
#endif
