/**
  ******************************************************************************
  * @file    I2C/IOExpander/main.h 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    20-September-2021
  * @brief   Header for main.c module
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
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/

#if !(defined USE_STM32100E_EVAL) && !(defined USE_STM3210C_EVAL)
 #error "Please select STM3210C_EVAL or STM32100E_EVAL board For this example"
#endif

#include "stm32f10x.h"
#include "stm32_eval.h"
#include <stdio.h>
 
#ifdef USE_STM3210C_EVAL
 #include "stm3210c_eval_lcd.h"
 #include "stm3210c_eval_ioe.h"
 
#elif defined USE_STM32100E_EVAL
 #include "stm32100e_eval_lcd.h"
 #include "stm32100e_eval_ioe.h"
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

// #define IOE_POLLING_MODE
#define IOE_INTERRUPT_MODE

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* __MAIN_H */

