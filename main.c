#include "main.h"

static uint8_t segment = 0;
static uint8_t field1[4];
static uint8_t field2[4];
static uint8_t blinkCount = 0;
static uint8_t blink = 0;
static onDelay buttonUp = {0, 1, 0, 0};
static onDelay buttonDown = {0, 1, 0, 0};
onDelay buttonLeft = {0, 1, 0, 0};
static onDelay buttonRight = {0, 1, 0, 0};
static onDelay auxLeft = {0, 120, 0, 0};
static onDelay auxRight = {0, 120, 0, 0};
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

void updateTimer(onDelay* timer){
	if(timer->start){
		if(timer->currentTime < timer->delay){
			timer->currentTime ++;
		} else {
			timer->finish = 1;
		}
	} else {
		timer->finish = 0;
	}
}

//Цикл 25мс
void TIM4_IRQHandler(void){
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	updateTimer(&buttonUp);
	updateTimer(&buttonDown);
	updateTimer(&buttonLeft);
	updateTimer(&buttonRight);
	updateTimer(&auxLeft);
	updateTimer(&auxRight);
}

//Цикл 2,5мс для обновления семисегментного индикатора
void TIM7_IRQHandler(void){
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	if(blinkCount < 125){
		blinkCount++;
	} else {
		blinkCount = 0;
		blink = !blink;
	}
	if(segment == 0){
		getLEDcodeArray(field1, getDisp1());
		getLEDcodeArray(field2, getDisp2());
	}
	GPIOD->ODR = field1[segment] | field2[segment] << 8;
	GPIOB->ODR &= 0xFF;
	GPIOB->ODR |= 1 << (8 + segment) | (segment != getCursor() || blink) << (12 + segment);
	segment ++;
	if(segment > 3){
		segment = 0;
	}
}

//Обработка прерываний кнопок
void EXTI9_5_IRQHandler(){
	EXTI_ClearFlag(EXTI_Line5);
	EXTI_ClearFlag(EXTI_Line6);
	EXTI_ClearFlag(EXTI_Line7);
	EXTI_ClearFlag(EXTI_Line8);
	buttonUp.start = GPIOA->IDR & GPIO_Pin_5 && 1;
	buttonDown.start = GPIOA->IDR & GPIO_Pin_6 && 1;
	buttonRight.start = GPIOA->IDR & GPIO_Pin_7 && 1;
	buttonLeft.start = GPIOA->IDR & GPIO_Pin_8 && 1;
	auxRight.start = GPIOA->IDR & GPIO_Pin_7 && 1;
	auxLeft.start = GPIOA->IDR & GPIO_Pin_8 && 1;
	if(buttonUp.finish && !(GPIOA->IDR & GPIO_Pin_5)){
		naviUp();
	}
	if(buttonDown.finish && !(GPIOA->IDR & GPIO_Pin_6)){
		naviDown();
	}
	if(buttonRight.finish  && !auxRight.finish && !(GPIOA->IDR & GPIO_Pin_7)){
		naviRight();
	}
	if(buttonLeft.finish && !auxLeft.finish && !(GPIOA->IDR & GPIO_Pin_8)){
		naviLeft();
	}
	if(auxRight.finish && !(GPIOA->IDR & GPIO_Pin_7)){
		prog = 1;
	}
	if(auxLeft.finish && !(GPIOA->IDR & GPIO_Pin_8)){
		if(prog){
			prog = 0;
			exitMenu();
		} else {
			AUTO = !AUTO;
		}
	}
}
