#include "menu.h"

extern uint16_t mode;
extern uint8_t AUTO;
extern double pv;
extern double sp;
extern Scale scale;
extern Limit limit;
extern TwoPosSet twoPosSet;
extern ThreePosSet threePosSet;
extern PIDset pidSet;
extern int8_t prog;

//Вертикальные позиции выбранные в меню
static int8_t navi[] = {0, 0, 0};
//Горизонтальная позиция меню
static int8_t xPos = 0;
//Курсор для редактирования значений
static int8_t cursor = 0;
//Размеры списков в меню первой позиции
static int8_t sizes[] = {1, 3, 0, 2, 4, 6};
//Строки для меню позиции 0
static char* menu0Strings[] = {"ISIg", " LI ", "USE ", "2POS", "3POS", "PId "};
//Строки для меню позиции 1
static char* menu1Strings[][7] = {
		{"dSL ", "uSL "},
		{" HH ", " LH ", " HL ", " LL "},
		{"rEg "},
		{"UInd", "dInd", " rE "},
		{"trES", " db ", "0tI ", "1tI ", " rE "},
		{"PrOP", " tI ", " td ", " db ", "UPOL", "doOL", " rE "}
};
//Поле для визуализации
static char field[5];

double getMenuParameter(){
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

char* getTemplate(){
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

void setMenuParameter(int8_t afterDot, int8_t step){
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
			cutAround(&threePosSet.treshold, 0.0, 999.9);
			break;
		case 1:
			setMenuDigitDbl(&threePosSet.deadband, cursor + afterDot, step);
			cutAround(&threePosSet.deadband, 0.0, 999.9);
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

int8_t getMenuSize(int8_t prevNavi){
	switch(xPos){
	case 0: return 5;
	case 1: return sizes[prevNavi];
	default: return 0;
	}
}

int8_t getNaviLimit(int8_t step){
	int8_t prevNaviIndex = xPos - 1 >= 0? xPos - 1: 0;
	if(navi[xPos] + step < 0){
		return getMenuSize(navi[prevNaviIndex]);
	}
	if(navi[xPos] + step > getMenuSize(navi[prevNaviIndex])){
		return 0;
	}
	return navi[xPos] + step;
}

void naviUp(){
	if(prog){
		if(cursor > 0){
			setMenuParameter(*(getTemplate() + 4) - 48, 1);
		}
		navi[xPos] = getNaviLimit(-1);
	} else {
		if(AUTO){
			changeSP(1);
		} else {
			changeOUT(1);
		}
	}
}

void naviDown(){
	if(prog){
		if(cursor > 0){
			setMenuParameter(*(getTemplate() + 4) - 48, -1);
		}
		navi[xPos] = getNaviLimit(1);
	} else {
		if(AUTO){
			changeSP(-1);
		} else {
			changeOUT(-1);
		}
	}
}

void naviRight(){
	if(prog){
		if(xPos < 2){
			xPos ++;
		} else if(cursor < 4){
			cursor ++;
		}
	}
}

void naviLeft(){
	if(prog){
		if(cursor == 0){
			if(xPos > 0){
				navi[xPos] = 0;
				xPos --;
			}
		} else {
			cursor--;
		}
	}
}

char* getDisp1(){
	if(prog){
		switch(xPos){
		case 0:
			return "PArA";
		case 1:
			return menu0Strings[navi[0]];
		case 2:
			return menu1Strings[navi[0]][navi[1]];
		}
		return "----";
	}
	sprintf(field, "%05.1f", pv);
	return field;
}

char* getDisp2(){
	if(prog){
		switch(xPos){
		case 0:
			return menu0Strings[navi[0]];
		case 1:
			return menu1Strings[navi[0]][navi[1]];
		case 2:
			sprintf(field, getTemplate(), getMenuParameter());
			return field;
		}
		return "----";
	}
	if(AUTO){
		sprintf(field, "%05.1f", sp);
		return field;
	}
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
	return field;
}
void exitMenu(){
	navi[0] = 0;
	navi[1] = 0;
	navi[2] = 0;
	xPos = 0;
	cursor = 0;
}

uint8_t getCursor(){
	return cursor - 1;
}
