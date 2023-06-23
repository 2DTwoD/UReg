#include "flash.h"

extern uint16_t mode;
extern int8_t AUTO;
extern double sp;
extern Scale scale;
extern Limit limit;
extern TwoPosSet twoPosSet;
extern ThreePosSet threePosSet;
extern PIDset pidSet;

static float flashContain[25];
static uint32_t startAddress = 0x0807F800;
static int16_t token = 12321;

void readFlash(){
	int8_t i;
	int8_t shift = 0;
	for(i = 0; i < 25; i++){
		shift = 4 * i;
		flashContain[i] = (*(__IO uint32_t*)(startAddress + shift)) |
						  (*(__IO uint32_t*)(startAddress + shift + 1)) << 8 |
						  (*(__IO uint32_t*)(startAddress + shift + 2)) << 16 |
						  (*(__IO uint32_t*)(startAddress + shift + 3)) << 24;
	}
	if(flashContain[0] == token){
		mode = flashContain[1];
		AUTO = flashContain[2];
		sp = flashContain[3];
		scale.up = flashContain[4];
		scale.down = flashContain[5];
		limit.hh = flashContain[6];
		limit.lh = flashContain[7];
		limit.hl = flashContain[8];
		limit.ll = flashContain[9];
		twoPosSet.up_indent = flashContain[10];
		twoPosSet.down_indent = flashContain[11];
		twoPosSet.inverse = flashContain[12];
		threePosSet.treshold = flashContain[13];
		threePosSet.deadband = flashContain[14];
		threePosSet.waitTime = flashContain[15];
		threePosSet.pulseTime = flashContain[16];
		threePosSet.inverse = flashContain[17];
		pidSet.kp = flashContain[18];
		pidSet.ti = flashContain[19];
		pidSet.td = flashContain[20];
		pidSet.db = flashContain[21];
		pidSet.upOutLim = flashContain[22];
		pidSet.downOutLim = flashContain[23];
		pidSet.inverse = flashContain[24];
	}
}

void saveFlash(){
	FLASH_Unlock();

	FLASH_ErasePage(startAddress);

	FLASH_ProgramWord(startAddress, token);
	FLASH_ProgramWord(startAddress + 4, mode);
	FLASH_ProgramWord(startAddress + 8, AUTO);
	FLASH_ProgramWord(startAddress + 12, sp);
	FLASH_ProgramWord(startAddress + 16, scale.up);
	FLASH_ProgramWord(startAddress + 20, scale.down);
	FLASH_ProgramWord(startAddress + 24, limit.hh);
	FLASH_ProgramWord(startAddress + 28, limit.lh);
	FLASH_ProgramWord(startAddress + 32, limit.hl);
	FLASH_ProgramWord(startAddress + 36, limit.ll);
	FLASH_ProgramWord(startAddress + 40, twoPosSet.up_indent);
	FLASH_ProgramWord(startAddress + 44, twoPosSet.down_indent);
	FLASH_ProgramWord(startAddress + 48, twoPosSet.inverse);
	FLASH_ProgramWord(startAddress + 52, threePosSet.treshold);
	FLASH_ProgramWord(startAddress + 56, threePosSet.deadband);
	FLASH_ProgramWord(startAddress + 60, threePosSet.waitTime);
	FLASH_ProgramWord(startAddress + 64, threePosSet.pulseTime);
	FLASH_ProgramWord(startAddress + 68, threePosSet.inverse);
	FLASH_ProgramWord(startAddress + 72, pidSet.kp);
	FLASH_ProgramWord(startAddress + 76, pidSet.ti);
	FLASH_ProgramWord(startAddress + 80, pidSet.td);
	FLASH_ProgramWord(startAddress + 84, pidSet.db);
	FLASH_ProgramWord(startAddress + 88, pidSet.upOutLim);
	FLASH_ProgramWord(startAddress + 92, pidSet.downOutLim);
	FLASH_ProgramWord(startAddress + 96, pidSet.inverse);

	FLASH_Lock();
}
