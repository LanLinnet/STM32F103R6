/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define _FLASH_ADD 0x08006400  //写入Flash ROM首地址（Page 25）
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rf = 0;		//自定义串口接收完毕标志
uint8_t RcvBuf[1];		//接收缓冲
uint8_t SndBuf[1];		//发送缓冲
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void FlashErase(uint32_t Add);		//声明自定义Flash ROM擦除函数
void FlashWrite(uint32_t Add, uint16_t Dat);		//声明自定义Flash ROM写函数
uint16_t FlashRead(uint32_t Add);		//声明自定义Flash ROM读函数
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint16_t flash_wdat;  //写入Flash数据存储变量
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1,RcvBuf,1);  //串口1接收中断函数
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(rf == 1)		//串口接收完毕
		{
			rf = 0;		//标志位清0
			flash_wdat = RcvBuf[0];		//将接收到的数据存入写Flash变量中
			FlashErase(_FLASH_ADD);		//擦除指定部分
			FlashWrite(_FLASH_ADD, flash_wdat);		//写入Flash
			HAL_UART_Receive_IT(&huart1, RcvBuf, 1);		//每次接收前都需要调用一次
		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET)		
		{
			HAL_Delay(25);		//消抖
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET)		//如果按键按下
			{
				SndBuf[0] = (uint8_t)FlashRead(_FLASH_ADD);		//读Flash中值并存入发送缓冲
				HAL_UART_Transmit(&huart1, SndBuf, 1, 10);		//由串口1发送缓冲中的值
				while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET);		//等待按键松开
			}
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//串口接收完毕回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)		//如果串口1接收完毕
	{
		rf = 1;		//标志位置1
	}
}

/*Flash页擦除
*-Add表示待擦除页的首地址
*-Flash必须整页擦除，也就是整页的每个地址单元内容都为FFH才能写入新数据
*/
void FlashErase(uint32_t Add)
{
	uint32_t page_error = 0;  	//错误指针
	FLASH_EraseInitTypeDef erase_initstruct = 
	{
		.TypeErase = FLASH_TYPEERASE_PAGES,		//擦除方式为页擦除
		.NbPages = 1,		//页数量为1页
		.PageAddress = Add		//擦除页起始地址
	};
	HAL_FLASH_Unlock();		//解锁Flash ROM
	HAL_FLASHEx_Erase(&erase_initstruct, &page_error);		//擦除
	HAL_FLASH_Lock();		//锁定Flash ROM
}

/*Flash写函数
*-写入一个Half Word（16位）型数据
*-Add表示Flash ROM地址
*-Dat表示写入数据（16位）
*-注意：写入时，高字节在高地址
*/
void FlashWrite(uint32_t Add, uint16_t Dat)
{
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Add, Dat);		//将数据写入Flash
	HAL_FLASH_Lock();
}

/*Flash读函数
*-返回一个Half Word（16位）型数据
*-Add表示Flash ROM地址
*/
uint16_t FlashRead(uint32_t Add)
{
	uint16_t dat;
	dat = *(uint16_t *)Add;
	return dat;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
