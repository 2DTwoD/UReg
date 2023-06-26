#ifndef _MISC_H
#define _MISC_H

//����� �������� ��� ���������� (1-256)
#define MAX_AVG_NUM 200

#include <stm32f30x.h>

#include "globals.h"
#include "twoPos.h"
#include "threePos.h"
#include "pid.h"

//����� ���� �����������
void resetRegulators();
//�������� ����������� �������� � ���
uint16_t getAvgRawPv();
//������� ���������� ��������� �������
void timerUpdater(onDelay* timer);
//�������� ��������� ����� ������
void changeDO(GPIO_TypeDef* gpio, uint16_t mask, uint16_t value);

#endif
