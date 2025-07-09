#pragma once

#include "main.hpp"

using namespace std;

#define SHT30_ADDR (uint8_t)(0x44<<1) 

#define SHT30_READ_HUMITURE (uint16_t)0x2c06 

#define POLYNOMIAL_CXDZ 0x31

#define SHT30_IIC_SCL_PIN 50 /*!< 作为 SCL */
#define SHT30_IIC_SDA_PIN 51 /*!< 作为 SDA */

/* 修改信号线的输入输出模式 */
#define SHT30_IIC_SDA_OUT (SOFT_IIC_SDA_PIN_fd.GpioDirection(GPIO_Mode_Out))
#define SHT30_IIC_SDA_IN  (SOFT_IIC_SDA_PIN_fd.GpioDirection(GPIO_Mode_In))

/* 初始化信号线和时钟线 */
#define SHT30_IIC_SCL_INIT (SOFT_IIC_SCL_PIN_fd = HWGpio(SOFT_IIC_SCL_PIN, GPIO_Mode_Out))
#define SHT30_IIC_SDA_INIT (SOFT_IIC_SDA_PIN_fd = HWGpio(SOFT_IIC_SDA_PIN, GPIO_Mode_Out))

/* 时钟线高电平与低电平的宏 */
#define SHT30_IIC_SCL_H (SOFT_IIC_SCL_PIN_fd.SetGpioValue(1))
#define SHT30_IIC_SCL_L (SOFT_IIC_SCL_PIN_fd.SetGpioValue(0))

/* 信号线高电平与低电平的宏 */
#define SHT30_IIC_SDA_H (SOFT_IIC_SDA_PIN_fd.SetGpioValue(1))
#define SHT30_IIC_SDA_L (SOFT_IIC_SDA_PIN_fd.SetGpioValue(0))

/* 读取信号线的电平值 */
#define SHT30_IIC_SDA_READ (SOFT_IIC_SDA_PIN_fd.GetGpioValue())

void IIC_Init(void);                // IIC初始化
unsigned char SHT3X_CRC(uint8_t *data, uint8_t len);
void SHT30_CMD(uint16_t cmd);
uint8_t SHT30_Read_Humiture(int *temp,int *humi);
void Delay_ms(uint32_t num);
