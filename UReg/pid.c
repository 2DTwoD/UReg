#include <pid.h>

static pidSet pidPars = {1.0, 10.0, 0.0, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1};
static double deviation;

void restorePID(pidSet *newPIDpars){
	pidPars.kp = newPIDpars->kp;
	pidPars.ti = newPIDpars->ti;
	pidPars.td = newPIDpars->td;
	pidPars.t = newPIDpars->t;
	pidPars.db = newPIDpars->db;
	pidPars.out = newPIDpars->out;
	pidPars.upOutLim = newPIDpars->upOutLim;
	pidPars.downOutLim = newPIDpars->downOutLim;
	pidPars.e0 = newPIDpars->e0;
	pidPars.e1 = newPIDpars->e1;
	pidPars.e2 = newPIDpars->e2;
	pidPars.q0 = newPIDpars->q0;
	pidPars.q1 = newPIDpars->q1;
	pidPars.q2 = newPIDpars->q2;
	pidPars.dir = newPIDpars->dir;
}

void resetPID(){
	pidPars.out = 0.0;
	pidPars.e0 = 0.0;
	pidPars.e1 = 0.0;
	pidPars.e2 = 0.0;
}

void updatePID(pidSet *newPIDpars){
	pidPars.kp = newPIDpars->kp;
	pidPars.ti = newPIDpars->ti;
	pidPars.td = newPIDpars->td;
	pidPars.t = newPIDpars->t;
	pidPars.db = newPIDpars->db;
	pidPars.q0 = pidPars.kp + pidPars.td / pidPars.t;
	pidPars.q1 = -pidPars.kp + pidPars.t / pidPars.ti - 2 * pidPars.td / pidPars.t;
	pidPars.q2 = pidPars.td / pidPars.t;
}

double getPIDout(double pv, double sp){
	deviation = sp - pv;
	if(fabs(deviation) < pidPars.db){
		return pidPars.out; 
	}
	pidPars.e2 = pidPars.e1;
	pidPars.e1 = pidPars.e0;
	pidPars.e0 = deviation * pidPars.dir;
	pidPars.out += pidPars.q0 * pidPars.e0 + pidPars.q1 * pidPars.e1 + pidPars.q2 * pidPars.e2;
	return PIDlim(pidPars.out);
}

double PIDlim(double out){
	if (out > pidPars.upOutLim){
		return pidPars.upOutLim;
	}
	if (out < pidPars.downOutLim){
		return pidPars.downOutLim;
	}
	return out;
}
