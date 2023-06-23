#ifndef _MENU_AUX_H
#define _MENU_AUX_H

#include <stdio.h>
#include <math.h>

#include "globals.h"
#include "misc.h"

double getMenuParameter(int8_t* navi);

char* getTemplate(int8_t* navi);

void getCurrentModeOut(char* field);

void setMenuDigitDbl(double* value, int8_t digit, int8_t step);

void setMenuDigitInt(uint16_t* value, int8_t digit, int8_t step, uint16_t upLim);

void setMenuParameter(int8_t afterDot, int8_t step, int8_t* navi, int8_t cursor);

void changeSP(int8_t dir);

void changeOUT(int8_t dir);

void cutAround(double* parameter, double downLimit, double upLimit);

#endif
