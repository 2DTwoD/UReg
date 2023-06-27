#include <math.h>
#include "threePos.h"

extern double pv;
extern double sp;
extern uint8_t AUTO;
extern ThreePosSet threePosSet;

static double deviation;
static uint16_t currentTime = 0;
static uint8_t pulseFlag = 0;

void resetThreePos(){
	threePosSet.out.out1 = 0;
	threePosSet.out.out2 = 0;
	currentTime = 0;
	pulseFlag = 0;
	changeDO(GPIOC, 0x30, 0);
	changeDO(GPIOE, 0xC00, 0);
}

void calculateThreePosOut(){
	if(!AUTO) return;
	deviation = threePosSet.inverse? pv - sp: sp - pv;
	if(fabs(deviation) < threePosSet.deadband && !pulseFlag){
		threePosSet.out.out1 = 0;
		threePosSet.out.out2 = 0;
		currentTime = 0;
		return;
	}
	if(fabs(deviation) > threePosSet.treshold && currentTime == 0){
		threePosSet.out.out1 = deviation > 0;
		threePosSet.out.out2 = deviation < 0;
		currentTime = 0;
		return;
	}
	currentTime++;
	if(currentTime < threePosSet.waitTime){
		threePosSet.out.out1 = 0;
		threePosSet.out.out2 = 0;
		return;
	}
	if(!pulseFlag){
		threePosSet.out.out1 = deviation > 0;
		threePosSet.out.out2 = deviation < 0;
		pulseFlag = 1;
	}
	if(currentTime > threePosSet.waitTime + threePosSet.pulseTime){
		currentTime = 0;
		pulseFlag = 0;
	}
}
