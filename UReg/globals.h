#ifndef _GLOBALS_H
#define _GLOBALS_H
#include <stdio.h>

//Глобальные структуры
//Таймер задержки вкючения
typedef struct{
	uint8_t start;
	uint8_t delay;
	uint8_t currentTime;
	uint8_t finish;
} onDelay;
//Параметры шкалирования
typedef struct{
	double up;
	double down;
} Scale;
//Параметры пределов для предупреждений
typedef struct{
	double hh;
	double lh;
	double hl;
	double ll;
} Limit;
//Параметры двупозиционнного регулятора
typedef struct{
	double up_indent;
	double down_indent;
	uint16_t inverse;
	uint8_t out;
} TwoPosSet;
//Выход трехпозиционного регулятора
typedef struct{
	uint8_t out1;
	uint8_t out2;
} ThreePosOut;
//Параметры трехпозиционного регулятора
typedef struct{
	double treshold;
	double deadband;
	uint16_t waitTime;
	uint16_t pulseTime;
	uint16_t currentTime;
	uint16_t inverse;
	ThreePosOut out;
	uint8_t pulseFlag;
} ThreePosSet;
//Параметры ПИД регулятора
typedef struct {
	double kp;
	double ti;
	double td;
	double t;
	double db;
	double out;
	double upOutLim;
	double downOutLim;
	double e0;
	double e1;
	double e2;
	double q0;
	double q1;
	double q2;
	uint16_t inverse;
} PIDset;

#endif
