#include "menu.h"

extern uint16_t mode;
extern uint8_t AUTO;
extern double pv;
extern double sp;
extern int8_t prog;

//Вертикальные позиции выбранные в меню
static int8_t navi[] = {0, 0, 0};
//Горизонтальная позиция меню
static int8_t xPos = 0;
//Курсор для редактирования значений
static int8_t cursor = 0;
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
//Размеры списков в меню первой позиции
static int8_t sizes[] = {1, 3, 0, 2, 4, 6};
//Поле для визуализации
static char field[5];


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
			setMenuParameter(*(getTemplate(navi) + 4) - 48, 1, navi, cursor);
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
			setMenuParameter(*(getTemplate(navi) + 4) - 48, -1, navi, cursor);
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
			sprintf(field, getTemplate(navi), getMenuParameter(navi));
			return field;
		}
		return "----";
	}
	if(AUTO){
		sprintf(field, "%05.1f", sp);
		return field;
	}
	getCurrentModeOut(field);
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
