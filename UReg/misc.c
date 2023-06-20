#include "misc.h"

void timerUpdater(onDelay* timer){
	if(timer->start){
		if(timer->currentTime < timer->delay){
			timer->currentTime++;
		} else {
			timer->finish = 1;
		}
	} else {
		timer->finish = 0;
	}
}

void changeDO(GPIO_TypeDef* gpio, uint16_t mask, uint16_t value){
	if((gpio->ODR & mask) != value){
		gpio->ODR &= ~mask;
		gpio->ODR |= mask;
	}
}
