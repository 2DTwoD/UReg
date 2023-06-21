#include "init.h"

void GPIOinit(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitTypeDef gpioStruct;

	// a5-a8 buttons
	gpioStruct.GPIO_Pin = 0x1E0;
	gpioStruct.GPIO_Mode = GPIO_Mode_IN;
	gpioStruct.GPIO_Speed = GPIO_Speed_2MHz;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &gpioStruct);

	//b8-b15 2x common cathode
	gpioStruct.GPIO_Pin = 0xFF00;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &gpioStruct);

	//c0-c5 limits and out1/2 DO
	gpioStruct.GPIO_Pin = 0x3F;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &gpioStruct);

	//d0-d15 2x 7 segment led
	gpioStruct.GPIO_Pin = 0xFFFF;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &gpioStruct);

	//indicators
	gpioStruct.GPIO_Pin = 0xFF00;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &gpioStruct);
}

void EXTIinit(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource7);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);

	EXTI_InitTypeDef extiStruct;

	extiStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	extiStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	extiStruct.EXTI_LineCmd = ENABLE;
	extiStruct.EXTI_Line = EXTI_Line5;
	EXTI_Init(&extiStruct);
	extiStruct.EXTI_Line = EXTI_Line6;
	EXTI_Init(&extiStruct);
	extiStruct.EXTI_Line = EXTI_Line7;
	EXTI_Init(&extiStruct);
	extiStruct.EXTI_Line = EXTI_Line8;
	EXTI_Init(&extiStruct);
}

void NVICinit(){
	NVIC_InitTypeDef nvicStruct;

	nvicStruct.NVIC_IRQChannel = TIM3_IRQn;
	nvicStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStruct.NVIC_IRQChannelSubPriority = 0;
	nvicStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStruct);

	nvicStruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStruct.NVIC_IRQChannelSubPriority = 3;
	nvicStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStruct);

	nvicStruct.NVIC_IRQChannel = TIM7_IRQn;
	nvicStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStruct.NVIC_IRQChannelSubPriority = 2;
	nvicStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStruct);

	nvicStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvicStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStruct.NVIC_IRQChannelSubPriority = 1;
	nvicStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStruct);
}

void TIMinit(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	TIM_TimeBaseInitTypeDef timStruct;

	timStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timStruct.TIM_Prescaler = 36000;
	timStruct.TIM_Period = 2;
	timStruct.TIM_ClockDivision = 1;
	TIM_TimeBaseInit(TIM3, &timStruct);
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	timStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timStruct.TIM_Prescaler = 36000;
	timStruct.TIM_Period = 50;
	timStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &timStruct);
	TIM_Cmd(TIM4, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	timStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timStruct.TIM_Prescaler = 36000;
	timStruct.TIM_Period = 5;
	TIM_TimeBaseInit(TIM7, &timStruct);
	TIM_Cmd(TIM7, ENABLE);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

}
