#ifndef _FLASH_H
#define _FLASH_H
//����� ��������� 2�� ���� ������
#define FLASH_START_ADDRESS 0x0803E800//0x0803F7FF
#define TOKEN 12321

#include <stdio.h>
#include <math.h>
#include <stm32f30x.h>
#include <stm32f30x_flash.h>

#include "globals.h"

//������� ��������� �� ���������� ���� ������ ��
void readFlash();
//�������� ��������� �� ���������� ���� ������ ��
void saveFlash();

#endif
