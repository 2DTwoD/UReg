#ifndef _TWOPOS_H
#define _TWOPOS_H
#include <stdio.h>

typedef struct{
	double up_indent;
	double down_indent;
	uint8_t inverse;
	uint8_t out;
} TwoPosSet;

void setTwoPosPars(TwoPosSet *newTwoPosSet);

uint8_t getTwoPosOut(double pv, double sp);

#endif
