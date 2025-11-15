#include "hal_config.h"
#if ECBM_CONFIG_UART_EN //编译开关，当配置库没有使能该外设时，就不编译该.c文件
/*------------------------------------资源冲突警告---------------------------------*/
#if (ECBM_UART1_RUN_MODE>=2)&&(ECBM_UART1_CHECK_MODE==0)
#warning 由于通信模式选择了9位模式，所以请至少选择一种校验位！
#endif
#if (ECBM_UART1_RUN_MODE<2)&&(ECBM_UART1_CHECK_MODE!=0)
#warning 由于校验位也要占用一位，所以通信模式请选择9位模式！
#endif
/*--------------------------------------变量定义-----------------------------------*/
u8 uart1_busy=0;
/*--------------------------------------引脚定义-----------------------------------*/
sbit uart1_rs485_io=ECBM_UART1_RS485_IO;
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
串口初始化函数。
-------------------------------------------------------*/
uart_status uart_init(uart_typedef * dev){
    switch(dev->id){
        #if ECBM_UART1_LIB_EN
            case 1:{
                if(dev->it_enable){     //配置串口1中断使能。
                    UART1_SET_IT_ENABLE;
                }else{
                    UART1_SET_IT_DISABLE;
                }
                if(dev->it_priority){   //配置串口1中断优先级。
                    UART1_SET_IT_PRIORITY_HIGH;
                }else{
                    UART1_SET_IT_PRIORITY_LOW;
                }
                if(dev->rxd_enable){    //配置串口1接收使能。
                    UART1_SET_RXD_ENABLE;
                }else{
                    UART1_SET_RXD_DISABLE;
                }
                if(dev->baud_mul){      //配置串口1波特率加倍使能。
                    UART1_SET_BAUD_2;
                }else{
                    UART1_SET_BAUD_1;
                }
                switch(dev->run_mode){  //配置串口1工作模式。
                    case 0:{UART1_SET_MODE_S_8;     }break;
                    case 1:{UART1_SET_MODE_A_8_BAUD;}break;
                    case 2:{UART1_SET_MODE_A_9;     }break;
                    case 3:{UART1_SET_MODE_A_9_BAUD;}break;
                }
                TIMER1_SET_GATE_DISABLE;//关定时器1的门控位
                TIMER1_SET_MODE_TIMER;  //定时器1的模式为定时器
                TIMER1_SET_MODE_8BIT;   //定时器1运行于8位自动重载
                TIMER1_SET_REG_HL(dev->init_value);//赋初值。
                TIMER1_SET_POWER_ON;    //打开定时器1。
                peripheral.uart |=0x01; //标记串口1已经打开。
                peripheral.timer|=0x02; //标记定时器1已经被使用。
            }break;
        #endif
        default:return UART_ID_ERR;break;
    }
    #if ECBM_UART1_LIB_EN
        return UART_OK;
    #endif
}
/*-------------------------------------------------------
串口还原函数。
-------------------------------------------------------*/
#if ECBM_UART_FUN_DEINIT_EN
uart_status uart_deinit(u8 id){
    switch(id){
        #if ECBM_UART1_LIB_EN
            case 1:{
                UART1_SET_IT_DISABLE;   //关闭串口1中断使能。
                UART1_SET_IT_PRIORITY_LOW;//还原串口1中断优先级。
                UART1_SET_RXD_DISABLE;  //关闭串口1接收使能。
                UART1_SET_BAUD_1;       //关闭串口1波特率加倍使能。
                UART1_SET_MUX_DISABLE;  //关闭串口1多机通信使能。
                UART1_SET_MODE_S_8;     //还原串口1工作模式。
                TIMER1_SET_POWER_OFF;   //关闭定时器1。
                peripheral.uart&=~0x01; //取消标记串口1。
                peripheral.timer&=~0x02;//取消标记定时器1。
            }break;
        #endif
        default:return UART_ID_ERR;break;
    }
    #if ECBM_UART1_LIB_EN
        return UART_OK;
    #endif
}
#endif
/*-------------------------------------------------------
从图形化界面中读取串口信息函数。
-------------------------------------------------------*/
#if (ECBM_UART_FUN_CONFIG_WIZARD_EN)&&(ECBM_UART_FUN_CONFIG_BAUD_EN)
uart_status uart_get_configuration_wizard(uart_typedef * dev,u8 id){
    u8 res;
    id=id;
    dev=dev;
    switch(id){
        #if ECBM_UART1_LIB_EN
            case 1:{
                dev->id=1;
                dev->rxd_enable =ECBM_UART1_RXD_EN;
                res=uart_config_baud(dev,ECBM_UART1_BAUD);
                if(res!=UART_OK)return res;
                dev->run_mode   =ECBM_UART1_RUN_MODE;
                dev->check_mode =ECBM_UART1_CHECK_MODE;
                dev->it_enable  =ECBM_UART1_IT_EN;
                dev->it_priority=ECBM_UART1_IT_PRIORITY;
            }break;
        #endif
        default:return UART_ID_ERR;break;//如果没有以上编号，返回编号错误。
    }
    #if ECBM_UART1_LIB_EN
        return UART_OK;
    #endif
}
#endif
/*-------------------------------------------------------
串口配置波特率函数。
-------------------------------------------------------*/
#if ECBM_UART_FUN_CONFIG_BAUD_EN
uart_status uart_config_baud(uart_typedef * dev,u32 baud){
    u8 temp1,temp2;
    u32 res1,res2,der1,der2;
    temp1=(u8 )(ECBM_SYSCLK_SETTING/(ECBM_TIMER1_CLK_DIV  )/32/baud);//计算出波特率不加倍下的初值。
    temp2=(u8 )(ECBM_SYSCLK_SETTING/(ECBM_TIMER1_CLK_DIV/2)/32/baud);//计算出波特率加倍下的初值。
    res1 =(u32)(ECBM_SYSCLK_SETTING/(ECBM_TIMER1_CLK_DIV  )/32/temp1);//由初值反推波特率。
    res2 =(u32)(ECBM_SYSCLK_SETTING/(ECBM_TIMER1_CLK_DIV/2)/32/temp2);
    if(res1>baud)der1=res1-baud;else der1=baud-res1;//计算出给定的波特率和计算的波特率的误差。
    if(res2>baud)der2=res2-baud;else der2=baud-res2;
    der1=der1*1000/baud;//给误差算算比例。
    der2=der2*1000/baud;
    if((der1>20)&&(der2>20)){//如果加倍和不加倍，误差都大于2%。
        return UART_BAUD_ERR;//那么返回波特率错误。
    }else{                   //如果有其中一个满足要求，
        if(der1<20){         //是不加倍满足要求的话，
            dev->baud_mul=0; //设置波特率不加倍。
            dev->init_value=(256-temp1)*256+(256-temp1);//装上初值。
        }
        if(der2<20){         //是加倍满足要求的话，
            dev->baud_mul=1; //设置波特率加倍。
            dev->init_value=(256-temp2)*256+(256-temp2);//装上初值。
        }
    }
    dev->run_mode=1;
    return UART_OK;
}
#endif
/*-------------------------------------------------------
串口通用配置函数。
-------------------------------------------------------*/
#if (ECBM_UART_FUN_CONFIG_EN)&&(ECBM_UART_FUN_CONFIG_BAUD_EN)
uart_status uart_config(uart_typedef * dev,u32 baud,u8 check){
    if(check>UART_CHECK_USER){      //判断校验是不是合格。
        return UART_CHECK_ERR;      //不合格返回校验错误。
    }else{                          //校验合格之后，
        dev->check_mode=check;      //储存校验方式。
        if(check==UART_CHECK_NONE){ //假如没有校验，
            dev->run_mode=1;        //就设定为8位数据通信。
        }else{                      //否则就是
            dev->run_mode=3;        //9位数据通信。
        }
    }
    dev->rxd_enable=1;              //默认打开接收使能。
    dev->it_enable =1;              //默认打开串口中断。
    dev->it_priority=0;             //中断优先级不变。
    return  uart_config_baud(dev,baud);
}
#endif
/*-------------------------------------------------------
串口发送函数。
-------------------------------------------------------*/
uart_status uart_send_char(uart_typedef * dev,u8 dat){
    dat=dat;
    switch(dev->id){
        #if ECBM_UART1_LIB_EN
            case 1:{
                #if ECBM_UART_FUN_CHECK_EN
                    switch(dev->check_mode){
                        case 0:break;//没有校验就什么都不执行。
                        case 1:{//奇校验
                            IF_ODD(dat){                //判断有没有奇数个1。
                                UART1_SET_TXD_BYTE9_0;  //有就加个0，维持个数为奇数。
                            }else{
                                UART1_SET_TXD_BYTE9_1;  //没有就加个1，变成奇数个1。
                            }
                        }break;
                        case 2:{//偶校验
                            IF_ODD(dat){                //判断有没有奇数个1
                                UART1_SET_TXD_BYTE9_1;  //有就加个1，变成偶数个1。
                            }else{
                                UART1_SET_TXD_BYTE9_0;  //没有就加个0，维持个数为偶数。
                            }
                        }break;
                        case 3:{//1校验
                            UART1_SET_TXD_BYTE9_1;      //恒定为1。
                        }break;
                        case 4:{//0校验
                            UART1_SET_TXD_BYTE9_0;      //恒定为0。 
                        }break;
                        default:return UART_CHECK_ERR;break;//该函数不支持自定义校验位。
                    }
                #endif
                #if ECBM_UART_RS485_EN
                    uart1_rs485_io=1;
                #endif
                UART1_SET_REG_SBUF(dat);//把数据发送出去。
                if(dev->it_enable){
                    uart1_busy=1;           //置串口忙标志位。
                    while(uart1_busy);      //等待发送结束。
                }else{
                    while(!UART1_GET_TI_FLAG);//等待发送。
                    UART1_CLR_TI_FLAG;          //发送成功后清除标志位。
                }
                #if ECBM_UART_RS485_EN
                    uart1_rs485_io=0;
                #endif
            }break;
        #endif
        default:return UART_ID_ERR;break;//如果ID不是单片机已有的，就返回ID错误。
    }
    #if ECBM_UART1_LIB_EN
        return UART_OK;
    #endif
}
/*-------------------------------------------------------
串口发送函数，发送单个字节，限定发送9位。
-------------------------------------------------------*/
#if ECBM_UART_FUN_CHECK_EN
uart_status uart_send_char_9(uart_typedef * dev,u8 dat,u8 bit9){
    dat=dat;
    bit9=bit9;
    switch(dev->id){
        #if ECBM_UART1_LIB_EN
            case 1:{
                if(bit9){
                    UART1_SET_TXD_BYTE9_1;
                }else{
                    UART1_SET_TXD_BYTE9_0;
                }
                #if ECBM_UART_RS485_EN
                    uart1_rs485_io=1;
                #endif
                UART1_SET_REG_SBUF(dat);//把数据发送出去。
                uart1_busy=1;           //置串口忙标志位。
                if(dev->it_enable){ 
                    while(uart1_busy);      //等待发送结束。
                }else{
                    while(!UART1_GET_TI_FLAG);//等待发送。
                    UART1_CLR_TI_FLAG;        //发送成功后清除标志位。
                    uart1_busy=0;             //清串口忙标志位。
                }
                #if ECBM_UART_RS485_EN
                    uart1_rs485_io=0;
                #endif
            }break;
        #endif
        default:return UART_ID_ERR;break;
    }
    #if ECBM_UART1_LIB_EN
        return UART_OK;
    #endif
}
#endif
/*-------------------------------------------------------
串口发送字符串函数。
-------------------------------------------------------*/
uart_status uart_send_string(uart_typedef * dev,u8 * str){
    u8 res;
    while(*str){                //有校验位就用通用发送函数来发送。
        res=uart_send_char(dev,*str);
        str++;
    }
    return res;
}
/*-------------------------------------------------------
串口中断处理函数。
-------------------------------------------------------*/
#if ECBM_UART_FUN_IT_EN
void uart1_it_fun(void) UART1_IT_NUM {
    if(UART1_GET_TI_FLAG){
        UART1_CLR_TI_FLAG;
        uart1_busy=0;
        #if ECBM_UART1_FUN_SEND_CALLBACK_EN
            uart1_send_callback();
        #endif
    }
    if(UART1_GET_RI_FLAG){
        UART1_CLR_RI_FLAG;
        ECBM_STREAM_IN(SBUF);
        #if ECBM_UART1_FUN_RECEIVE_CALLBACK_EN
            uart1_receive_callback();
        #endif
    }
}
#endif
#endif
