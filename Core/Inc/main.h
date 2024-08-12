/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

void Determining_Power_Output_Status(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define P_IN_Pin GPIO_PIN_0
#define P_IN_GPIO_Port GPIOA
#define BTN_Pin GPIO_PIN_1
#define BTN_GPIO_Port GPIOA
#define BTN_EXTI_IRQn EXTI1_IRQn
#define SW_Pin GPIO_PIN_2
#define SW_GPIO_Port GPIOA
#define ADD_Pin GPIO_PIN_3
#define ADD_GPIO_Port GPIOA
#define REDUCE_Pin GPIO_PIN_4
#define REDUCE_GPIO_Port GPIOA
#define ST_Pin GPIO_PIN_5
#define ST_GPIO_Port GPIOA
#define a_Pin GPIO_PIN_0
#define a_GPIO_Port GPIOB
#define b_Pin GPIO_PIN_1
#define b_GPIO_Port GPIOB
#define c_Pin GPIO_PIN_2
#define c_GPIO_Port GPIOB
#define A2_Pin GPIO_PIN_10
#define A2_GPIO_Port GPIOB
#define d_Pin GPIO_PIN_3
#define d_GPIO_Port GPIOB
#define e_Pin GPIO_PIN_4
#define e_GPIO_Port GPIOB
#define f_Pin GPIO_PIN_5
#define f_GPIO_Port GPIOB
#define g_Pin GPIO_PIN_6
#define g_GPIO_Port GPIOB
#define dp_Pin GPIO_PIN_7
#define dp_GPIO_Port GPIOB
#define A0_Pin GPIO_PIN_8
#define A0_GPIO_Port GPIOB
#define A1_Pin GPIO_PIN_9
#define A1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

typedef enum
{
  POWER_OFF = 0x00U,
  POWER_ON  = 0x01U
} enum_PowerStatusTypeDef;

extern enum_PowerStatusTypeDef global_power_status;

typedef enum
{
  DISPLAY_OFF     = 0x00U,
  DISPLAY_HOUR    = 0x01U,
  DISPLAY_MINUTE  = 0x02U,
  DISPLAY_SECOND  = 0x03U,
  DISPLAY_ALL     = 0x04U
} enum_DisplayStatusTypeDef;

extern enum_DisplayStatusTypeDef global_display_status;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
