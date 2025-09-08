#include <dht11.h>

void _Delay10us() // @16MHz, 软件延时，由 STC-ISP 工具生成
{
    unsigned char i;
    _nop_();
    _nop_();
    i = 37;
    while (--i)
        ;
}

uint8_t DHT11_Measure(DHT11_Data *dat)
{
    int8_t buf[5];
    uint8_t i, j, errCode = DHT11_DONE;

    DATA_WRITE(0);
    _Delay(20); // 开始信号 20 ms
    DATA_WRITE(1);

    // 60 us
    _Delay10us();
    _Delay10us();
    _Delay10us();
    _Delay10us();
    _Delay10us();
    _Delay10us();

    if (DATA_READ() == 0)
    {
        while (DATA_READ() == 0) // 等待 DHT11 拉高
            ;

        while (DATA_READ() == 1)
            ;

        i = 0;
        while (i < 5)
        {
            j = 0;
            while (j < 8)
            {
                while (DATA_READ() == 0)
                    ;

                _Delay10us();
                _Delay10us();
                _Delay10us();

                buf[i] <<= 1;
                buf[i] |= DATA_READ();
                while (DATA_READ() == 1)
                    ;
                j++;
            }
            i++;
        }

        _Delay10us();
        _Delay10us();
        _Delay10us();
        _Delay10us();
        _Delay10us();
        _Delay10us();

        if (buf[4] == buf[0] + buf[1] + buf[2] + buf[3])
        {
            dat->temperature = buf[2];
            dat->humidity = buf[0];
        }
        else
        {
            errCode = DHT11_VERIFY_ERR;
        }
    }
    else
    {
        errCode = DHT11_CONNECT_ERR;
    }

    DATA_WRITE(1);
    _Delay(1);

    return errCode;
}
