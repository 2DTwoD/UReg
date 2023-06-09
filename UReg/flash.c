#include "flash.h"

extern uint16_t mode;
extern int8_t AUTO;
extern double sp;
extern Scale scale;
extern Limit limit;
extern TwoPosSet twoPosSet;
extern ThreePosSet threePosSet;
extern PIDset pidSet;
extern uint8_t menuParChanged;

static int32_t flashContain[25];

void readFlash(){
	int8_t i;
	for(i = 0; i < 25; i++){
		flashContain[i] = *(__IO int32_t*)(FLASH_START_ADDRESS + 4 * i);
	}
	if(flashContain[0] == TOKEN){
		mode = flashContain[1];
		AUTO = flashContain[2];
		sp = flashContain[3] / 10.0;
		scale.up = flashContain[4] / 10.0;
		scale.down = flashContain[5] / 10.0;
		limit.hh = flashContain[6] / 10.0;
		limit.lh = flashContain[7] / 10.0;
		limit.hl = flashContain[8] / 10.0;
		limit.ll = flashContain[9] / 10.0;
		twoPosSet.up_indent = flashContain[10] / 10.0;
		twoPosSet.down_indent = flashContain[11] / 10.0;
		twoPosSet.inverse = flashContain[12];
		threePosSet.treshold = flashContain[13] / 10.0;
		threePosSet.deadband = flashContain[14] / 10.0;
		threePosSet.waitTime = flashContain[15];
		threePosSet.pulseTime = flashContain[16];
		threePosSet.inverse = flashContain[17];
		pidSet.kp = flashContain[18] / 100.0;
		pidSet.ti = flashContain[19] / 10.0;
		pidSet.td = flashContain[20] / 100.0;
		pidSet.db = flashContain[21] / 10.0;
		pidSet.upOutLim = flashContain[22] / 10.0;
		pidSet.downOutLim = flashContain[23] / 10.0;
		pidSet.inverse = flashContain[24];
	}
}

void saveFlash(){
	__disable_irq();
	FLASH_Unlock();

	FLASH_ErasePage(FLASH_START_ADDRESS);
	while((FLASH->SR & FLASH_SR_BSY) != 0);

	FLASH_ProgramWord(FLASH_START_ADDRESS, TOKEN);
	FLASH_ProgramWord(FLASH_START_ADDRESS + 4, mode);
	FLASH_ProgramWord(FLASH_START_ADDRESS + 8, AUTO);
	FLASH_ProgramWord(FLASH_START_ADDRESS + 12, round(sp * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 16, (int32_t)round(scale.up * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 20, (int32_t)round(scale.down * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 24, round(limit.hh * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 28, round(limit.lh * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 32, round(limit.hl * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 36, round(limit.ll * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 40, round(twoPosSet.up_indent * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 44, round(twoPosSet.down_indent * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 48, twoPosSet.inverse);
	FLASH_ProgramWord(FLASH_START_ADDRESS + 52, round(threePosSet.treshold * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 56, round(threePosSet.deadband * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 60, threePosSet.waitTime);
	FLASH_ProgramWord(FLASH_START_ADDRESS + 64, threePosSet.pulseTime);
	FLASH_ProgramWord(FLASH_START_ADDRESS + 68, threePosSet.inverse);
	FLASH_ProgramWord(FLASH_START_ADDRESS + 72, round(pidSet.kp * 100));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 76, round(pidSet.ti * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 80, round(pidSet.td * 100));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 84, round(pidSet.db * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 88, round(pidSet.upOutLim * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 92, round(pidSet.downOutLim * 10));
	FLASH_ProgramWord(FLASH_START_ADDRESS + 96, pidSet.inverse);

	FLASH_Lock();
	__enable_irq();
	menuParChanged = 0;
}
