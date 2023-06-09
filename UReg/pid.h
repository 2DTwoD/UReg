#ifndef _PID_H
#define _PID_H
#include <stdio.h>
#include <math.h>
#include "globals.h"

void restorePID(PIDset *newPIDpars);

void resetPID();

double getPIDout();

#endif
