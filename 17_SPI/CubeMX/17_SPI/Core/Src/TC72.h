#ifndef INC_TC72_H_
#define INC_TC72_H_

#include "main.h"
#include "vSPI.h"

//宏定义
#define _TC72_CTRL_R 			0x00		//控制寄存器地址（读）
#define _TC72_CTRL_W 			0x80		//控制寄存器地址（写）
#define _TC72_Dat_LSB 		0x01		//温度低字节地址（读）
#define _TC72_Dat_MSB 		0x02		//温度高字节地址（读）
#define _TC72_ID 					0x03		//制造商ID（读）
#define _TC72_OnceCnv 		0x15		//单次转化指令
#define _TC72_ContinueCnv 0x05		//连续转化指令

//发送转化指令
void TC72_Convert(uint8_t Instr)		//Instr为指令
{
	vSPI_En();		//SPI总线使能
	vSPI_SndByte(_TC72_CTRL_W);		//发送控制寄存器地址（写）
	vSPI_SndByte(Instr);		//发送转化指令
	vSPI_Dis();		//SPI总线禁止
}

//读温度
float TC72_TemperatureRd()
{
	uint8_t DatL, DatM;		//高低字节
	int16_t Dat;		//最终接收数据
	float t;		//转化温度
	vSPI_En();		//SPI总线使能
	vSPI_SndByte(_TC72_Dat_MSB);		//发送温度高字节地址（读）
	DatM = vSPI_RcvByte();		//SPI主站接收1字节（高）
	DatL = vSPI_RcvByte();		//SPI主站接收1字节（低）
	vSPI_Dis();		//SPI总线禁止
	Dat = DatM;	
	Dat <<= 8;
	Dat += DatL;	//组合高低字节
	t = ((float)(Dat))/256;		//转化温度
	return t;		//返回温度值
}

#endif /* INC_TC72_H_ */
