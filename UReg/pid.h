#ifndef _PID_H
#define _PID_H
#include <stdio.h>
#include <math.h>
#include "globals.h"

//����� ������ ���������� � 0
void resetPID();
//���������� ������������� ����������
void updatePID();
//������ ������ ����������
void calculatePIDout();

#endif
