#include <math.h>
#include "threePos.h"

static double deviation;
extern double pv;
extern double sp;
extern ThreePosSet threePosSet;

void setThreePosPars(ThreePosSet *newThreePosSet){
	threePosSet.treshold = newThreePosSet->treshold;
	threePosSet.deadband = newThreePosSet->deadband;
	threePosSet.waitTime = newThreePosSet->waitTime;
	threePosSet.pulseTime = newThreePosSet->pulseTime;
	threePosSet.inverse = newThreePosSet->inverse;
	threePosSet.currentTime = 0;
	threePosSet.pulseFlag = 0;
}

void resetThreePos(){
	threePosSet.currentTime = 0;
	threePosSet.out.out1 = 0;
	threePosSet.out.out2 = 0;
	threePosSet.pulseFlag = 0;
}

void setThreePosCurrentTime(){
	deviation = fabs(pv - sp);
	if(deviation < threePosSet.deadband || deviation > threePosSet.treshold){
		threePosSet.currentTime = 0;
		return;
	}
	threePosSet.currentTime ++;
}

void calculateThreePosOut(){
	deviation = threePosSet.inverse? pv - sp: sp - pv;
	if(fabs(deviation) < threePosSet.deadband){
		threePosSet.out.out1 = 0;
		threePosSet.out.out2 = 0;
		return;
	}
	if(fabs(deviation) > threePosSet.treshold){
		threePosSet.out.out1 = deviation > 0;
		threePosSet.out.out2 = deviation < 0;
		return;
	}
	if(threePosSet.currentTime < threePosSet.waitTime){
		threePosSet.out.out1 = 0;
		threePosSet.out.out2 = 0;
		return;
	}
	if(!threePosSet.pulseFlag){
		threePosSet.out.out1 = deviation > 0;
		threePosSet.out.out2 = deviation < 0;
		threePosSet.pulseFlag = 1;
	}
	if(threePosSet.currentTime > threePosSet.waitTime + threePosSet.pulseTime){
		threePosSet.currentTime = 0;
		threePosSet.pulseFlag = 0;
	}
}
