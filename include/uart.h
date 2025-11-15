#define RX_ENABLED_UART0 REN
#define RX_FILTERED_UART0 SM2
#define UART0_CONFIG(x) {SCON &= ~0x00; SCON |= (x);}
#define UART0_MODE_8 0x00
#define UART0_MODE_8V 0x40
#define UART0_MODE_9 0x80
#define UART0_MODE_9V 0xC0
#define UART0_BAUD() {PCON &= ~0x80;}
#define UART0_DUAL_BAUD() {PCON |= 0x80;}

// 11059200L
// 方式1和方式3的波特率都利用定时器T1工作于定时方式2并装载适当的时间常数来获得
#define BAUD_TO_LOAD(freq, baud) (256 - (freq / 32 / (baud)))
#define LOAD_TO_BAUD(freq, load) (freq / 32 / (256 - (load)))