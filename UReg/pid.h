#ifndef _PID_H
#define _PID_H
#include <stdio.h>
#include <math.h>
#include "globals.h"

void setPID(PIDset *newPIDpars);

void resetPID();

void updatePID();

void calculatePIDout();

#endif
