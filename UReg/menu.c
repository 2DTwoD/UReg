#include "menu.h"

extern uint16_t mode;
extern uint8_t AUTO;
extern double pv;
extern double sp;
extern double out;
extern Scale scale;
extern Limit limit;
extern TwoPosSet twoPosSet;
extern ThreePosSet threePosSet;
extern PIDset pidSet;

//Режим параметризации (0 - наблюдение, 1 - параметризация)
static int8_t prog = 0;
//Вертикальные позиции выбранные в меню
static int8_t navi[] = {0, 0, 0};
//Горизонтальная позиция меню
static int8_t xPos = 0;
//Курсор для редактирования значений
static int8_t cursor = 0;
//Размеры списков меню
static int8_t sizes[][6] = {
		{6},
		{2, 4, 1, 3, 5, 7},
		{1}
};
//Строки для меню позиции 0
static char* menu0Strings[] = {"ISIg", " LI ", "USE ", "2POS", "3POS", "PId "};
//Строки для меню позиции 1
static char* menu1Strings[][7] = {
		{"dSL ", "uSL "},
		{" HH ", " LH ", " HL ", " LL "},
		{"rEg "},
		{"UInD", "DInD", " rE "},
		{"trES", " db ", "0tI ", "1tI ", " rE "},
		{"PrOP", " tI ", " td ", " db ", "UPOL", "doOL", "dIr "}
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
		return "%4.0f";
	case 3:
		if(navi[1] == 2){
			return "%4.0f";
		}
		break;
	case 4:
		if(navi[1] > 1){
			return "%4.0f";
		}
		break;
	case 5:
		switch(navi[1]){
		case 0:
			return "%5.2f";
		case 6:
			return "%4.0f";
		}
		break;
	}
	return "%5.1f";
}


void setMenuDigitDbl(double* value, int8_t digit, int8_t step){
	int16_t valDigit = *value;
	int16_t powTen = pow(10, 4 - digit);
	valDigit /= powTen;
	valDigit %= 10;
	*value -= valDigit * powTen;
	valDigit += step;
	if(valDigit > 9){
		valDigit = 0;
	} else if(valDigit < 0){
		valDigit = 9;
	}
	*value += valDigit * powTen;
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
			setMenuDigitDbl(&scale.down, cursor - afterDot, step);
			if(scale.down > scale.up){
				scale.down = scale.up;
			}
			break;
		case 1:
			setMenuDigitDbl(&scale.up, cursor - afterDot, step);
			if(scale.up < scale.down){
				scale.up = scale.down;
			}
			break;
		}
		break;
	case 1:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&limit.hh, cursor - afterDot, step);
			if(limit.hh < limit.lh){
				limit.hh = limit.lh;
			}
			break;
		case 1:
			setMenuDigitDbl(&limit.lh, cursor - afterDot, step);
			if(limit.lh > limit.hh){
				limit.lh = limit.hh;
			} else if(limit.lh < limit.hl){
				limit.lh = limit.hl;
			}
			break;
		case 2:
			setMenuDigitDbl(&limit.hl, cursor - afterDot, step);
			if(limit.hl > limit.lh){
				limit.hl = limit.lh;
			} else if(limit.hl < limit.ll){
				limit.hl = limit.ll;
			}
			break;
		case 3:
			setMenuDigitDbl(&limit.ll, cursor - afterDot, step);
			if(limit.ll > limit.hl){
				limit.ll = limit.hl;
			}
			break;
		}
		break;
	case 2:
		setMenuDigitInt(&mode, cursor - afterDot, step, 2);
		break;
	case 3:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&twoPosSet.up_indent, cursor - afterDot, step);
			break;
		case 1:
			setMenuDigitDbl(&twoPosSet.down_indent, cursor - afterDot, step);
			break;
		case 2:
			setMenuDigitInt(&twoPosSet.inverse, cursor - afterDot, step, 1);
			break;
		}
		break;
	case 4:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&threePosSet.treshold, cursor - afterDot, step);
			break;
		case 1:
			setMenuDigitDbl(&threePosSet.deadband, cursor - afterDot, step);
			break;
		case 2:
			setMenuDigitInt(&threePosSet.waitTime, cursor - afterDot, step, 9);
			break;
		case 3:
			setMenuDigitInt(&threePosSet.pulseTime, cursor - afterDot, step, 9);
			break;
		case 4:
			setMenuDigitInt(&threePosSet.inverse, cursor - afterDot, step, 1);
			break;
		}
		break;
	case 5:
		switch(navi[1]){
		case 0:
			setMenuDigitDbl(&pidSet.kp, cursor - afterDot, step);
			break;
		case 1:
			setMenuDigitDbl(&pidSet.ti, cursor - afterDot, step);
			break;
		case 2:
			setMenuDigitDbl(&pidSet.td, cursor - afterDot, step);
			break;
		case 3:
			setMenuDigitDbl(&pidSet.db, cursor - afterDot, step);
			break;
		case 4:
			setMenuDigitDbl(&pidSet.upOutLim, cursor - afterDot, step);
			if(pidSet.upOutLim < pidSet.downOutLim){
				pidSet.upOutLim = pidSet.downOutLim;
			}
			break;
		case 5:
			setMenuDigitDbl(&pidSet.downOutLim, cursor - afterDot, step);
			if(pidSet.downOutLim > pidSet.upOutLim){
				pidSet.downOutLim = pidSet.upOutLim;
			}
			break;
		case 6:
			setMenuDigitInt(&pidSet.inverse, cursor - afterDot, step, 1);
			break;
		}
		break;
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
		if(out != 0.0){
			out = 0.0;
		} else {
			out = 1.0;
		}
		break;
	case 1:
		out += dir;
		if(out > 1.0){
			out = 1.0;
		} else if(out < -1){
			out = -1.0;
		}
		break;
	case 2:
		out += dir;
		if(out > 100.0){
			out = 100.0;
		} else if(out < 0.0){
			out = 0.0;
		}
		break;
	}
}

void setNaviLimit(){
	if(navi[xPos] < 0){
		navi[xPos] = sizes[xPos][navi[xPos]] - 1;
	}
	if(navi[xPos] > sizes[xPos][navi[xPos]] - 1){
		navi[xPos] = 0;
	}
}

void naviUp(){
	if(prog){
		if(cursor > 0){
			setMenuParameter(*(getTemplate() + 3) - 49, 1);
		}
		navi[xPos]--;
		setNaviLimit();
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
			setMenuParameter(*(getTemplate() + 3) - 49, -1);
		}
		navi[xPos]++;
		setNaviLimit();
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
		} else if(cursor < 3){
			cursor ++;
		}
	}
}

void naviLeft(){
	if(prog){
		if(cursor == 0){
			xPos --;
		} else {
			cursor--;
		}
		if(xPos < 0){
			xPos = 0;
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
	sprintf(field, "%5.1f", pv);
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
		sprintf(field, "%5.1f", sp);
		return field;
	}
	sprintf(field, "%5.1f", out);
	return field;
}

void setProg(){
	prog = 1;
}

void resetProg(){
	prog = 0;
}
