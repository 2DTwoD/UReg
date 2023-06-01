#ifndef _PID_H
#define _PID_H

typedef struct {
	double kp;
	double ti;
	double td;
	double t;
	double db;
	double out;
	double e0;
	double e1;
	double e2;
	double q0;
	double q1;
	double q2;
} pidSet;

void restorePID(pidSet *newPIDpars);

void resetPID();

void updatePID(pidSet *newPIDpars);

double getPIDout(double pv, double sp);

#endif
