#include "menuAux.h"

extern uint16_t mode;
extern double sp;
extern Scale scale;
extern Limit limit;
extern TwoPosSet twoPosSet;
extern ThreePosSet threePosSet;
extern PIDset pidSet;

double getMenuParameter(int8_t* navi){
	switch(navi[0]){
	case 0:
		switch(navi[1]){
		case 0:
			return scale.down;
		case 1:
			return scale.up;
		}
		break;
	case 1:
		switch(navi[1]){
		case 0:
			return limit.hh;
		case 1:
			return limit.lh;
		case 2:
			return limit.hl;
		case 3:
			return limit.ll;
		}
		break;
	case 2:
		return mode;
		break;
	case 3:
		switch(navi[1]){
		case 0:
			return twoPosSet.up_indent;
		case 1:
			return twoPosSet.down_indent;
		case 2:
			return twoPosSet.inverse;
		}
		break;
	case 4:
		switch(navi[1]){
		case 0:
			return threePosSet.treshold;
		case 1:
			return threePosSet.deadband;
		case 2:
			return threePosSet.waitTime;
		case 3:
			return threePosSet.pulseTime;
		case 4:
			return threePosSet.inverse;
		}
		break;
	case 5:
		switch(navi[1]){
		case 0:
			return pidSet.kp;
		case 1:
			return pidSet.ti;
		case 2:
			return pidSet.td;
		case 3:
			return pidSet.db;
		case 4:
			return pidSet.upOutLim;
		case 5:
			return pidSet.downOutLim;
		case 6:
			return pidSet.inverse;
		}
		break;
	}
	return 987.6;
}

char* getTemplate(int8_t* navi){
	switch(navi[0]){
	case 2:
		return "%04.0f";
	case 3:
		if(navi[1] == 2){
			return "%04.0f";
		}
		break;
	case 4:
		if(navi[1] > 1){
			return "%04.0f";
		}
		break;
	case 5:
		switch(navi[1]){
		case 0:
			return "%05.2f";
		case 6:
			return "%04.0f";
		}
		break;
	}
	return "%05.1f";
}

void cutAround(double* parameter, double downLimit, double upLimit){
	if(*parameter > upLimit){
		*parameter = upLimit;
	} else if(*parameter < downLimit){
		*parameter = downLimit;
	}
}
void setMenuDigitDbl(double* value, int8_t digit, int8_t step){
	double powTen = pow(10, 4 - digit);
	*value += powTen * step;
}
void setMenuDigitInt(uint16_t* value, int8_t digit, int8_t step, uint16_t upLim){
	if(upLim != 9 && digit != 4){
		return;
	}
	int16_t valDigit = *value;
	int16_t powTen = pow(10, 4 - digit);
	valDigit /= powTen;
	valDigit %= 10;
	*value -= valDigit * powTen;
	valDigit += step;
	if(valDigit > upLim){
		valDigit = 0;
	} else if(valDigit < 0){
		valDigit = upLim;
	}
	*value += valDigit * powTen;
}

void setMenuParameter(int8_t afterDot, int8_t step, int8_t* navi, int8_t cursor){
	switch(navi[0]){
	case 0:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&scale.down, cursor + afterDot, step);
			cutAround(&scale.down, -99.9, scale.up);
			break;
		case 1:
			setMenuDigitDbl(&scale.up, cursor + afterDot, step);
			cutAround(&scale.up, scale.down, 999.9);
			break;
		}
		break;
	case 1:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&limit.hh, cursor + afterDot, step);
			cutAround(&limit.hh, limit.lh, 100.0);
			break;
		case 1:
			setMenuDigitDbl(&limit.lh, cursor + afterDot, step);
			cutAround(&limit.lh, limit.hl, limit.hh);
			break;
		case 2:
			setMenuDigitDbl(&limit.hl, cursor + afterDot, step);
			cutAround(&limit.hl, limit.ll, limit.lh);
			break;
		case 3:
			setMenuDigitDbl(&limit.ll, cursor + afterDot, step);
			cutAround(&limit.ll, 0.0, limit.hl);
			break;
		}
		break;
	case 2:
		setMenuDigitInt(&mode, cursor, step, 2);
		resetRegulators();
		break;
	case 3:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&twoPosSet.up_indent, cursor + afterDot, step);
			cutAround(&twoPosSet.up_indent, 0.0, 999.9);
			break;
		case 1:
			setMenuDigitDbl(&twoPosSet.down_indent, cursor + afterDot, step);
			cutAround(&twoPosSet.down_indent, 0.0, 999.9);
			break;
		case 2:
			setMenuDigitInt(&twoPosSet.inverse, cursor, step, 1);
			break;
		}
		break;
	case 4:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&threePosSet.treshold, cursor + afterDot, step);
			cutAround(&threePosSet.treshold, threePosSet.deadband, 999.9);
			break;
		case 1:
			setMenuDigitDbl(&threePosSet.deadband, cursor + afterDot, step);
			cutAround(&threePosSet.deadband, 0.0, threePosSet.treshold);
			break;
		case 2:
			setMenuDigitInt(&threePosSet.waitTime, cursor, step, 9);
			break;
		case 3:
			setMenuDigitInt(&threePosSet.pulseTime, cursor, step, 9);
			break;
		case 4:
			setMenuDigitInt(&threePosSet.inverse, cursor, step, 1);
			break;
		}
		break;
	case 5:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&pidSet.kp, cursor + afterDot, step);
			cutAround(&pidSet.kp, 0.0, 99.99);
			break;
		case 1:
			setMenuDigitDbl(&pidSet.ti, cursor + afterDot, step);
			cutAround(&pidSet.ti, 0.0, 999.9);
			break;
		case 2:
			setMenuDigitDbl(&pidSet.td, cursor + afterDot, step);
			cutAround(&pidSet.td, 0.0, 999.9);
			break;
		case 3:
			setMenuDigitDbl(&pidSet.db, cursor + afterDot, step);
			cutAround(&pidSet.db, 0.0, 999.9);
			break;
		case 4:
			setMenuDigitDbl(&pidSet.upOutLim, cursor + afterDot, step);
			cutAround(&pidSet.upOutLim, pidSet.downOutLim, 100.0);
			break;
		case 5:
			setMenuDigitDbl(&pidSet.downOutLim, cursor + afterDot, step);
			cutAround(&pidSet.downOutLim, 0.0, pidSet.upOutLim);
			break;
		case 6:
			setMenuDigitInt(&pidSet.inverse, cursor, step, 1);
			break;
		}
		break;
		updatePID();
	}
}

void changeSP(int8_t dir){
	double step = (scale.up - scale.down) / 100;
	if (step < 0.1){
		step  = 0.1;
	}
	sp += step * dir;
	if(sp > scale.up){
		sp = scale.up;
	} else if(sp < scale.down){
		sp = scale.down;
	}
}

void changeOUT(int8_t dir){
	switch(mode){
	case 0:
		twoPosSet.out = !twoPosSet.out;
		break;
	case 1:
		if(dir > 0){
			if(threePosSet.out.out2){
				threePosSet.out.out2 = 0;
			}else if(!threePosSet.out.out1){
				threePosSet.out.out1 = 1;
			}
		} else {
			if(threePosSet.out.out1){
				threePosSet.out.out1 = 0;
			} else if(!threePosSet.out.out2){
				threePosSet.out.out2 = 1;
			}
		}
		if(threePosSet.out.out1 && threePosSet.out.out2){
			threePosSet.out.out1 = 0;
			threePosSet.out.out2 = 0;
		}
		break;
	case 2:
		pidSet.out += dir;
		if(pidSet.out > 100.0){
			pidSet.out = 100.0;
		} else if(pidSet.out < 0.0){
			pidSet.out = 0.0;
		}
		break;
	}
}

void getCurrentModeOut(char* field){
	switch(mode){
	case 0:
		sprintf(field, "%04d", twoPosSet.out);
		break;
	case 1:
		sprintf(field, "%04d", threePosSet.out.out1 - threePosSet.out.out2);
		break;
	default:
		sprintf(field, "%05.1f", pidSet.out);
		break;
	}
}
