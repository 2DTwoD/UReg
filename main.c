#include "main.h"

static uint8_t segment = 0;
static uint8_t field1[4];
static uint8_t field2[4];

int main(void)
{
	GPIOinit();
	EXTIinit();
	NVICinit();
	TIMinit();
    while(1)
    {
    }
}

void TIM7_IRQHandler(void){
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	if(segment == 0){
		getLEDcodeArray(field1, getDisp1());
		getLEDcodeArray(field2, getDisp2());
	}
	GPIOD->ODR = field1[segment] | field2[segment] << 8;
	GPIOB->ODR &= ~0xFF00;
	GPIOB->ODR |= 1 << (8 + segment) | 1 << (12 + segment);
	segment ++;
	if(segment > 3){
		segment = 0;
	}
	/*if(GPIOA->IDR & 0x20){
		GPIOE->ODR ^= 0x0100;
	}*/
}

void EXTI9_5_IRQHandler(){
	EXTI_ClearFlag(EXTI_Line5);
	EXTI_ClearFlag(EXTI_Line6);
	EXTI_ClearFlag(EXTI_Line7);
	EXTI_ClearFlag(EXTI_Line8);
	 /*if(GPIOA->IDR & 1){
		 GPIOE->ODR ^= 0xFF00;
	 }*/
	GPIOE->ODR ^= 0x0100;
}
