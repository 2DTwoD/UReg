#ifndef _MISC_H
#define _MISC_H

#include <stm32f30x.h>

#include "globals.h"
#include "twoPos.h"
#include "threePos.h"
#include "pid.h"

void resetRegulators();

void timerUpdater(onDelay* timer);

void changeDO(GPIO_TypeDef* gpio, uint16_t mask, uint16_t value);

#endif
