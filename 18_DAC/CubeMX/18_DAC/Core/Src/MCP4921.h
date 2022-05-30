#ifndef INC_MCP4921_H_
#define INC_MCP4921_H_

#include "main.h"
#include "vSPI.h"

//写入MCP4921: Cmd-指令（仅高4位）  Dat-数据（12位）
void MCP4921Write(uint8_t Cmd, uint16_t Dat)
{
	uint8_t DatM, DatL;		//数据高字节、低字节
	DatL = (uint8_t)(Dat & 0x00ff);	
	DatM = (uint8_t)((Dat>>8) & 0x00ff);
	vSPI_En();		//SPI总线使能
	vSPI_SndByte(0x70|DatM);		//先写高字节
	vSPI_SndByte(DatL);		//再写低字节
	vSPI_Dis();		//SPI总线禁止
}

#endif /* INC_MCP4921_H_ */
