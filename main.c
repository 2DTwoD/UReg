#include "main.h"

static uint8_t segment = 0;
static uint8_t field1[4];
static uint8_t field2[4];
static uint8_t blinkCount = 0;
static uint8_t pidCount = 0;
static uint16_t saveCount = 0;
static uint8_t blink = 0;
static uint8_t percPv = 0;
static uint8_t prevAUTO;
static double prevSP;
//Таймеры
static onDelay buttonUp = {0, 2, 0, 0};
static onDelay buttonDown = {0, 2, 0, 0};
static onDelay buttonLeft = {0, 2, 0, 0};
static onDelay buttonRight = {0, 2, 0, 0};
static onDelay auxLeft = {0, 80, 0, 0};
static onDelay auxRight = {0, 80, 0, 0};
static onDelay HHdelay = {0, 4, 0, 0};
static onDelay LHdelay = {0, 4, 0, 0};
static onDelay HLdelay = {0, 4, 0, 0};
static onDelay LLdelay = {0, 4, 0, 0};
int tmp = 0;

int main(void)
{
	
	prevAUTO = AUTO;
	prevSP = sp;

	//Настройка МК
	RCCinit();
	GPIOinit();
	EXTIinit();
	NVICinit();
	TIMinit();
	ADCinit();
	DMAinit();
	PWMinit();

	//Считывание внутренней флэш памяти
	readFlash();
	//Сброс регуляторов
	resetRegulators();
	updatePID();

    while(1);
}
//Цикл 1мс
void TIM3_IRQHandler(){
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	if(tmp < 1000){
		tmp++;
	} else {
		GPIOE->ODR ^= 0x200;
		tmp = 0;
	}
	//Расчет сигнала с датчика с учетом пределов шкалирования
	pv = getAvgRawPv() * (scale.up - scale.down) / 4095.0 + scale.down;
	//Расчет выхода регулятора в зависимости от выбранного режима
	switch(mode){
	case 0:
		//Расчет выхода двупозиционного регулятора
		calculateTwoPosOut();
		changeDO(GPIOC, 0x10, twoPosSet.out << 4);
		changeDO(GPIOE, 0x400, twoPosSet.out << 10);
		break;
	case 1:
		//Расчет выхода трехпозиционного регулятора
		calculateThreePosOut();
		changeDO(GPIOC, 0x30, threePosSet.out.out1 << 4 | threePosSet.out.out2 << 5);
		changeDO(GPIOE, 0xC00, threePosSet.out.out1 << 10 | threePosSet.out.out2 << 11);
		break;
	default:
		//Расчет выхода ПИД регулятора
		pidCount++;
		if(pidCount > 50){
			pidCount = 0;
			updatePID();
			calculatePIDout();
			outRaw = pidSet.out * 10;
		}
		break;
	}
}

//Цикл 25мс
void TIM4_IRQHandler(){
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	//Расчет сигнала с датчика в процентах
	percPv = (pv - scale.down) * 100 / (scale.up - scale.down);
	//Условия срабатывания сигналов предупреждения
	HHdelay.start = (percPv > limit.hh);
	LHdelay.start = (percPv > limit.lh);
	HLdelay.start = (percPv < limit.hl);
	LLdelay.start = (percPv < limit.ll);
	//Обновление таймеров для кнопок и пределов предупреждения
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
	//1 раз в 5 минут проверять было ли изменеие уставки или режима работы,при наличии изменения сохранение на внутреннюю флэш память
	if(saveCount < 12000){
		saveCount ++;
	} else {
		if(sp != prevSP || AUTO != prevAUTO){
			prevAUTO = AUTO;
			prevSP = sp;
			//saveFlash();
		}
		saveCount = 0;
	}
	//Обновление дискретных выходов
	changeDO(GPIOE, 0x100, AUTO << 8);
	changeDO(GPIOE, 0xF000, HHdelay.finish << 12 | LHdelay.finish << 13 | HLdelay.finish << 14 | LLdelay.finish << 15);
	changeDO(GPIOC, 0xF, HHdelay.finish | LHdelay.finish << 1 | HLdelay.finish << 2 | LLdelay.finish << 3);
}

//Цикл 2.5мс для семисегментного индикатора
void TIM7_IRQHandler(){
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	//Переключение "маркера" мигания выбранного разряда числа
	if(blinkCount < 60){
		blinkCount++;
	} else {
		blinkCount = 0;
		blink = !blink;
	}
	//Расчет кодов семисегментного индиктора
	if(segment == 0){
		getLEDcodeArray(field1, getDisp1());
		getLEDcodeArray(field2, getDisp2());
	}
	//Динамическая индикация семисегментного индикатора
	GPIOD->ODR = field1[segment] | field2[segment] << 8;
	GPIOB->ODR &= 0xFF;
	GPIOB->ODR |= 1 << (8 + segment) | (segment != getCursor() || blink) << (12 + segment);
	segment ++;
	if(segment > 3){
		segment = 0;
	}
}

//Прерывания для кнопок
void EXTI9_5_IRQHandler(){
	EXTI_ClearFlag(EXTI_Line5);
	EXTI_ClearFlag(EXTI_Line6);
	EXTI_ClearFlag(EXTI_Line7);
	EXTI_ClearFlag(EXTI_Line8);
	//Старт таймеров задержки кнопок (антидребезг)
	buttonUp.start = GPIOA->IDR & GPIO_Pin_5 && 1;
	buttonDown.start = GPIOA->IDR & GPIO_Pin_6 && 1;
	buttonRight.start = GPIOA->IDR & GPIO_Pin_7 && 1;
	buttonLeft.start = GPIOA->IDR & GPIO_Pin_8 && 1;
	auxRight.start = GPIOA->IDR & GPIO_Pin_7 && 1;
	auxLeft.start = GPIOA->IDR & GPIO_Pin_8 && 1;
	//Действия при отпускании кнопок с учетом таймеров антидребезга
	if(buttonUp.finish && !(GPIOA->IDR & GPIO_Pin_5)){
		naviUp();
		buttonUp.finish = 0;
	}
	if(buttonDown.finish && !(GPIOA->IDR & GPIO_Pin_6)){
		naviDown();
		buttonDown.finish = 0;
	}
	if(auxRight.finish && !(GPIOA->IDR & GPIO_Pin_7)){
		prog = 1;
		auxRight.finish = 0;
		buttonRight.finish = 0;
	}
	if(auxLeft.finish && !(GPIOA->IDR & GPIO_Pin_8)){
		if(prog){
			prog = 0;
			//saveFlash();
			exitMenu();
		} else {
			AUTO = !AUTO;
		}
		auxLeft.finish = 0;
		buttonLeft.finish = 0;
	}
	if(buttonRight.finish && !(GPIOA->IDR & GPIO_Pin_7)){
		naviRight();
		buttonRight.finish = 0;
		blink = 0;
		blinkCount = 0;
	}
	if(buttonLeft.finish && !(GPIOA->IDR & GPIO_Pin_8)){
		naviLeft();
		buttonLeft.finish = 0;
		blink = 0;
		blinkCount = 0;
	}
}
