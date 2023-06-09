#include "main.h"

static uint8_t segment = 0;
static uint16_t field1[4];
static uint16_t field2[4];

int main(void)
{
	GPIOinit();
	NVICinit();
	TIMinit();
    while(1)
    {
    }
}

void TIM7_IRQHandler(void){
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	if(segment == 0){
		getLEDcodeArray(field1, getDisp1(), 0);
		getLEDcodeArray(field2, getDisp2(), 1);
	}
	GPIOD->ODR = field1[segment] | field2[segment];
	segment++;
	if(segment > 3){
		segment = 0;
	}
}
