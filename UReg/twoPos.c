#include "twoPos.h"

static TwoPosSet twoPosSet = {0.0, 0.0, 0, 0};
static double deviation;

void setTwoPosPars(TwoPosSet *newTwoPosSet){
	twoPosSet.up_indent = newTwoPosSet->up_indent;
	twoPosSet.up_indent = newTwoPosSet->down_indent;
	twoPosSet.inverse = newTwoPosSet->inverse;
}

uint8_t getTwoPosOut(double pv, double sp){
	deviation = sp - pv;
	if(deviation > twoPosSet.up_indent){
		twoPosSet.out = 1;
	} else if(deviation < -twoPosSet.down_indent){
		twoPosSet.out = 0;
	}
	return twoPosSet.inverse? !twoPosSet.out: twoPosSet.out;
}
