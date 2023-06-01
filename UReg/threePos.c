#include <math.h>
#include "threePos.h"

static ThreePosSet threePosSet = {5.0, 1.0, 200, 200, 0, 1, {0, 0}, 0};
static double deviation;

void setThreePosPars(ThreePosSet *newThreePosSet){
	threePosSet.treshold = newThreePosSet->treshold;
	threePosSet.deadband = newThreePosSet->deadband;
	threePosSet.waitTime = newThreePosSet->waitTime;
	threePosSet.pulseTime = newThreePosSet->pulseTime;
	threePosSet.currentTime = 0;
	threePosSet.pulseFlag = 0;
}

void setThreePosCurrentTime(double pv, double sp){
	deviation = fabs(pv - sp);
	if(deviation < threePosSet.deadband || deviation > threePosSet.treshold){
		threePosSet.currentTime = 0;
		return;
	}
	threePosSet.currentTime ++;
}

ThreePosOut getThreePosOut(double pv, double sp){
	deviation = sp - pv;
	if(fabs(deviation) < threePosSet.deadband){
		threePosSet.out.out1 = 0;
		threePosSet.out.out2 = 0;
		goto end;
	}
	if(fabs(deviation) > threePosSet.treshold){
		threePosSet.out.out1 = deviation * threePosSet.inverse > 0;
		threePosSet.out.out2 = deviation * threePosSet.inverse < 0;
		goto end;
	}
	if(threePosSet.currentTime < threePosSet.waitTime){
		threePosSet.out.out1 = 0;
		threePosSet.out.out2 = 0;
		goto end;
	}
	if(!threePosSet.pulseFlag){
		threePosSet.out.out1 = deviation * threePosSet.inverse > 0;
		threePosSet.out.out2 = deviation * threePosSet.inverse < 0;
		threePosSet.pulseFlag = 1;
	}
	if(threePosSet.currentTime > threePosSet.waitTime + threePosSet.pulseTime){
		threePosSet.currentTime = 0;
		threePosSet.pulseFlag = 0;
	}
	end:
	return threePosSet.out;
}
