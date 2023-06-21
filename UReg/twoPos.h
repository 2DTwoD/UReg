#ifndef _TWOPOS_H
#define _TWOPOS_H
#include <stdio.h>
#include <stm32f30x.h>

#include "misc.h"
#include "globals.h"

void setTwoPosPars(TwoPosSet *newTwoPosSet);

void resetTwoPos();

void calculateTwoPosOut();

#endif
