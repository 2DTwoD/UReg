#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>

#include "init.h"
#include "globals.h"
#include "misc.h"
#include "menu.h"
#include "ledDigits.h"
#include "twoPos.h"
#include "threePos.h"
#include "pid.h"
#include "flash.h"

//����� (0 - 2-�����������, 1 - 3-�����������, 2 - ���)
uint16_t mode = 0;
//�������������� ����� (0 - ����. 1 - ���.)
int8_t AUTO = 0;
//����� �������������� (0 - ����������, 1 - ��������������)
int8_t prog = 0;
//���������� �������� � ���
uint16_t pvRaw = 0;
//����� ��� ���������� �� ���
uint16_t outRaw = 0;
//���������� ��������
double pv = 0.0;
//�������
double sp = 0.0;
//������ �������
Scale scale = {100.0, 0.0};
//������� ������������
Limit limit = {95.0, 90.0, 10.0, 5.0};
//��������� 2-������������ ����������
TwoPosSet twoPosSet = {5.0, 5.0, 0, 0};
//��������� 3-������������ ����������
ThreePosSet threePosSet = {5.0, 1.0, 200, 200, 0, 1, {0, 0}, 0};
//��������� ��� ����������
PIDset pidSet = {1.0, 10.0, 0.0, 0.025, 0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0};

#endif
