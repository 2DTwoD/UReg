#ifndef _FLASH_H
#define _FLASH_H

#define FLASH_START_ADDRESS 0x0807F800
#define TOKEN 12321

#include <stdio.h>
#include <stm32f30x.h>
#include <stm32f30x_flash.h>

#include "globals.h"

//Считать параметры из внутренней флэш памяти МК
void readFlash();
//записать параметры во внутреннюю флэш памяти МК
void saveFlash();

#endif
