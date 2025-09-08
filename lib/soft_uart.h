#ifndef _H_SOFT_UART
#define _H_SOFT_UART

/**
 * 波特率：9600，位宽度：8，停止位：1
*/

#include "stdint.h"
#include "mcs51/8051.h"

#define P_TXD P1_0 //定义模拟串口发送端,可以是任意IO

void TxSend(uint8_t dat);

#endif
