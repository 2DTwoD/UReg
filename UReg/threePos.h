#ifndef _THREEPOS_H
#define _THREEPOS_H
#include <stdio.h>

typedef struct{
	uint8_t out1;
	uint8_t out2;
} ThreePosOut;

typedef struct{
	double treshold;
	double deadband;
	uint16_t waitTime;
	uint16_t pulseTime;
	uint16_t currentTime;
	int8_t inverse;
	ThreePosOut out;
	uint8_t pulseFlag;
} ThreePosSet;

void setThreePosPars(ThreePosSet *newThreePosSet);

void setThreePosCurrentTime(double pv, double sp);

ThreePosOut getThreePosOut(double pv, double sp);

#endif
