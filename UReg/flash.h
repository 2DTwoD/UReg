#ifndef _FLASH_H
#define _FLASH_H
//Адрес последних 2кБ флэш памяти
#define FLASH_START_ADDRESS 0x0803E800//0x0803F7FF
#define TOKEN 12321

#include <stdio.h>
#include <math.h>
#include <stm32f30x.h>
#include <stm32f30x_flash.h>

#include "globals.h"

//Считать параметры из внутренней флэш памяти МК
void readFlash();
//записать параметры во внутреннюю флэш памяти МК
void saveFlash();

#endif
