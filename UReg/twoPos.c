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

void calculateTwoPosOut(){
	deviation = twoPosSet.inverse > 0? pv - sp: sp - pv;
	if(deviation > twoPosSet.up_indent){
		twoPosSet.out = 1;
	} else if(deviation < -twoPosSet.down_indent){
		twoPosSet.out = 0;
	}
}
