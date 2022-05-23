#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_
#include "main.h"

//选择数据寄存器
#define RS_DataR() HAL_GPIO_WritePin(GPIOA, RS_Pin, GPIO_PIN_SET)
#define RS_InstructionR() HAL_GPIO_WritePin(GPIOA, RS_Pin, GPIO_PIN_RESET)

//选择指令寄存器
//读操作
#define RW_Read() HAL_GPIO_WritePin(GPIOA, RW_Pin, GPIO_PIN_SET)
//写操作
#define RW_Write() HAL_GPIO_WritePin(GPIOA, RW_Pin, GPIO_PIN_RESET)

//Enable操作：高电平-读取信息；下降沿-执行指令
#define E_Set() HAL_GPIO_WritePin(GPIOA, E_Pin, GPIO_PIN_SET)
#define E_Rst() HAL_GPIO_WritePin(GPIOA, E_Pin, GPIO_PIN_RESET)

/*************************************自定义函数****************************************/
//D0-D7设定方向：I-输入；O-输出
void DataDir(char dir)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(GPIOC, D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	if(dir == 'I')
	{
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	}
	else if(dir == 'O')
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	}
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

//D0-D7读数据
uint8_t ReadData()
{
	uint8_t dat=0;
	//DataDir('I');
	if(HAL_GPIO_ReadPin(GPIOC, D0_Pin)==GPIO_PIN_SET) dat|=0x01;
	if(HAL_GPIO_ReadPin(GPIOC, D1_Pin)==GPIO_PIN_SET) dat|=0x02;
	if(HAL_GPIO_ReadPin(GPIOC, D2_Pin)==GPIO_PIN_SET) dat|=0x04;
	if(HAL_GPIO_ReadPin(GPIOC, D3_Pin)==GPIO_PIN_SET) dat|=0x08;
	if(HAL_GPIO_ReadPin(GPIOC, D4_Pin)==GPIO_PIN_SET) dat|=0x10;
	if(HAL_GPIO_ReadPin(GPIOC, D5_Pin)==GPIO_PIN_SET) dat|=0x20;
	if(HAL_GPIO_ReadPin(GPIOC, D6_Pin)==GPIO_PIN_SET) dat|=0x40;
	if(HAL_GPIO_ReadPin(GPIOC, D7_Pin)==GPIO_PIN_SET) dat|=0x80;
	return dat;
}

//D0-D7写数据
void WriteData(uint8_t dat)
{
	uint16_t Set_Pins = 0, Rst_Pins = 0;
	//DataDir('O');
	if(dat & 0x01) Set_Pins |= D0_Pin;
	else Rst_Pins |= D0_Pin;
	if(dat & 0x02) Set_Pins |= D1_Pin;
	else Rst_Pins |= D1_Pin;
	if(dat & 0x04) Set_Pins |= D2_Pin;
	else Rst_Pins |= D2_Pin;
	if(dat & 0x08) Set_Pins |= D3_Pin;
	else Rst_Pins |= D3_Pin;
	if(dat & 0x10) Set_Pins |= D4_Pin;
	else Rst_Pins |= D4_Pin;
	if(dat & 0x20) Set_Pins |= D5_Pin;
	else Rst_Pins |= D5_Pin;
	if(dat & 0x40) Set_Pins |= D6_Pin;
	else Rst_Pins |= D6_Pin;
	if(dat & 0x80) Set_Pins |= D7_Pin;
	else Rst_Pins |= D7_Pin;
	
	HAL_GPIO_WritePin(GPIOC, Set_Pins, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, Rst_Pins, GPIO_PIN_RESET);
}

//LCD忙等待
void LCD_Busy_Wait()
{
	uint8_t status;
	DataDir('I');
	RS_InstructionR();
	RW_Read();
	do
	{
		E_Set();
		__NOP();
		status = ReadData();
		E_Rst();
	}
	while(status & 0x80);
}

//写LCD指令
void LCD_Write_Cmd(uint8_t cmd)
{
	DataDir('O');
	WriteData(cmd);
	RS_InstructionR();
	RW_Write();
	E_Rst();
	RS_InstructionR();
	RW_Write();
	E_Set();
	__NOP();
	E_Rst();
	LCD_Busy_Wait();
}

//写LCD数据寄存器
void LCD_Write_Data(uint8_t dat)
{
	DataDir('O');
	WriteData(dat);
	RS_DataR();
	RW_Write();
	E_Set();
	__NOP();
	E_Rst();
	LCD_Busy_Wait();
}

//LCD初始化
void LCD_Init()
{
	LCD_Write_Cmd(0x38);
	HAL_Delay(2);
	LCD_Write_Cmd(0x01);
	HAL_Delay(2);
	LCD_Write_Cmd(0x06);
	HAL_Delay(2);
	LCD_Write_Cmd(0x0c);
	HAL_Delay(2);
}

//在x行（0-1），y列（0-15）显示字符串
void LCD_ShowString(uint8_t x, uint8_t y, char *str)
{
	uint8_t i=0;
	//设置显示起始位置
	if(x == 0)
		LCD_Write_Cmd(0x80|y);
	else if(x == 1)
		LCD_Write_Cmd(0xc0|y);
	//输出字符串
	for(i=0; i<16 && str[i]!='\0'; i++)
	{
		LCD_Write_Data(str[i]);
		HAL_Delay(2);
	}
}
#endif //INC_LCD1602_H_
