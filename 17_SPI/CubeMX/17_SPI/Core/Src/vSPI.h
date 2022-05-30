#ifndef INC_VSPI_H_
#define INC_VSPI_H_

#include "main.h"

//软件延时函数，单位为微秒
void delay_us(uint16_t n)
{
	uint16_t i = n * 8;
	while(i--);
}

//SPI总线使能
void vSPI_En()
{
	HAL_GPIO_WritePin(GPIOA, vCE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_RESET);
	delay_us(4);
}

//SPI总线禁止
void vSPI_Dis()
{
	HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, vCE_Pin, GPIO_PIN_RESET);
}

//SPI主站发送1字节
void vSPI_SndByte(uint8_t dat)		//dat表示发送的字节
{
	uint8_t i;
	for(i=0; i<8; i++)
	{
		HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_RESET);
		delay_us(4);
		if(dat & 0x80)
		{
			HAL_GPIO_WritePin(GPIOA, vMOSI_Pin, GPIO_PIN_SET);
		}
		else 
			HAL_GPIO_WritePin(GPIOA, vMOSI_Pin, GPIO_PIN_RESET);
		dat<<=1;
		//上升沿
		HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_SET);
		delay_us(4);
	}
}

//SPI主站接收1字节数据
uint8_t vSPI_RcvByte()
{
	uint8_t i, dat=0;
	for(i=0;i<8;i++)
	{
		delay_us(4);
		dat<<=1;
		HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(GPIOA, vMISO_Pin) == GPIO_PIN_SET)
		{
			dat |= 0x01;
		}
		else
			dat &= 0xfe;
		HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_SET);
	}
	return dat;		//返回1字节数据
}

#endif /* INC_VSPI_H_ */
