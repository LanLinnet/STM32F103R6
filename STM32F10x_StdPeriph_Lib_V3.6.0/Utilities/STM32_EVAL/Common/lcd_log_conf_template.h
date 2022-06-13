/**
  ******************************************************************************
  * @file    lcd_log_conf_template.h
  * @author  MCD Application Team
  * @version V4.6.0
  * @date    11-March-2011
  * @brief   lcd_log configuration template file.
  *          This file should be copied to the application folder and changed to
  *          lcd_log_conf.h  
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef  __LCD_LOG_CONF_H__
#define  __LCD_LOG_CONF_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32_eval.h"
#include <stdio.h>

#ifdef USE_STM32100B_EVAL
 #include "stm32100b_eval/stm32100b_eval_lcd.h"
#elif defined USE_STM3210B_EVAL
 #include "stm3210b_eval/stm3210b_eval_lcd.h" 
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval/stm3210e_eval_lcd.h"
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval/stm3210c_eval_lcd.h"
#elif defined USE_STM32L152_EVAL
 #include "stm32l152_eval/stm32l152_eval_lcd.h" 
#elif defined USE_STM32100E_EVAL
 #include "stm32100e_eval/stm32100e_eval_lcd.h" 
#elif defined USE_STM322xG_EVAL
 #include "stm322xg_eval/stm322xg_eval_lcd.h"
#endif  

/** @addtogroup LCD_LOG
  * @{
  */
  
/** @defgroup LCD_LOG
  * @brief This file is the 
  * @{
  */ 


/** @defgroup LCD_LOG_CONF_Exported_Defines
  * @{
  */ 

/* Define the LCD default text color */
#define     LCD_LOG_DEFAULT_COLOR    White

/* Comment the line below to disable the scroll back and forward features */
#define     LCD_SCROLL_ENABLED               

/* Define the display window settings */
#define     YWINDOW_MIN         3
#define     YWINDOW_SIZE        12
#define     XWINDOW_MAX         50

/* Define the cache depth */
#define     CACHE_SIZE          50

/** @defgroup LCD_LOG_CONF_Exported_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup LCD_LOG_Exported_Macros
  * @{
  */ 


/**
  * @}
  */ 

/** @defgroup LCD_LOG_CONF_Exported_Variables
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LCD_LOG_CONF_Exported_FunctionsPrototype
  * @{
  */ 

/**
  * @}
  */ 


#endif /* __LCD_LOG_H__ */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
