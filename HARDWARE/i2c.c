#include"main.h"


void I2C_Init(void)
{
   //暂无需要初始化参数 
}

void I2C_Delay(uint32_t t)
{
    volatile uint32_t tmp = t;
    while(tmp--);
}

void I2C_Start(void)
{
    SCL_H;
    SDA_H;
    I2C_Delay(100);
    SDA_L;
    I2C_Delay(100);
}

void I2C_Stop(void)
{
    SCL_H;
    SDA_L;
    I2C_Delay(100);
    SDA_H;
    I2C_Delay(100);
}

int I2C_GetAck(void)
{
    int i = 0;
    SCL_L;
    SDA_H;
    I2C_Delay(100);
    SCL_H;
    while(SDA_IN != 0)
    {
        i++;
        if(i==100)
        {
            SCL_L;
            return -1;
        }
        I2C_Delay(10);
    }
    SCL_L;
    return 0;
}

void I2C_ACK(void)
{
    SCL_L;
    SDA_L;
    I2C_Delay(100);
    SCL_H;
    I2C_Delay(100);

}

void I2C_NACK(void)
{
    SCL_L;
    SDA_H;
    I2C_Delay(100);
    SCL_H;
    I2C_Delay(100);
}
void I2C_WriteByte(uint8_t data)
{
    uint8_t i=0;
    for(i=0;i<8;i++)
    {
        SCL_L;
        I2C_Delay(100);
        if(data & 0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }
        data<<=1;
        SCL_H;
        I2C_Delay(100);
    }
    I2C_GetAck();

}
uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t i =0;
    uint8_t data =0;
    SDA_H;
    
    for(i=0; i<8; i++)
    {
        SCL_L;
        I2C_Delay(100);
        SCL_H;
        I2C_Delay(100);
        data <<= 1; // 更新数据前，要将上一次数据左移1位用来保存接下来的这一位数据
        if(SDA_IN == 1)    
        {                 
            data++;
        }
        else
        {
            data = data;
        }
    }
    
    // 根据ack决定是否发出应答
    if(ack == 0)
    {
        I2C_ACK();
    }
    else if(ack == 1)
    {
        I2C_NACK();
    }
    
    return data;

}
