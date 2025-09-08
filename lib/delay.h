#ifndef _H_DELAY_
#define _H_DELAY_

#include "stdint.h"

#define _nop_() __asm__("nop\n")

void DelayUs(uint16_t us);

void Delay(uint16_t ms);

#endif
