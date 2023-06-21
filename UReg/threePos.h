#ifndef _THREEPOS_H
#define _THREEPOS_H
#include <stdio.h>
#include <stm32f30x.h>

#include "misc.h"
#include "globals.h"

void setThreePosPars(ThreePosSet *newThreePosSet);

void resetThreePos();

void setThreePosCurrentTime();

void calculateThreePosOut();

#endif
