/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim4;

/* USER CODE BEGIN Private defines */

uint8_t display_number[10] = 
{
  0x3F, 0x06, 0x5B, 0x4F, 0x66,       //  0, 1, 2, 3, 4
  0x6D, 0x7D, 0x07, 0x7F, 0x7F        //  5, 6, 7, 8, 9
};
uint8_t cathode_number[8] = 
{
  0x00, 0x00, 0x00, 0x00,       //  -, -, -, -
  0x00, 0x00, 0x00, 0x00        //  -, -, -, -
};
uint8_t cathode_select = 0;

/* USER CODE END Private defines */

void MX_TIM4_Init(void);

/* USER CODE BEGIN Prototypes */

void DynamicDisplay (GPIO_TypeDef *GPIOx, uint8_t i, uint16_t number);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

