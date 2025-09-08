#ifndef _H_DHT11
#define _H_DHT11

#include <stdint.h>

/**
 * Interface define
*/

#include "mcs51/8051.h"
#include "delay.h"

#define DATA_WRITE(val) P1_1 = (val)
#define DATA_READ() P1_1

#define _Delay(ms) Delay(ms)

//=========================================

// ∑µªÿ÷µ∫¨“Â
#define DHT11_DONE 0
#define DHT11_CONNECT_ERR 1
#define DHT11_VERIFY_ERR 2

typedef struct
{
    uint8_t humidity;
    float temperature;
} DHT11_Data;

#define DHT11_Init() DATA_WRITE(1)

uint8_t DHT11_Measure(DHT11_Data *dat);

#endif

