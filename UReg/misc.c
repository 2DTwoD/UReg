#include "misc.h"

extern uint16_t pvRaw;

static uint16_t pvArray[MAX_AVG_NUM];
static uint8_t currentAvgIndex = 0;

uint16_t getAvgRawPv(){
	pvArray[currentAvgIndex] = pvRaw;
	currentAvgIndex++;
	if(currentAvgIndex >= MAX_AVG_NUM){
		currentAvgIndex = 0;
	}
	uint32_t avg = 0;
	int16_t i;
	for(i = 0; i < MAX_AVG_NUM; i++){
		avg += pvArray[i];
	}
	return avg / MAX_AVG_NUM;
}

void resetRegulators(){
	resetTwoPos();
	resetThreePos();
	resetPID();
}

void timerUpdater(onDelay* timer){
	if(timer->start){
		if(timer->currentTime < timer->delay){
			timer->currentTime++;
		} else {
			timer->finish = 1;
		}
	} else {
		timer->finish = 0;
		timer->currentTime = 0;
	}
}

void changeDO(GPIO_TypeDef* gpio, uint16_t mask, uint16_t value){
	if((gpio->ODR & mask) != value){
		gpio->ODR &= ~mask;
		gpio->ODR |= value;
	}
}
