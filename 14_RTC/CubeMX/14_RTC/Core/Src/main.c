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
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
	//定义日期结构体和时间结构体
	RTC_DateTypeDef sDateStructure;
	RTC_TimeTypeDef sTimeStructure;
	char sYear[5];
	char sMonth[3];
	char sDate[3];
	char sHour[3];
	char sMin[3];
	char sSec[3];
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
  MX_RTC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//十进制格式
		HAL_RTC_GetTime(&hrtc, &sTimeStructure, RTC_FORMAT_BIN);  //RTC时间获取函数
		//BCD码格式
		HAL_RTC_GetDate(&hrtc, &sDateStructure, RTC_FORMAT_BCD);  //RTC日期获取函数
		//格式转换为字符串
		sprintf(sYear, "%04x", 0x2000+sDateStructure.Year);
		sprintf(sMonth, "%02x", sDateStructure.Month);
		sprintf(sDate, "%02x", sDateStructure.Date);
		sprintf(sHour, "%02d", sTimeStructure.Hours);
		sprintf(sMin, "%02d", sTimeStructure.Minutes);
		sprintf(sSec, "%02d", sTimeStructure.Seconds);
		//打印日期
		HAL_UART_Transmit(&huart1, (uint8_t *)sYear, 4, 4);
		HAL_UART_Transmit(&huart1, (uint8_t *)&"-", 1, 1);
		HAL_UART_Transmit(&huart1, (uint8_t *)sMonth, 2, 2);
		HAL_UART_Transmit(&huart1, (uint8_t *)&"-", 1, 1);
		HAL_UART_Transmit(&huart1, (uint8_t *)sDate, 2, 2);
		HAL_UART_Transmit(&huart1, (uint8_t *)&" ", 1, 2);
		//打印时间
		HAL_UART_Transmit(&huart1, (uint8_t *)sHour, 2, 2);
		HAL_UART_Transmit(&huart1, (uint8_t *)&":", 1, 1);
		HAL_UART_Transmit(&huart1, (uint8_t *)sMin, 2, 2);
		HAL_UART_Transmit(&huart1, (uint8_t *)&":", 1, 1);
		HAL_UART_Transmit(&huart1, (uint8_t *)sSec, 2, 2);
		HAL_UART_Transmit(&huart1, (uint8_t *)&"\n\r", 2, 2);
		//延时
		HAL_Delay(1000);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//外部中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//定义日期结构体和时间结构体
	RTC_DateTypeDef sDateStructure;
	RTC_TimeTypeDef sTimeStructure;
	if(GPIO_Pin == GPIO_PIN_5)  //检测到EXTI5线产生外部中断事件
	{
		//设置日期
		sDateStructure.Year = 22;
		sDateStructure.Month = 5;
		sDateStructure.Date = 20;
		sDateStructure.WeekDay = 5;
		//十进制格式
		HAL_RTC_SetDate(&hrtc, &sDateStructure, RTC_FORMAT_BIN);
		
		//设置时间
		sTimeStructure.Hours = 0x05;
		sTimeStructure.Minutes = 0x20;
		sTimeStructure.Seconds = 0;
		//BCD码格格式
		HAL_RTC_SetTime(&hrtc, &sTimeStructure, RTC_FORMAT_BCD);
		
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET);  //直到按键松开
	}
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
