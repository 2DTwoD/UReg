#include "menu.h"

static int8_t navi[] = {1, 1};
static int8_t xPos = 0;
static int8_t cursor = 0;
static int8_t sizes[] = {6, 2, 4, 1, 3, 5, 7};
char* menu1Strings[] = {"ISIg", "LI", "USE", "2POS", "3POS", "PId"};
char* menu2Strings[][7] = {
		{"dSL", "uSL"},
		{"HH", "LH", "HL", "LL"},
		{"rEg"},
		{"UInD", "DInD", "rE"},
		{"trES", "db", "0tI", "1tI", "rE"},
		{"PrOP", "tI", "td", "db", "UPOL", "doOL", "dIr"}
};

int8_t getSizeOfMenu(){
	switch(xPos){
	case 0:
		return sizes[0];
	case 2:
		return 1;
	}
	return sizes[navi[1]];
}

void naviUp(){
	if(xPos == 2){

	}else{
		navi[xPos]--;
		if(navi[xPos] < 1){
			navi[xPos] = getSizeOfMenu();
		}
	}
}

void naviDown(){
	if(xPos == 2){

	}else{
		navi[xPos]++;
		if(navi[xPos] > getSizeOfMenu()){
			navi[xPos] = 1;
		}
	}
}

void naviRight(){
	if(xPos < 2){
		xPos ++;
	}
	if(xPos == 2 && cursor < 3){
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
	switch(xPos){
	case 0:
		return "PAr";
	case 1:
		return menu1Strings[navi[0]];
	case 2:
		return menu2Strings[navi[0] - 1][navi[1]];
	}
	return "----";
}

char* getDisp2(){
	switch(xPos){
	case 0:
		return menu1Strings[navi[0]];
	case 1:
		return menu2Strings[navi[0] - 1][navi[1]];
	case 2:
		return "0000";
	}
	return "----";
}
