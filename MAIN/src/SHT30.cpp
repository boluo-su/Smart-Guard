#include "SOFT_I2C.hpp"
#include "SHT30.hpp"

HWGpio SOFT_IIC_SCL_PIN_fd;
HWGpio SOFT_IIC_SDA_PIN_fd;

void iic_delay()
{
    /* 200MHz 系统时钟下 模拟IIC速度为 400Khz */
    for (uint8_t i = 0; i < 30; i++) // 修改这里可以调整IIC速率
        __asm("NOP"); /* delay */
}

void IIC_Init(void)
{
    IIC_SCL_INIT;
    IIC_SDA_INIT;
    IIC_SCL_H;
    IIC_SDA_H;
}

void IIC_Start(void)
{
    SDA_OUT; // sda线输出
    IIC_SDA_H;
    IIC_SCL_H;
    iic_delay();
    iic_delay();
    iic_delay();
    iic_delay();
    iic_delay();
    IIC_SDA_L; // 当CLK为高时，DATA从高变低
    iic_delay();
    iic_delay();
    iic_delay();
    IIC_SCL_L; // 钳住I2C总线，准备发送或接收数据
}

void IIC_Stop(void)
{
    SDA_OUT; // sda线输出
    IIC_SCL_L;
    IIC_SDA_L; // 当CLK为高时，DATA从低变为高
    iic_delay();
    iic_delay();
    iic_delay();
    IIC_SCL_H;
    iic_delay();
    iic_delay();
    iic_delay();
    IIC_SDA_H; // 发送I2C总线结束信号
    iic_delay();
}

void IIC_Ack(void)
{
    IIC_SCL_L;
    SDA_OUT;
    IIC_SDA_L;
    iic_delay();
    iic_delay();
    iic_delay();
    IIC_SCL_H;
    iic_delay();
    iic_delay();
    iic_delay();
    IIC_SCL_L;
}

void IIC_NAck(void)
{
    IIC_SCL_L;
    SDA_OUT;
    IIC_SDA_H;
    iic_delay();
    iic_delay();
    iic_delay();
    IIC_SCL_H;
    iic_delay();
    iic_delay();
    iic_delay();
    IIC_SCL_L;
}

uint8_t IIC_WaitAck(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN; // SDA设置为输入  （从机给一个低电平做为应答）
    IIC_SDA_H;
    iic_delay();
    IIC_SCL_H;
    iic_delay();
    while (IIC_SDA_READ)
    {
        ucErrTime++;
        if (ucErrTime > 100)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_L; // 时钟输出0
    return 0;
}

void IIC_SendByte(uint8_t data_t)
{
    uint8_t t;
    SDA_OUT;
    IIC_SCL_L; // 拉低时钟开始数据传输
    for (t = 0; t < 8; t++)
    {
        // IIC_SDA_READ = data_t&0x80;
        if (data_t & 0x80)
            IIC_SDA_H;
        else
            IIC_SDA_L;

        IIC_SCL_H;
        iic_delay();
        data_t <<= 1;
        iic_delay();
        iic_delay();
        IIC_SCL_L;
        iic_delay();
    }
    iic_delay();
}

uint8_t IIC_ReadByte(uint8_t ack)
{
    uint8_t i, receive = 0;
    SDA_IN; // SDA设置为输入模式 等待接收从机返回数据
    for (i = 0; i < 8; i++)
    {
        IIC_SCL_L;
        iic_delay();
        iic_delay();
        iic_delay();
        IIC_SCL_H;
        receive <<= 1;
        if (IIC_SDA_READ)
            receive++; // 从机发送的电平
        iic_delay();
    }
    if (ack)
        IIC_Ack(); // 发送ACK
    else
        IIC_NAck(); // 发送nACK
    return receive;
}



unsigned char SHT3X_CRC(uint8_t *data, uint8_t len)
{
	uint8_t bit;        
	uint8_t crc = 0xFF; 
	uint8_t byteCtr;    

	for(byteCtr = 0; byteCtr < len; byteCtr++) {
			crc ^= (data[byteCtr]);
			for(bit = 8; bit > 0; --bit) {
					if(crc & 0x80) {
							crc = (crc << 1) ^ POLYNOMIAL_CXDZ;
					}  else {
							crc = (crc << 1);
					}
			}
	}
  return crc;
}

void SHT30_CMD(uint16_t cmd)
{
	IIC_Start();
    IIC_SendByte(SHT30_ADDR+0);
	IIC_WaitAck();
	IIC_SendByte((cmd>>8)&0xff); //MSB
	IIC_WaitAck();
	IIC_SendByte(cmd&0xff); //LSB
	IIC_WaitAck();
	IIC_Stop();
	iic_delay();
}


uint8_t SHT30_Read_Humiture(int *temp,int *humi)
{
	uint8_t buff[6];
	
	SHT30_CMD(SHT30_READ_HUMITURE);
	
	IIC_Start();
	IIC_SendByte(SHT30_ADDR+1); 
	IIC_WaitAck();
	buff[0]=IIC_ReadByte(1);
	buff[1]=IIC_ReadByte(1);
	buff[2]=IIC_ReadByte(1);
	buff[3]=IIC_ReadByte(1);
	buff[4]=IIC_ReadByte(1);
	buff[5]=IIC_ReadByte(0);
	IIC_Stop();

	if(SHT3X_CRC(&buff[0],2)==buff[2] &&SHT3X_CRC(&buff[3],2)==buff[5])
	{

		*temp=(-45+(175.0*((buff[0]<<8)+buff[1])/65535.0));
		*humi=100*(((buff[3]<<8)+buff[4])/65535.0);
		if(*temp>12500) *temp=12500;
		else if(*temp<-4000) *temp=-4000;
		return 0;
	}
	else return 1;	
	
}