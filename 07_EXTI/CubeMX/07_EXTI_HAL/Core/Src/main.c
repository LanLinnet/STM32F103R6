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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void ByteOut2PC(uint8_t dat);  //声明函数
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
	int8_t i;   //循环变量i
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		for(i=0; i<8; i++)
		{
			ByteOut2PC((0xfe<<i)|(0xfe>>(8-i)));  //正常流水灯状态
			HAL_Delay(500);
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
//自定义函数，将1字节数据输出到PC端口的PC0-PC7引脚
void ByteOut2PC(uint8_t dat)
{
	if(dat & 0x01)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
	else 
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
	if(dat & 0x02)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
	else 
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
	if(dat & 0x04)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 1);
	else 
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
	if(dat & 0x08)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);
	else 
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0);
	if(dat & 0x10)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);
	else 
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 0);
	if(dat & 0x20)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 1);
	else 
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 0);
	if(dat & 0x40)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 1);
	else 
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
	if(dat & 0x80)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
	else 
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
}

//中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	int8_t i;  //循环变量
	if(GPIO_Pin == GPIO_PIN_0)  //检测到EXTI0线产生外部中断事件
	{
		for(i=0; i<3; i++)  //全亮全灭闪烁3次
		{
			ByteOut2PC(0xff);  //全灭
			HAL_Delay(500);
			ByteOut2PC(0);  //全亮
			HAL_Delay(500);
		}
	}
	else if(GPIO_Pin == GPIO_PIN_1) //检测到EXTI1线产生外部中断事件
	{
		for(i=0; i<3; i++)  //间隔交替闪烁3次
		{
			ByteOut2PC(0x55);  
			HAL_Delay(500);
			ByteOut2PC(0xaa);  
			HAL_Delay(500);
		}
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
