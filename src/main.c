#include "mcs51/8051.h"

void main()
{
    while (1)
    {
        unsigned char temp;             // 定义临时变量
        P2 = 0xff;                      // P2 口初始化高电平
        temp = P2 & 0xf0;               // 读取 P2 口高四位，低四位为零
        // TODO: Keil C51 在定义位变量时，把 ^ 操作符作为“取第几位”操作符，参见<reg51.h>
        __bit temp7, temp6, temp5, temp4 = 0; // 临时存储
        temp7 = (temp >> 7) & 0x01;
        temp6 = (temp >> 6) & 0x01;
        temp5 = (temp >> 5) & 0x01;
        temp4 = (temp >> 4) & 0x01;
        temp |= (temp7 << 0);      // 
        temp |= (temp6 << 1);      // 
        temp |= (temp5 << 2);      // 
        temp |= (temp4 << 3);      //
        P2 = temp;
    }
}