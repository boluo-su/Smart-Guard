#pragma once

#include "main.hpp"


/* 确认软件IIC所使用的引脚号 */
#define SOFT_IIC_SCL_PIN 50 /*!< 作为 SCL */
#define SOFT_IIC_SDA_PIN 51 /*!< 作为 SDA */

/* 修改信号线的输入输出模式 */
#define SDA_OUT (SOFT_IIC_SDA_PIN_fd.GpioDirection(GPIO_Mode_Out))
#define SDA_IN  (SOFT_IIC_SDA_PIN_fd.GpioDirection(GPIO_Mode_In))

/* 初始化信号线和时钟线 */
#define IIC_SCL_INIT (SOFT_IIC_SCL_PIN_fd = HWGpio(SOFT_IIC_SCL_PIN, GPIO_Mode_Out))
#define IIC_SDA_INIT (SOFT_IIC_SDA_PIN_fd = HWGpio(SOFT_IIC_SDA_PIN, GPIO_Mode_Out))

/* 时钟线高电平与低电平的宏 */
#define IIC_SCL_H (SOFT_IIC_SCL_PIN_fd.SetGpioValue(1))
#define IIC_SCL_L (SOFT_IIC_SCL_PIN_fd.SetGpioValue(0))

/* 信号线高电平与低电平的宏 */
#define IIC_SDA_H (SOFT_IIC_SDA_PIN_fd.SetGpioValue(1))
#define IIC_SDA_L (SOFT_IIC_SDA_PIN_fd.SetGpioValue(0))

/* 读取信号线的电平值 */
#define IIC_SDA_READ (SOFT_IIC_SDA_PIN_fd.GetGpioValue())

#define SHT30_ADDR (uint8_t)(0x44<<1) 

#define SHT30_READ_HUMITURE (uint16_t)0x2c06 

#define POLYNOMIAL_CXDZ 0x31

void IIC_Start(void);               // 发送IIC开始信号
void IIC_Stop(void);                // 发送IIC停止信号
void IIC_Ack(void);                 // IIC发送ACK信号
void IIC_NAck(void);                // IIC不发送ACK信号
uint8_t IIC_WaitAck(void);          // IIC等待ACK信号
void IIC_SendByte(uint8_t data_t);  // IIC发送一个字节
uint8_t IIC_ReadByte(uint8_t ack);  // IIC读取一个字节
unsigned char SHT3X_CRC(uint8_t *data, uint8_t len);
void SHT30_CMD(uint16_t cmd);
uint8_t SHT30_Read_Humiture(int *temp,int *humi);

