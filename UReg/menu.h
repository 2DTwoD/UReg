#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>

#include "misc.h"
#include "globals.h"
#include "threePos.h"
#include "pid.h"
#include "menuAux.h"

//��������� � ���� - ��������� ������� ������ �����
void naviUp();
//��������� � ���� - ��������� ������� ������ ����
void naviDown();
//��������� � ���� - ��������� ������� ������ ������
void naviRight();
//��������� � ���� - ��������� ������� ������ �����
void naviLeft();
//�������� ������ ��� 1 ���������� (������� �� ���������� ������ � ����)
char* getDisp1();
//�������� ������ ��� 2 ���������� (������� �� ���������� ������ � ����)
char* getDisp2();
//����� ���� � ��������� ���������
void exitMenu();
//�������� ������� ������� �������
uint8_t getCursor();
#endif
