
# MCS51 例程

> 本例程使用 SDCC 工具链编译

使用 DHT11 温湿度传感器完成测量，并打印结果到串口

波特率：9600，位宽度：8，停止位：1

## 引脚配置

 - DHT11 DATA 引脚：P11
 - 串口输出 Tx 引脚：P10

## 时钟配置

 - 本例所用时钟频率 16 Mhz，要修改时钟频率，更改宏 CLOCK 的值即可；
 - 注意：CLOCK 的值为：`晶振频率/一条指令所需周期数`，如 12M 晶振的 stc89c52 单片机，一条指令需要 12 个机器周期，因此：CLOCK=1

## FLASH 和 RAM 大小设置

打开 构建器选项 -> Other Global Options 可以看到如下配置

请根据你使用的芯片型号修改 `--xram-size` 和 `--code-size` 参数，单位为字节

默认 FLASH 为 8KB，无 XRAM

```txt
--iram-size 256 --xram-size 0 --code-size 8192
```

## 烧录程序

烧录工具可使用厂家提供的工具，比如 STCISP.exe

要使用插件的烧录功能，需要在本机上安装 python 以及 stcgal 软件包

# 89C52 例程

89C52 的点灯例程，使用 SDCC 编译器进行编译

```c
#include <reg52.h>
#include <stdio.h>

void delay_100ms(void) //@12MHz
{
    unsigned char i, j;

    i = 195;
    j = 138;

    do
    {
        while (--j)
            ;
    } while (--i);
}

void main(void)
{
    while (1)
    {
        P00 = !P00;
        delay_100ms();
    }
}
```

## SDCC 编译设置

默认设置：`--iram-size 256 --xram-size 0 --code-size 8192`，对应参数如下：

- IRAM  SIZE: 256  Bytes
- XRAM  SIZE: 0    Bytes
- FLASH SIZE: 8192 Bytes

要修改上述参数，请到 `构建器选项 -> Other Global Options` 中进行修改。
