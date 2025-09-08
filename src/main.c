/**********************************************************************************************************************
 * 
 * 使用 DHT11 温湿度传感器完成测量，并打印结果到串口；使用 SDCC 工具链编译
 * 
 * ---------------------- 时钟配置 ----------------------
 * 
 * 本例所用时钟频率 16 Mhz，要修改时钟频率，更改宏 CLOCK 的值即可；
 * 注意：CLOCK 的值为：晶振频率/一条指令所需周期数，如 12M 晶振的 stc89c52 单片机，一条指令需要 12 个机器周期，因此：CLOCK=1
 * 
 * ---------------------- 引脚配置 ----------------------
 * 
 * DHT11 DATA 引脚：P11
 * 
 * 串口输出 Tx 引脚：P10
 * 
 * ---------------------- 串口配置 ----------------------
 * 
 * 波特率：9600，位宽度：8，停止位：1
 * 
 * ********************************************************************************************************************
*/

#include "stdio.h"
#include "soft_uart.h"
#include "dht11.h"

void main()
{
    DHT11_Data dhtData;
    DHT11_Init();

    while (1)
    {
        switch (DHT11_Measure(&dhtData))
        {
        case DHT11_CONNECT_ERR:
            printf("connect DHT11 failed !\n");
            break;
        case DHT11_VERIFY_ERR:
            printf("data verify error !\n");
            break;
        default:
            printf("temp: %d, humidity: %d%%\n", (uint8_t)dhtData.temperature, dhtData.humidity);
            break;
        }

        Delay(2000);
    }
}

/* redirect 'int putchar(int c);' function */
int putchar(int c)
{
    TxSend((uint8_t)c);
    return c;
}
