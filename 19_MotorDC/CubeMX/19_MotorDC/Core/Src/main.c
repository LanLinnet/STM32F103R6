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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"		//引入标准输入输出库头文件
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
uint16_t cmpv = 80;		//捕获比较值，即CRR2的设定值
uint8_t rf = 0;		//中断标志位
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
	char str[4];		//用于存放CRR2值转换的字符串
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
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);		//定时器3运行并在通道2输出PWM函数
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, cmpv);		//给定时器3设定通道2的捕获比较寄存器值（CRR2）
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);		
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(rf == 1)
		{
			HAL_UART_Transmit(&huart1, (uint8_t *)&"PWM:", 4, 4);		//串口发送字符串（PWM比较寄存器值，值越大转速越快）
			sprintf(str, "%d", cmpv);
			HAL_UART_Transmit(&huart1, (uint8_t *)str, 3, 3);
			HAL_UART_Transmit(&huart1, (uint8_t *)&"\n\r", 2, 2);
			rf = 0;		//标志位清零
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
//外部中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)		//正转按钮
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		rf = 1;
	}
	else if(GPIO_Pin == GPIO_PIN_1)		//反转按钮
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		rf = 1;
	}
	else if(GPIO_Pin == GPIO_PIN_2)		//停止按钮
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);
	}
	else if(GPIO_Pin == GPIO_PIN_3)		//加速按钮（增加PWM信号波形占空比）
	{
		if(cmpv<100) cmpv+=10;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, cmpv);		//给定时器3设定通道2的捕获比较寄存器值（CRR2）
		rf = 1;
	}
	else if(GPIO_Pin == GPIO_PIN_4)		//减速按钮（减小PWM信号波形占空比）
	{
		if(cmpv>0) cmpv-=10;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, cmpv);		//给定时器3设定通道2的捕获比较寄存器值（CRR2）
		rf = 1;
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
