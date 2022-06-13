/**
  ******************************************************************************
  * @file    USART/HalfDuplex/platform_config.h 
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
#if !defined (USE_STM32100B_EVAL) && !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL) &&  !defined (USE_STM3210C_EVAL) &&  !defined (USE_STM32100E_EVAL)
 //#define USE_STM32100B_EVAL
 //#define USE_STM3210B_EVAL
 //#define USE_STM3210E_EVAL
 //#define USE_STM32100E_EVAL
 #define USE_STM3210C_EVAL 
#endif

/* Define the STM32F10x hardware depending on the used evaluation board */
#if defined(USE_STM3210B_EVAL) || defined (USE_STM32100B_EVAL)

  #define USARTy                   USART1
  #define USARTy_GPIO              GPIOA
  #define USARTy_CLK               RCC_APB2Periph_USART1
  #define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTy_TxPin             GPIO_Pin_9

  #define USARTz                   USART2
  #define USARTz_GPIO              GPIOD
  #define USARTz_CLK               RCC_APB1Periph_USART2
  #define USARTz_GPIO_CLK          RCC_APB2Periph_GPIOD
  #define USARTz_TxPin             GPIO_Pin_5

#elif defined USE_STM3210E_EVAL || defined (USE_STM32100E_EVAL)

  #define USARTy                   USART1
  #define USARTy_GPIO              GPIOA
  #define USARTy_CLK               RCC_APB2Periph_USART1
  #define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTy_TxPin             GPIO_Pin_9

  #define USARTz                   USART2
  #define USARTz_GPIO              GPIOA
  #define USARTz_CLK               RCC_APB1Periph_USART2
  #define USARTz_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTz_TxPin             GPIO_Pin_2

#elif defined USE_STM3210C_EVAL

  #define USARTy                   USART2
  #define USARTy_GPIO              GPIOD
  #define USARTy_CLK               RCC_APB1Periph_USART2
  #define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOD
  #define USARTy_TxPin             GPIO_Pin_5

  #define USARTz                   USART3
  #define USARTz_GPIO              GPIOC
  #define USARTz_CLK               RCC_APB1Periph_USART3
  #define USARTz_GPIO_CLK          RCC_APB2Periph_GPIOC
  #define USARTz_TxPin             GPIO_Pin_10

#endif /* USE_STM3210B_EVAL */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

