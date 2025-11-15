#define TIM0_CONFIG(x) {TMOD &= 0xF0; TMOD |= (x);} //设置定时器0模式
#define TIM0_GATE_EX 0x08
#define TIM0_COUNT_UP 0x04
#define TIM0_MODE_13 0x00
#define TIM0_MODE_16 0x01
#define TIM0_MODE_8 0x02
#define TIM0_MODE_D 0x03
#define TIM0_LOAD(t) { TL0 = (t)&0xFF; TH0 = (t) >> 8; } //设置定时器0初值，1ms@12.000MHz
#define TIM0_START() { TF0 = 0; TR0 = 1; } //清除溢出标志，并启动定时器0
#define TIM0_STOP() { TR0 = 0; } //停止定时器0

#define TIM1_CONFIG(x) {TMOD &= 0x0F; TMOD |= (x);}
#define TIM1_GATE_EX 0x80
#define TIM1_COUNT_UP 0x40
#define TIM1_MODE_13 0x00
#define TIM1_MODE_16 0x10
#define TIM1_MODE_8 0x20
#define TIM1_MODE_D 0x30
#define TIM1_LOAD(t) { TL1 = (t)&0xFF; TH1 = (t) >> 8; }
#define TIM1_START() { TF1 = 0; TR1 = 1; }
#define TIM1_STOP() { TR1 = 0; }

