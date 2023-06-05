#include "twoPos.h"

static double deviation;
extern double pv;
extern double sp;
extern TwoPosSet twoPosSet;

void setTwoPosPars(TwoPosSet *newTwoPosSet){
	twoPosSet.up_indent = newTwoPosSet->up_indent;
	twoPosSet.up_indent = newTwoPosSet->down_indent;
	twoPosSet.inverse = newTwoPosSet->inverse;
}

uint8_t getTwoPosOut(){
	deviation = sp - pv;
	if(deviation > twoPosSet.up_indent){
		twoPosSet.out = 1;
	} else if(deviation < -twoPosSet.down_indent){
		twoPosSet.out = 0;
	}
	return twoPosSet.inverse > 0? twoPosSet.out: !twoPosSet.out;
}
