#ifndef _HAL_UART_H_ //头文件防止重加载必备，先看看有没有定义过这个，定义说明已经加载过一次了。
#define _HAL_UART_H_ //没定义说明是首次加载，那么往下执行。并且定义这个宏定义，防止下一次被加载。
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2022 奈特

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

免责说明：
    本软件库以MIT开源协议免费向大众提供。作者只保证原始版本是由作者在维护修BUG，
其他通过网络传播的版本也许被二次修改过，由此出现的BUG与作者无关。而当您使用原始
版本出现BUG时，请联系作者解决。
                            **************************
                            * 联系方式：进群778916610 *
                            * 若1群满人：进群927297508*
                            **************************
------------------------------------------------------------------------------------*///这是开源协议，下面是图形界面选项。
//-----------------以下是图形设置界面，可在Configuration Wizard界面设置-----------------
//<<< Use Configuration Wizard in Context Menu >>>
//<h>HAL层设置
//<e>串口1函数库使能
//<i>使能该设置，即可让IDE编译和串口1有关的代码。
//<i>不使能该设置，即可不编译相关代码，从而减小代码占用空间大小。
#define ECBM_UART1_LIB_EN 1
//<q>接收使能
#define ECBM_UART1_RXD_EN 1
//<h>波特率选择列表
//<i>鉴于本页面不是动态的，所以只能把所有情况都列出来，请到对应的晶振参数下选择波特率。
//<o>5.5296MHz
//<1200=>1200 <2400=>2400 <4800=>4800 <9600=>9600 
//<o>6.000MHz
//<1200=>1200 <2400=>2400
//<o>11.0592MHz
//<1200=>1200 <2400=>2400 <4800=>4800 <9600=>9600 <19200=>19200 <57600=>57600
//<o>12.000MHz
//<1200=>1200 <2400=>2400 <4800=>4800
//<o>18.432MHz
//<1200=>1200 <2400=>2400 <4800=>4800 <9600=>9600 <19200=>19200
//<o>20.000MHz
//<1200=>1200 <2400=>2400 
//<o>24.000MHz
//<1200=>1200 <2400=>2400 <4800=>4800 <9600=>9600 
//<o>27.000MHz
//<1200=>1200 <2400=>2400
//<o>30.000MHz
//<1200=>1200 <2400=>2400
//<o>33.000MHz
//<1200=>1200 <2400=>2400 <4800=>4800 <9600=>9600 <19200=>19200 <57600=>57600
//<o>33.1776MHz
//<1200=>1200 <2400=>2400 <4800=>4800 <9600=>9600 <19200=>19200 <57600=>57600
//<o>35.000MHz
//<1200=>1200 <2400=>2400 <4800=>4800 <9600=>9600
#define ECBM_UART1_BAUD 4800
//</h>
//<o>通信模式
//<i>一般用到8位，只有需要校验位的时候才会用到第9位。
//<0=>同步移位通信 
//<1=>可变波特率8位通信 
//<2=>固定波特率9位通信 
//<3=>可变波特率9位通信
#define ECBM_UART1_RUN_MODE 1
//<o>校验方式
//<i>只要是用了校验，无论用的是哪种都需要把通信模式改成9位的同步/异步通信。
//<0=>不校验  
//<1=>奇校验  
//<2=>偶校验  
//<3=>1校验  
//<4=>0校验  
//<5=>自定义  
#define ECBM_UART1_CHECK_MODE 0
//<q>中断使能
#define ECBM_UART1_IT_EN  0
//<o>中断优先级
//<i>在同时触发中断的时候，高优先级中断的函数总会比低优先级中断的函数先执行。
//<0=>低优先级
//<1=>高优先级
#define ECBM_UART1_IT_PRIORITY 0
//<q>串口1发送回调函数
#define ECBM_UART1_FUN_SEND_CALLBACK_EN 0
//<q>串口1接收回调函数
#define ECBM_UART1_FUN_RECEIVE_CALLBACK_EN 0
//</e>
//</h>
//<e>RS485控制
//<i>使能的话就开启485控制功能，默认是控制脚同时连接DE和RE。
#define ECBM_UART_RS485_EN 0
//<h>串口1控制脚定义
//<o.3..7>Port
//<i>和下面的选项组合成一个完整的IO，比如P5.5。
//<0x10=>P0 
//<0x12=>P1 
//<0x14=>P2 
//<0x16=>P3 
//<o.0..2>Pin
//<i>和上面的选项组合成一个完整的IO，比如P5.5。
//<0=>__.0
//<1=>__.1 
//<2=>__.2 
//<3=>__.3 
//<4=>__.4 
//<5=>__.5 
//<6=>__.6 
//<7=>__.7
#define ECBM_UART1_RS485_IO 0x91
//</h>
//</e>
//<h>函数优化
//<i>对于一些使用率不高的函数，可以进行精简优化。
//<q>uart_deinit
//<i>如果整个应用中，初始化之后就没必要再改设置，那么这个函数可以不要。
#define ECBM_UART_FUN_DEINIT_EN 0
//<q>uart_get_configuration_wizard
//<i>如果整个应用中，不需要图形化配置界面提供的信息，那么这个函数可以不要。
#define ECBM_UART_FUN_CONFIG_WIZARD_EN 1
//<q>uart_config_baud
//<i>如果整个应用中，不需要函数来计算波特率和初值，那么这个函数可以不要。
//<i>但是要注意：uart_config和uart_get_configuration_wizard都调用了这个函数。
//<i>关闭这个函数，就会导致那两个函数也关闭！
#define ECBM_UART_FUN_CONFIG_BAUD_EN 1
//<q>uart_config
//<i>假如串口参数明确且不会变动，那么也可以不要配置函数，直接填入参数即可。
#define ECBM_UART_FUN_CONFIG_EN 1
//<q>uart1_it_fun
//<i>本库中已经提前写好了串口中断函数，但要是从来都没用到中断，可以将其优化掉。
//<i>不过要注意优化之后，中断回调函数也会失效。
#define ECBM_UART_FUN_IT_EN 1
//</h>
//<h>功能优化
//<i>对于一些使用率不高的功能，可以进行精简优化。
//<q>校验功能
//<i>串口一般都有一位校验位来验证数据传输是否正确，但简单的工程应用中往往不需要，在这可以优化掉以节省出大量空间。
#define ECBM_UART_FUN_CHECK_EN 0
//</h>
//<<< end of configuration section >>>
//-----------------以上是图形设置界面，可在Configuration Wizard界面设置-----------------
/*---------------------------------------头文件------------------------------------*/
#include "hal_config.h" //库的头文件。
/*--------------------------------------结构体定义---------------------------------*/
typedef struct {
    u8  id:3;           //串口编号。目前只能为1。
    u8  it_enable:1;    //串口中断使能，0为关闭，1为开启。
    u8  it_priority:1;  //串口中断优先级，0为低优先级，1为高优先级。
    u8  rxd_enable:1;   //串口接收使能，0为关闭，1为开启。
    u8  baud_mul:1;     //串口波特率倍数，0为不加倍，1为波特率加倍。
    u8  run_mode:2;     //串口工作模式，0为8位同步，1为8位异步，2为9位同步，3为9位异步。
    u8  check_mode:3;   //串口检验方式，0为不检验，1为奇校验，2为偶检验，3为1校验，4为0校验，5为自定义校验。
    u16 init_value;     //生成波特率的定时器初值，填写0~65535，亦可用软件计算。
}uart_typedef;
/*---------------------------------------枚举定义----------------------------------*/
typedef enum{
    UART_OK=0,          //串口操作正常。
    UART_ID_ERR,        //串口编号错误。
    UART_BAUD_ERR,      //波特率错误。
    UART_CHECK_ERR      //校验错误
}uart_status;

typedef enum{
    UART_CHECK_NONE=0,  //不校验
    UART_CHECK_ODD,     //奇检验
    UART_CHECK_EVEV,    //偶校验
    UART_CHECK_ONE,     //1校验
    UART_CHECK_ZERO,    //0校验
    UART_CHECK_USER     //用户手动装填第九位
}uart_check_def;

typedef enum{
#if   ECBM_SYSCLK_SETTING == 5529600L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
    uart_baud_4800=4800,
    uart_baud_9600=9600,
#elif ECBM_SYSCLK_SETTING == 6000000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
#elif ECBM_SYSCLK_SETTING == 11059200L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
    uart_baud_4800=4800,
    uart_baud_9600=9600,
    uart_baud_19200=19200,
    uart_baud_57600=57600,
#elif ECBM_SYSCLK_SETTING == 12000000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
    uart_baud_4800=4800,
#elif ECBM_SYSCLK_SETTING == 18432000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
    uart_baud_4800=4800,
    uart_baud_9600=9600,
    uart_baud_19200=19200,
#elif ECBM_SYSCLK_SETTING == 20000000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
#elif ECBM_SYSCLK_SETTING == 22118400L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
	uart_baud_4800=4800,
	uart_baud_9600=9600,
	uart_baud_19200=19200,
	uart_baud_38400=38400,
	uart_baud_57600=57600,
	uart_baud_115200=115200,
#elif ECBM_SYSCLK_SETTING == 24000000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
    uart_baud_4800=4800,
    uart_baud_9600=9600,
#elif ECBM_SYSCLK_SETTING == 27000000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
#elif ECBM_SYSCLK_SETTING == 30000000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
#elif ECBM_SYSCLK_SETTING == 33000000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
    uart_baud_4800=4800,
    uart_baud_9600=9600,
    uart_baud_19200=19200,
    uart_baud_57600=57600,
#elif ECBM_SYSCLK_SETTING == 33177600L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
    uart_baud_4800=4800,
    uart_baud_9600=9600,
    uart_baud_19200=19200,
    uart_baud_57600=57600,
#elif ECBM_SYSCLK_SETTING == 35000000L
    uart_baud_1200=1200,
    uart_baud_2400=2400,
    uart_baud_4800=4800,
    uart_baud_9600=9600,
#endif
}uart_baud_def;
/*---------------------------------------宏定义------------------------------------*/

/*--------------------------------------变量定义-----------------------------------*/
extern u8 uart1_busy;
/*--------------------------------------程序定义-----------------------------------*/

/*-------------------------------------------------------
函数名：uart_init
描  述：串口初始化函数。
输  入：
    dev     串口信息结构体。
输  出：无
返回值：
    UART_OK     正常
    UART_ID_ERR 编号错误
创建者：奈特
调用例程：
    uart_typedef uart1;         //定义一个信息结构体。
    uart_config(&uart1,9600,0); //设置波特率为9600，无校验。
    uart_init(&uart1);          //使用以上信息初始化串口1。
创建日期：2021-01-21
修改记录：
-------------------------------------------------------*/
extern uart_status uart_init(uart_typedef * dev);
/*-------------------------------------------------------
函数名：uart_deinit
描  述：串口还原函数。
输  入：
    id      串口编号。
输  出：无
返回值：
    UART_OK     正常
    UART_ID_ERR 编号错误
创建者：奈特
调用例程：
    uart_deinit(&uart1);//还原串口1的设置。
创建日期：2021-05-11
修改记录：
-------------------------------------------------------*/
extern uart_status uart_deinit(u8 id);
/*-------------------------------------------------------
函数名：uart_get_configuration_wizard
描  述：从图形化界面中读取串口信息函数。
输  入：
    id      串口编号。
输  出：
    dev     串口信息结构体    
返回值：
    UART_OK         串口操作正常。
    UART_ID_ERR     串口编号错误。
    UART_BAUD_ERR   波特率错误。
创建者：奈特
调用例程：
    uart_typedef uart1; //定义一个信息结构体。
    uart_get_configuration_wizard(&uart1,1);//从图形化界面里读取串口1的设置信息。
    uart_init(&uart1);  //使用以上信息初始化串口1。
创建日期：2021-05-11
修改记录：
-------------------------------------------------------*/
extern uart_status uart_get_configuration_wizard(uart_typedef * dev,u8 id);
/*-------------------------------------------------------
函数名：uart_config_baud
描  述：串口配置波特率函数，用于计算波特率对应的初值。
输  入：
    dev     串口信息结构体。
    baud    波特率。
输  出：无
返回值：
    UART_OK         串口操作正常。
    UART_BAUD_ERR   波特率错误。
创建者：奈特
调用例程：
    uart_typedef uart1;         //定义一个信息结构体。
    uart_config_baud(&uart1,9600,0); //设置波特率为9600。
    uart_init(&uart1);          //使用以上信息初始化串口1。
创建日期：2021-01-21
修改记录：
-------------------------------------------------------*/
extern uart_status uart_config_baud(uart_typedef * dev,u32 baud);
/*-------------------------------------------------------
函数名：uart_config
描  述：串口通用配置函数，将串口配置成常用的异步通信。
输  入：
    dev     串口信息结构体。
    baud    波特率。
    check   检验方式。
输  出：无
返回值：
    UART_OK         串口操作正常。
    UART_BAUD_ERR   波特率错误。
    UART_CHECK_ERR  校验错误。
创建者：奈特
调用例程：
    uart_typedef uart1;         //定义一个信息结构体。
    uart_config(&uart1,9600,0); //设置波特率为9600，无校验。
    uart_init(&uart1);          //使用以上信息初始化串口1。
创建日期：2021-01-21
修改记录：
-------------------------------------------------------*/
extern uart_status uart_config(uart_typedef * dev,u32 baud,u8 check);
/*-------------------------------------------------------
函数名：uart_send_char
描  述：串口发送函数，发送单个字节。
输  入：
    dev     串口信息结构体。
    dat     要发送的数据。
输  出：无
返回值：
    UART_OK         串口操作正常。
    UART_ID_ERR     串口编号错误。
    UART_CHECK_ERR  校验错误。
创建者：奈特
调用例程：
    uart_send_char(&uart1,'Q');//使用串口1发送字符Q。
创建日期：2021-01-21
修改记录：
2021-05-12：新增非中断下的发送成功判断。
-------------------------------------------------------*/
extern uart_status uart_send_char(uart_typedef * dev,u8 dat);
/*-------------------------------------------------------
函数名：uart_send_char_9
描  述：串口发送函数，发送单个字节，限定发送9位。
输  入：
    dev     串口信息结构体。
    dat     要发送的数据。
    bit9    第9位数据。
输  出：无
返回值：
    UART_OK         串口操作正常。
    UART_ID_ERR     串口编号错误。
创建者：奈特
调用例程：
    uart_send_char_9(&uart1,'Q',1);//使用串口1发送字符Q，且第9位为1。
创建日期：2021-01-21
修改记录：
2021-05-12：新增非中断下的发送成功判断。
-------------------------------------------------------*/
extern uart_status uart_send_char_9(uart_typedef * dev,u8 dat,u8 bit9);
/*-------------------------------------------------------
函数名：uart_send_string
描  述：串口发送字符串函数。
输  入：
    dev     串口信息结构体。
    str     要发送的字符串。
输  出：无
返回值：
    UART_OK         串口操作正常。
    UART_ID_ERR     串口编号错误。
    UART_CHECK_ERR  校验错误。
创建者：奈特
调用例程：
    uart_send_string(&uart1,"Hi,PC!\r\n");//使用串口1发送“HI,PC!”并回车换行。
创建日期：2021-01-21
修改记录：
-------------------------------------------------------*/
extern uart_status uart_send_string(uart_typedef * dev,u8 * str);
/*-------------------------------------------------------
函数名：uart1_receive_callback
描  述：串口1接收回调函数。串口1接收到数据的时候会调用该函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2020-01-07
修改记录：
-------------------------------------------------------*/
extern void uart1_receive_callback(void);
/*-------------------------------------------------------
函数名：uart1_send_callback
描  述：串口1发送回调函数。串口1发送完一个数据的时候会调用该函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2020-01-07
修改记录：
-------------------------------------------------------*/
extern void uart1_send_callback(void);
#endif //和最上面的#ifndef配合成一个程序段。
       //以一个空行为结尾。 