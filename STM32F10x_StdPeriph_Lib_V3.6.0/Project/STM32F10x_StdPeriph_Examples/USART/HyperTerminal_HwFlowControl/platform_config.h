/**
  ******************************************************************************
  * @file    USART/HyperTerminal_HwFlowControl/platform_config.h 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    20-September-2021
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2011 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM32100B_EVAL) && !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL) &&  !defined (USE_STM32100E_EVAL)
 //#define USE_STM32100B_EVAL
 //#define USE_STM3210B_EVAL
 //#define USE_STM32100E_EVAL
 #define USE_STM3210E_EVAL
#endif

/* Define the STM32F10x hardware depending on the used evaluation board */
#if defined(USE_STM3210B_EVAL) || defined (USE_STM32100B_EVAL)
#define  GPIOx                    GPIOD
#define  RCC_APB2Periph_GPIOx     RCC_APB2Periph_GPIOD
#define  GPIO_RTSPin              GPIO_Pin_4
#define  GPIO_CTSPin              GPIO_Pin_3
#define  GPIO_TxPin               GPIO_Pin_5
#define  GPIO_RxPin               GPIO_Pin_6
#elif defined (USE_STM3210E_EVAL) || defined (USE_STM32100E_EVAL)
#define  GPIOx                    GPIOA
#define  RCC_APB2Periph_GPIOx     RCC_APB2Periph_GPIOA
#define  GPIO_RTSPin              GPIO_Pin_1
#define  GPIO_CTSPin              GPIO_Pin_0
#define  GPIO_TxPin               GPIO_Pin_2
#define  GPIO_RxPin               GPIO_Pin_3
#endif /* USE_STM3210B_EVAL */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

