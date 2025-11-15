#include <reg51.h>

void DelayMS(unsigned int ms) {
    // 粗略延时，Keil编译器下可用
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++) {
            ; // 约1ms@11.0592MHz，近似即可
        }
    }
}


#define COMMON_CATHODE 1  // P0接共阴数码管：1；若是共阳，改为0
// 共阴数码管段码(0~9): a b c d e f g dp
unsigned char __code SEG_CC[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};
void DisplayDigit(unsigned char ch) {
    unsigned char seg;

    if (ch >= '0' && ch <= '9') {
        seg = SEG_CC[ch - '0'];
#if COMMON_CATHODE
        P0 = seg;           // 共阴：段码直接输出
#else
        P0 = ~seg;          // 共阳：段码取反输出
#endif
    } else {
        // 非数字字符：原样输出到P0，便于调试（可能不是有效段码）
        P0 = ch;
    }
}


void UART_Init(void) {
    SCON = 0x50;        // 串口方式1，8位UART，允许接收(虽不接收也无妨)
    TMOD |= 0x20;       // T1方式2，8位自动重装
    TH1 = 0xFD;         // 9600bps@11.0592MHz
    TL1 = 0xFD;
    TR1 = 1;            // 启动T1
    ES = 0;             // 关闭串口中断（轮询发送）
    EA = 1;             // 开总中断（可选）
}

void UART_SendByte(unsigned char dat) {
    SBUF = dat;
    while (!TI);
    TI = 0;
}

// 串口中断服务程序
void UART_ISR(void) __interrupt(4) {
    unsigned char dat;

    if (RI) {
        RI = 0;             // 清接收中断标志
        dat = SBUF;         // 读缓冲
        DisplayDigit(dat);  // 逐个显示接收的数据
    }
    if (TI) {
        TI = 0;             // 清发送中断标志（防误触发）
    }
}


void main(void) {
#if COMMON_CATHODE
    P0 = 0x00;              // 共阴默认灭
#else
    P0 = 0xFF;              // 共阳默认灭
#endif
    unsigned char i;
    const unsigned char tx[10] = { '0','1','2','3','4','5','6','7','8','9' };

    UART_Init();

    // 持续循环发送10个数据，便于观察接收端逐个显示
    while (1) {
        for (i = 0; i < 10; i++) {
            UART_SendByte(tx[i]);   // 轮询发送
            DelayMS(300);           // 发送间隔，便于观察显示
        }
        DelayMS(800);               // 每轮结束停顿
    }

    // 如需只发送一次，把while(1)去掉，直接执行for循环即可
}

