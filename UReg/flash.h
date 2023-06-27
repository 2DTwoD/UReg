#ifndef _FLASH_H
#define _FLASH_H
//Начальный адрес флэш для записи
#define FLASH_START_ADDRESS 0x0803E800
#define TOKEN 12321

#include <stdio.h>
#include <math.h>
#include <stm32f30x.h>
#include <stm32f30x_flash.h>

#include "globals.h"

//Чтение внутренней флэш памяти
void readFlash();
//Запись во внутреннюю флэш память
void saveFlash();

#endif
