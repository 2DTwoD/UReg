#include "menu.h"

extern uint8_t mode;
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
		{"trES", " db ", "0tI", "1tI", " rE "},
		{"PrOP", " tI ", " td ", " db ", "UPOL", "doOL", "dIr "}
};
static char field[5];

void setNaviLimit(){
	if(navi[xPos] < 0){
		navi[xPos] = sizes[xPos][navi[xPos]] - 1;
	}
	if(navi[xPos] > sizes[xPos][navi[xPos]] - 1){
		navi[xPos] = 0;
	}
}

void setMenuParameterLimit(double* value){

}

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

void setMenuParameter(double inc){
	switch(navi[0]){
	case 0:
		switch(navi[1]){
		case 0:
			scale.down += inc;
			break;
		case 1:
			scale.up += inc;
			break;
		}
		break;
	case 1:
		switch(navi[1]){
		case 0:
			limit.hh += inc;
			break;
		case 1:
			limit.lh += inc;
			break;
		case 2:
			limit.hl += inc;
			break;
		case 3:
			limit.ll += inc;
			break;
		}
		break;
	case 2:
		mode += inc;
		break;
	case 3:
		switch(navi[1]){
		case 0:
			twoPosSet.up_indent += inc;
			break;
		case 1:
			twoPosSet.down_indent += inc;
			break;
		case 2:
			twoPosSet.inverse += inc;
			break;
		}
		break;
	case 4:
		switch(navi[1]){
		case 0:
			threePosSet.treshold += inc;
			break;
		case 1:
			threePosSet.deadband += inc;
			break;
		case 2:
			threePosSet.waitTime += inc;
			break;
		case 3:
			threePosSet.pulseTime += inc;
			break;
		case 4:
			threePosSet.inverse += inc;
			break;
		}
		break;
	case 5:
		switch(navi[1]){
		case 0:
			pidSet.kp += inc;
			break;
		case 1:
			pidSet.ti += inc;
			break;
		case 2:
			pidSet.td += inc;
			break;
		case 3:
			pidSet.db += inc;
			break;
		case 4:
			pidSet.upOutLim += inc;
			break;
		case 5:
			pidSet.downOutLim += inc;
			break;
		case 6:
			pidSet.inverse += inc;
			break;
		}
		break;
	}
}

void naviUp(){
	if(cursor > 0){
		int8_t shift = *(getTemplate() + 3) - 49;
		setMenuParameter(pow(10, 4 - cursor - shift));
	}
	navi[xPos]--;
	setNaviLimit();
}

void naviDown(){
	if(cursor > 0){
		int8_t shift = *(getTemplate() + 3) - 49;
		setMenuParameter(-pow(10, 4 - cursor - shift));
	}
	navi[xPos]++;
	setNaviLimit();
}

void naviRight(){
	if(xPos < 2){
		xPos ++;
	} else if(cursor < 3){
		cursor ++;
	}
}

void naviLeft(){
	if(cursor == 0){
		xPos --;
	} else {
		cursor--;
	}
	if(xPos < 0){
		xPos = 0;
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
