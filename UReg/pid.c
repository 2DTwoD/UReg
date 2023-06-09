#include <pid.h>

static double deviation;
extern double pv;
extern double sp;
extern PIDset pidSet;

void restorePID(PIDset *newPIDset){
	pidSet.kp = newPIDset->kp;
	pidSet.ti = newPIDset->ti;
	pidSet.td = newPIDset->td;
	pidSet.t = newPIDset->t;
	pidSet.db = newPIDset->db;
	pidSet.out = newPIDset->out;
	pidSet.upOutLim = newPIDset->upOutLim;
	pidSet.downOutLim = newPIDset->downOutLim;
	pidSet.e0 = newPIDset->e0;
	pidSet.e1 = newPIDset->e1;
	pidSet.e2 = newPIDset->e2;
	pidSet.q0 = newPIDset->q0;
	pidSet.q1 = newPIDset->q1;
	pidSet.q2 = newPIDset->q2;
	pidSet.inverse = newPIDset->inverse;
}

void resetPID(){
	pidSet.out = 0.0;
	pidSet.e0 = 0.0;
	pidSet.e1 = 0.0;
	pidSet.e2 = 0.0;
}

double getPIDout(){
	deviation = sp - pv;
	if(fabs(deviation) < pidSet.db){
		return pidSet.out;
	}
	pidSet.e2 = pidSet.e1;
	pidSet.e1 = pidSet.e0;
	pidSet.e0 = deviation * pidSet.inverse? -1: 1;
	pidSet.out += pidSet.q0 * pidSet.e0 + pidSet.q1 * pidSet.e1 + pidSet.q2 * pidSet.e2;
	if (pidSet.out > pidSet.upOutLim){
		return pidSet.upOutLim;
	}
	if (pidSet.out < pidSet.downOutLim){
		return pidSet.downOutLim;
	}
	return pidSet.out;
}
