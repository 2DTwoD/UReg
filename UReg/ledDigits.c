#include "ledDigits.h"

uint8_t getLEDcode(char* c){
	switch(*c){
	case '0':
	case 'O':
		return 0x3F;
	case '1':
	case 'I':
		return 0x06;
	case '2':
		return 0x5B;
	case '3':
		return 0x4F;
	case '4':
		return 0x66;
	case '5':
	case 'S':
		return 0x6D;
	case '6':
		return 0x7D;
	case '7':
		return 0x07;
	case '8':
		return 0x7F;
	case '9':
	case 'g':
		return 0x6F;
	case 'L':
		return 0x38;
	case 'U':
		return 0x3E;
	case 'E':
		return 0x79;
	case 'P':
		return 0x73;
	case 'd':
		return 0x5E;
	case 'u':
		return 0x1C;
	case 'H':
		return 0x76;
	case 'r':
		return 0x50;
	case 't':
		return 0x78;
	case 'b':
		return 0x7C;
	case 'o':
		return 0x5C;
	case 'A':
		return 0x77;
	case '-':
		return 0x40;
	}
	return 0;
}

void getLEDcodeArray(uint16_t* digits, char* str, uint8_t shift){
	while(*str){
		*digits = getLEDcode(str);
		digits++;
		str++;
		if(*str == '.'){
			*digits |= 0x80;
			str++;
		}
		if (shift){
			*digits = *digits << 8;
		}
	}
}
