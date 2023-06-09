#include "main.h"

uint8_t segment = 0;
static char field1[5] = "-----";
static char field2[5] = "-----";
int main(void)
{
	GPIOinit();
	NVICinit();
	TIMinit();
	//GPIOD->ODR = 0xFFFF;
    while(1)
    {
    }
}

void TIM7_IRQHandler(void){
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	if(segment == 0){
		strcpy(field1, getDisp1());
		strcpy(field2, getDisp2());
	}
	segment++;
	if(segment > 3){
		segment = 0;
	}
}
