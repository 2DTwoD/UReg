#include "twoPos.h"

extern double pv;
extern double sp;
extern uint8_t AUTO;
extern TwoPosSet twoPosSet;

static double deviation;

void setTwoPosPars(TwoPosSet *newTwoPosSet){
	twoPosSet.up_indent = newTwoPosSet->up_indent;
	twoPosSet.up_indent = newTwoPosSet->down_indent;
	twoPosSet.inverse = newTwoPosSet->inverse;
}

void resetTwoPos(){
	twoPosSet.out = 0;
	changeDO(GPIOC, 0x10, 0);
	changeDO(GPIOE, 0x400, 0);
}

void calculateTwoPosOut(){
	if(!AUTO) return;
	deviation = twoPosSet.inverse? pv - sp: sp - pv;
	if(deviation > twoPosSet.up_indent){
		twoPosSet.out = 1;
	} else if(deviation <= -twoPosSet.down_indent){
		twoPosSet.out = 0;
	}
}
