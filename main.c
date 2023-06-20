#include "main.h"

static uint8_t segment = 0;
static uint8_t field1[4];
static uint8_t field2[4];
static uint8_t blinkCount = 0;
static uint8_t pidCount = 0;
static uint8_t blink = 0;
static onDelay buttonUp = {0, 1, 0, 0};
static onDelay buttonDown = {0, 1, 0, 0};
static onDelay buttonLeft = {0, 1, 0, 0};
static onDelay buttonRight = {0, 1, 0, 0};
static onDelay auxLeft = {0, 120, 0, 0};
static onDelay auxRight = {0, 120, 0, 0};
static onDelay HHdelay = {0, 4, 0, 0};
static onDelay LHdelay = {0, 4, 0, 0};
static onDelay HLdelay = {0, 4, 0, 0};
static onDelay LLdelay = {0, 4, 0, 0};

int main(void)
{
	GPIOinit();
	EXTIinit();
	NVICinit();
	TIMinit();
    while(1);
}

//Цикл 1мс
void TIM3_IRQHandler(void){
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	switch(mode){
	case 0:
		calculateTwoPosOut();
		changeDO(GPIOC, 0x10, twoPosSet.out << 4);
		break;
	case 1:
		setThreePosCurrentTime();
		calculateThreePosOut();
		changeDO(GPIOC, 0x30, threePosSet.out.out1 << 4 | threePosSet.out.out2 << 5);
		break;
	default:
		pidCount++;
		if(pidCount > 25){
			pidCount = 0;
			calculatePIDout();
		}
		break;
	}
}

//Цикл 25мс
void TIM4_IRQHandler(void){
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

	HHdelay.start = pv > limit.hh;
	LHdelay.start = pv > limit.lh;
	HLdelay.start = pv < limit.hl;
	LLdelay.start = pv < limit.ll;

	timerUpdater(&buttonUp);
	timerUpdater(&buttonDown);
	timerUpdater(&buttonLeft);
	timerUpdater(&buttonRight);
	timerUpdater(&auxLeft);
	timerUpdater(&auxRight);
	timerUpdater(&HHdelay);
	timerUpdater(&LHdelay);
	timerUpdater(&HLdelay);
	timerUpdater(&LLdelay);

	changeDO(GPIOC, 0xF, HHdelay.finish | LHdelay.finish << 1 | HLdelay.finish << 2 | LLdelay.finish << 3);
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
		blink = 0;
		blinkCount = 0;
	}
	if(buttonLeft.finish && !auxLeft.finish && !(GPIOA->IDR & GPIO_Pin_8)){
		naviLeft();
		blink = 0;
		blinkCount = 0;
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
