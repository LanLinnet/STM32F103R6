/**
  ******************************************************************************
  * @file    CAN/Networking/platform_config.h 
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
#include "stm32_eval.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL) &&  !defined (USE_STM3210C_EVAL)
 //#define USE_STM3210B_EVAL
 //#define USE_STM3210E_EVAL
 #define USE_STM3210C_EVAL
#endif

/* Define the STM32F10x hardware depending on the used evaluation board */
#ifdef USE_STM3210B_EVAL
  #define RCC_APB2Periph_GPIO_CAN1    RCC_APB2Periph_GPIOD
  #define GPIO_Remapping_CAN1         GPIO_Remap2_CAN1
  #define GPIO_CAN1                   GPIOD  
  #define GPIO_Pin_CAN1_RX            GPIO_Pin_0
  #define GPIO_Pin_CAN1_TX            GPIO_Pin_1

#elif defined USE_STM3210E_EVAL
  #define RCC_APB2Periph_GPIO_CAN1    RCC_APB2Periph_GPIOB
  #define GPIO_Remapping_CAN1         GPIO_Remap1_CAN1
  #define GPIO_CAN1                   GPIOB
  #define GPIO_Pin_CAN1_RX            GPIO_Pin_8
  #define GPIO_Pin_CAN1_TX            GPIO_Pin_9

#elif defined USE_STM3210C_EVAL
  #define RCC_APB2Periph_GPIO_CAN1    RCC_APB2Periph_GPIOD
  #define GPIO_Remapping_CAN1         GPIO_Remap2_CAN1
  #define GPIO_CAN1                   GPIOD  
  #define GPIO_Pin_CAN1_RX            GPIO_Pin_0
  #define GPIO_Pin_CAN1_TX            GPIO_Pin_1
  
  #define RCC_APB2Periph_GPIO_CAN2    RCC_APB2Periph_GPIOB
  #define GPIO_Remapping_CAN2         GPIO_Remap_CAN2
  #define GPIO_CAN2                   GPIOB  
  #define GPIO_Pin_CAN2_RX            GPIO_Pin_5
  #define GPIO_Pin_CAN2_TX            GPIO_Pin_6
#endif /* USE_STM3210B_EVAL */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

