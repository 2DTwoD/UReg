#include "init.h"

void GPIOinit(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

	GPIO_InitTypeDef gpioStruct;
	//a8-a15 2x common cathode
	gpioStruct.GPIO_Pin = 0xFF00;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &gpioStruct);

	//d0-d15 2x 7 seg led
	gpioStruct.GPIO_Pin = 0xFFFF;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &gpioStruct);
}

void NVICinit(){
	NVIC_InitTypeDef nvicStruct;
	nvicStruct.NVIC_IRQChannel = TIM7_IRQn;
	nvicStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStruct.NVIC_IRQChannelSubPriority = 0;
	nvicStruct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&nvicStruct);
}

void TIMinit(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	TIM_TimeBaseInitTypeDef timStruct;
	timStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timStruct.TIM_Prescaler = 36000;
	timStruct.TIM_Period = 20;
	TIM_TimeBaseInit(TIM7, &timStruct);

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, ENABLE);
}
