#ifndef _MENU_H
#define _MENU_H
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "misc.h"
#include "globals.h"
#include "threePos.h"
#include "pid.h"

void naviUp();
void naviDown();
void naviRight();
void naviLeft();
char* getDisp1();
char* getDisp2();
void exitMenu();
uint8_t getCursor();
#endif
