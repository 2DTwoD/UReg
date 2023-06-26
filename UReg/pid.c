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
	if(pidSet.t == 0) return;
	pidSet.q0 = pidSet.kp + pidSet.td / pidSet.t;
	if(pidSet.ti > 0){
		pidSet.q1 = -pidSet.kp + pidSet.t / pidSet.ti - 2 * pidSet.td / pidSet.t;
	} else {
		pidSet.q1 = -pidSet.kp - 2 * pidSet.td / pidSet.t;
	}
	pidSet.q2 = pidSet.td / pidSet.t;
}

void calculatePIDout(){
	if(!AUTO) return;
	deviation = pidSet.inverse? pv - sp: sp - pv;
	if(fabs(deviation) < pidSet.db) return;
	pidSet.e2 = pidSet.e1;
	pidSet.e1 = pidSet.e0;
	pidSet.e0 = deviation;
	pidSet.out += pidSet.q0 * pidSet.e0 + pidSet.q1 * pidSet.e1 + pidSet.q2 * pidSet.e2;
	if (pidSet.out > pidSet.upOutLim){
		pidSet.out = pidSet.upOutLim;
		return;
	}
	if (pidSet.out < pidSet.downOutLim){
		pidSet.out =  pidSet.downOutLim;
	}
}
