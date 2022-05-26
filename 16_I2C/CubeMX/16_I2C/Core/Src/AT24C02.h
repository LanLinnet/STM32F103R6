//AT24C02操作
#ifndef AT24C02_H_
#define AT24C02_H_
#define AT24C02_ADDR 0xa0
#include "main.h"
#include "vI2C.h"

//写入1字节
void AT24C02_Write(uint8_t DatAddr, uint8_t Dat)
{
	I2C_Start();		//主机发送启动通信信号
	I2C_WtByte(AT24C02_ADDR + 0);		//发送器件（芯片）地址
	I2C_Ack(); 		//产生应答响应
	I2C_WtByte(DatAddr);  //发送字地址
	I2C_Ack();		//产生应答响应
	I2C_WtByte(Dat);		//发送数据
	I2C_Ack();		//产生应答响应
	I2C_Stop();		//发送停止通信信号
}

//读取1字节
uint8_t AT24C02_Read(uint8_t DatAddr)
{
	uint8_t Dat;
	I2C_Start();		//主机发送启动通信信号
	I2C_WtByte(AT24C02_ADDR + 0);		//发送器件地址
	I2C_Ack();		//产生应答响应
	I2C_WtByte(DatAddr);		//发送字地址
	I2C_Ack();		//产生应答响应
	I2C_Start();		//再次发送启动通信信号
	I2C_WtByte(AT24C02_ADDR + 1);		//发送器件地址
	I2C_Ack();		//产生应答响应
	Dat = I2C_RdByte();		//读取数据
	I2C_Stop();		//产生非应答信号，发送停止通信信号
	return Dat;
}

#endif /* AT24C02_H_ */
