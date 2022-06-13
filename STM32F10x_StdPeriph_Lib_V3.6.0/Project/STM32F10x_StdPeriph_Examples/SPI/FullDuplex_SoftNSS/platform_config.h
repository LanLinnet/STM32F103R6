/**
  ******************************************************************************
  * @file    SPI/FullDuplex_SoftNSS/platform_config.h 
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
#if defined (USE_STM3210B_EVAL) || defined (USE_STM3210E_EVAL) || defined(USE_STM32100B_EVAL) || defined (USE_STM32100E_EVAL)
  #define SPIy                   SPI1
  #define SPIy_CLK               RCC_APB2Periph_SPI1
  #define SPIy_GPIO              GPIOA
  #define SPIy_GPIO_CLK          RCC_APB2Periph_GPIOA  
  #define SPIy_PIN_SCK           GPIO_Pin_5
  #define SPIy_PIN_MISO          GPIO_Pin_6
  #define SPIy_PIN_MOSI          GPIO_Pin_7
  
  #define SPIz                    SPI2
  #define SPIz_CLK                RCC_APB1Periph_SPI2
  #define SPIz_GPIO               GPIOB
  #define SPIz_GPIO_CLK           RCC_APB2Periph_GPIOB 
  #define SPIz_PIN_SCK            GPIO_Pin_13
  #define SPIz_PIN_MISO           GPIO_Pin_14
  #define SPIz_PIN_MOSI           GPIO_Pin_15 
          
#elif defined (USE_STM3210C_EVAL)
  #define SPIy                   SPI3   /* SPI pins are remapped by software */
  #define SPIy_CLK               RCC_APB1Periph_SPI3
  #define SPIy_GPIO              GPIOC
  #define SPIy_GPIO_CLK          RCC_APB2Periph_GPIOC  
  #define SPIy_PIN_SCK           GPIO_Pin_10
  #define SPIy_PIN_MISO          GPIO_Pin_11
  #define SPIy_PIN_MOSI          GPIO_Pin_12
  
  #define SPIz                    SPI2
  #define SPIz_CLK                RCC_APB1Periph_SPI2
  #define SPIz_GPIO               GPIOB
  #define SPIz_GPIO_CLK           RCC_APB2Periph_GPIOB
  #define SPIz_PIN_SCK            GPIO_Pin_13
  #define SPIz_PIN_MISO           GPIO_Pin_14
  #define SPIz_PIN_MOSI           GPIO_Pin_15

#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

