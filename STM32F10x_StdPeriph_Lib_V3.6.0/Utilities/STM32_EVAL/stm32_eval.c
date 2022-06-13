/**
  ******************************************************************************
  * @file    stm32_eval.c
  * @author  MCD Application Team
  * @version V4.5.1
  * @date    20-September-2021
  * @brief   STM32xx-EVAL abstraction layer. 
  *          This file should be added to the main application to use the provided
  *          functions that manage Leds, push-buttons, COM ports and low level 
  *          HW resources initialization of the different modules available on
  *          STM32 evaluation boards from STMicroelectronics.
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
  
/* Includes ------------------------------------------------------------------*/
#include "stm32_eval.h"

/** @addtogroup Utilities
  * @{
  */ 
  
/** @defgroup STM32_EVAL 
  * @brief This file provides firmware functions to manage Leds, push-buttons, 
  *        COM ports and low level HW resources initialization of the different 
  *        modules available on STM32 Evaluation Boards from STMicroelectronics.
  * @{
  */ 

/** @defgroup STM32_EVAL_Abstraction_Layer
  * @{
  */ 
  
#ifdef USE_STM32100B_EVAL
 #include "stm32100b_eval/stm32100b_eval.c"
#elif defined USE_STM3210B_EVAL
 #include "stm3210b_eval/stm3210b_eval.c" 
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval/stm3210e_eval.c"
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval/stm3210c_eval.c"
#elif defined USE_STM32L152_EVAL
 #include "stm32l152_eval/stm32l152_eval.c"
#elif defined USE_STM32100E_EVAL
 #include "stm32100e_eval/stm32100e_eval.c"
#else 
 #error "Please select first the STM32 EVAL board to be used (in stm32_eval.h)"
#endif

/** @defgroup STM32_EVAL_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32_EVAL_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32_EVAL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32_EVAL_Private_Variables
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32_EVAL_Private_FunctionPrototypes
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32_EVAL_Private_Functions
  * @{
  */ 
/**
  * @}
  */ 


/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

