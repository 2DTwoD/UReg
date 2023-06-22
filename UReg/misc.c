#include "misc.h"

extern uint16_t pvRaw;

static uint16_t pvArray[200];

uint16_t getAvgRawPv(){
	uint32_t avg = 0;
	int16_t i;
	for(i = 199; i >= 0; i--){
		if(i == 0){
			pvArray[i] = pvRaw;
		} else {
			pvArray[i] = pvArray[i - 1];
		}
		avg += pvArray[i];
	}
	return avg / 200;
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
