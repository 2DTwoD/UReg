#include <pid.h>

extern double pv;
extern double sp;
extern uint8_t AUTO;
extern uint16_t outRaw;
extern PIDset pidSet;

static double deviation;

void resetPID(){
	pidSet.out = 0.0;
	outRaw = 0;
	pidSet.e0 = 0.0;
	pidSet.e1 = 0.0;
	pidSet.e2 = 0.0;
}

void updatePID(){
	if(pidSet.t == 0.0) return;
	if(pidSet.ti == 0.0){
		pidSet.g0 = pidSet.kp * (1.0 + pidSet.td / pidSet.t);
	} else {
		pidSet.g0 = pidSet.kp * (1.0 + pidSet.t / pidSet.ti + pidSet.td / pidSet.t);
	}
	pidSet.g1 = pidSet.kp * (-1.0 - 2.0 * pidSet.td / pidSet.t);
	pidSet.g2 = pidSet.kp * pidSet.td / pidSet.t;
}

void calculatePIDout(){
	if(!AUTO) return;
	deviation = pidSet.inverse? pv - sp: sp - pv;
	if(fabs(deviation) < pidSet.db) return;
	pidSet.e2 = pidSet.e1;
	pidSet.e1 = pidSet.e0;
	pidSet.e0 = deviation;
	pidSet.out += pidSet.g0 * pidSet.e0 + pidSet.g1 * pidSet.e1 + pidSet.g2 * pidSet.e2;
	if (pidSet.out > pidSet.upOutLim){
		pidSet.out = pidSet.upOutLim;
		return;
	}
	if (pidSet.out < pidSet.downOutLim){
		pidSet.out =  pidSet.downOutLim;
	}
}
