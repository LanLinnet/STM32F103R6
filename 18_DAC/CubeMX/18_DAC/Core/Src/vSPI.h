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
	HAL_GPIO_WritePin(GPIOA, vnCS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_RESET);
	delay_us(4);
}

//SPI总线禁止
void vSPI_Dis()
{
	HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, vnCS_Pin, GPIO_PIN_SET);
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

#endif /* INC_VSPI_H_ */
