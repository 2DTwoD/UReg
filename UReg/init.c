#include "init.h"

extern uint16_t pvRaw;
extern uint16_t outRaw;

//AHB - 64MHz, APB1 - 32MHz, APB2 - 64MHz
void RCCinit(){
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);
	RCC_PLLCmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
}

void GPIOinit(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitTypeDef gpioStruct;

	//a1 АЦП AI
	gpioStruct.GPIO_Pin = GPIO_Pin_1;
	gpioStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOA, &gpioStruct);

	//a5-a8 кнопки управления в меню
	gpioStruct.GPIO_Pin = 0x1E0;
	gpioStruct.GPIO_Mode = GPIO_Mode_IN;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_2;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &gpioStruct);

	//a9 ШИМ AO
	gpioStruct.GPIO_Pin = GPIO_Pin_9;
	gpioStruct.GPIO_Mode = GPIO_Mode_AF;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &gpioStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_6);

	//b8-b15 семисегментный индикатор, общий катод
	gpioStruct.GPIO_Pin = 0xFF00;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &gpioStruct);

	//d0-d15 2x семисегментный индикатор, аноды
	gpioStruct.GPIO_Pin = 0xFFFF;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &gpioStruct);

	//c0-c5 дискретные выходы, пределы предупреждений и выход регулятора 1/2 DO
	gpioStruct.GPIO_Pin = 0x3F;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_Speed = GPIO_Speed_Level_1;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &gpioStruct);

	//e8-e15 индикация на плате
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	TIM_TimeBaseInitTypeDef timStruct;
	//Таймер для ШИМ
	timStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timStruct.TIM_Prescaler = 32;
	timStruct.TIM_Period = 1000;
	TIM_TimeBaseInit(TIM1, &timStruct);
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	//Цикл 1 мс
	timStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timStruct.TIM_Prescaler = 8000;
	timStruct.TIM_Period = 4;
	timStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &timStruct);
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//Цикл 25 мс
	timStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timStruct.TIM_Prescaler = 8000;
	timStruct.TIM_Period = 100;
	timStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &timStruct);
	TIM_Cmd(TIM4, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//Цикл 2.5 мс
	timStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timStruct.TIM_Prescaler = 8000;
	timStruct.TIM_Period = 10;
	TIM_TimeBaseInit(TIM7, &timStruct);
	TIM_Cmd(TIM7, ENABLE);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
}

void ADCinit(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
	RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div6);

	ADC_InitTypeDef adcStruct;
	ADC_CommonInitTypeDef adcComStruct;

	adcComStruct.ADC_Mode = ADC_Mode_Independent;
	adcComStruct.ADC_Clock = ADC_Clock_AsynClkMode;
	adcComStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
	adcComStruct.ADC_DMAMode = ADC_DMAMode_Circular;
	adcComStruct.ADC_TwoSamplingDelay = 0;
	ADC_CommonInit(ADC1, &adcComStruct);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);

	adcStruct.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	adcStruct.ADC_Resolution = ADC_Resolution_12b;
	adcStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
	adcStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
	adcStruct.ADC_DataAlign = ADC_DataAlign_Right;
	adcStruct.ADC_OverrunMode = ADC_OverrunMode_Disable;
	adcStruct.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	adcStruct.ADC_NbrOfRegChannel = 1;

	ADC_Init(ADC1, &adcStruct);

	ADC_Cmd(ADC1, ENABLE);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_7Cycles5);
	NVIC_EnableIRQ(ADC1_2_IRQn);
	ADC_StartConversion(ADC1);
}

void DMAinit(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_InitTypeDef dmaStruct;

	dmaStruct.DMA_PeripheralBaseAddr = (uint32_t) &(ADC1->DR);
	dmaStruct.DMA_MemoryBaseAddr = (uint32_t) &pvRaw;
	dmaStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	dmaStruct.DMA_BufferSize = 1;
	dmaStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	dmaStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dmaStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dmaStruct.DMA_Mode = DMA_Mode_Circular;
	dmaStruct.DMA_Priority = DMA_Priority_High;
	dmaStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &dmaStruct);

	dmaStruct.DMA_PeripheralBaseAddr = (uint32_t) &outRaw;
	dmaStruct.DMA_MemoryBaseAddr = (uint32_t) &(TIM1->CCR2);
	dmaStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	dmaStruct.DMA_BufferSize = 1;
	dmaStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	dmaStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dmaStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dmaStruct.DMA_Mode = DMA_Mode_Circular;
	dmaStruct.DMA_Priority = DMA_Priority_High;
	dmaStruct.DMA_M2M = DMA_M2M_Enable;
	DMA_Init(DMA1_Channel3, &dmaStruct);

	DMA_Cmd(DMA1_Channel1, ENABLE);
	DMA_Cmd(DMA1_Channel3, ENABLE);
}

void PWMinit(){
	TIM_OCInitTypeDef pwmStruct;
	pwmStruct.TIM_Pulse = 1000;
	pwmStruct.TIM_OCMode = TIM_OCMode_PWM1;
	pwmStruct.TIM_OutputState = TIM_OutputState_Enable;
	pwmStruct.TIM_OutputNState = TIM_OutputNState_Enable;
	pwmStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	pwmStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	pwmStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
	pwmStruct.TIM_OCNIdleState = TIM_OCNIdleState_Set;
	TIM_OC2Init(TIM1, &pwmStruct);
}
