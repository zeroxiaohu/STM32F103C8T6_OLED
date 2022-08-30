#ifndef _I2C_H_
#define _I2C_H_

/*  引脚宏定义  */
#define SCL_PIN         GPIO_PIN_0
#define SDA_PIN         GPIO_PIN_1

#define SCL_PORT        GPIOB
#define SDA_PORT        GPIOB

/*  函数宏定义  */
#define SCL_H       HAL_GPIO_WritePin(SCL_PORT,SCL_PIN,GPIO_PIN_SET)
#define SCL_L       HAL_GPIO_WritePin(SCL_PORT,SCL_PIN,GPIO_PIN_RESET)

#define SDA_H       HAL_GPIO_WritePin(SDA_PORT,SDA_PIN,GPIO_PIN_SET)
#define SDA_L       HAL_GPIO_WritePin(SDA_PORT,SDA_PIN,GPIO_PIN_RESET)
#define SDA_IN      HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN)

void I2C_Init(void);
void I2C_Delay(uint32_t t);
void I2C_Start(void);
void I2C_Stop(void);
int I2C_GetAck(void);
void I2C_ACK(void);
void I2C_NACK(void);

void I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte(uint8_t ack);
#endif
