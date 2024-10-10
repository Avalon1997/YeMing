/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "usart.h"
#include "tim.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

static int display_convert;
static uint8_t second_convert_mask = 0x00U;
static uint16_t second_number = 0x0000U;
static uint8_t display_convert_hourbuffer[2] = {0x00, 0x00};
static uint8_t display_convert_minutebuffer[2] = {0x00, 0x00};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(PBTN_Pin);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  if (GPIO_PIN_SET == HAL_GPIO_ReadPin(PBTN_GPIO_Port,PBTN_Pin))
  {
    global_power_status = POWER_ON;
  }
  else if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(PBTN_GPIO_Port,PBTN_Pin))
  {
    global_power_status == POWER_OFF;
  }

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel4 global interrupt.
  */
void DMA1_Channel4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_IRQn 0 */

  /* USER CODE END DMA1_Channel4_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA1_Channel4_IRQn 1 */

  /* USER CODE END DMA1_Channel4_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel5 global interrupt.
  */
void DMA1_Channel5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel5_IRQn 0 */

  /* USER CODE END DMA1_Channel5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Channel5_IRQn 1 */

  /* USER CODE END DMA1_Channel5_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(TBTN_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  if (GPIO_PIN_SET == HAL_GPIO_ReadPin(TBTN_GPIO_Port,TBTN_Pin))
  {
    global_timer_status = POWER_ON;
    global_display_status = DISPLAY_ON;
  }
  else if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(TBTN_GPIO_Port,TBTN_Pin))
  {
    global_timer_status == POWER_OFF;
    global_display_status = DISPLAY_OFF;
  }

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
  if (0 == second_count)
  {
    if (minute_count > 0)
    {
      minute_count --;
      second_count = 60;
    }
    else if (0 == minute_count)
    {
      if (hour_count > 0)
      {
        hour_count --;
        minute_count = 59;
        second_count = 60;
      }
      else if (0 == hour_count)
      {
        // Counter end, cut off power output, clear display, reset counter.
      }
    }
  }
  second_count --;

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  // Flashing count limit.
  if (8 == cathode_select)
  {
    cathode_select = 0;
  }

  // Timeout count
  if (DISPLAY_HOUR == global_display_status || DISPLAY_MINUTE == global_display_status)
  {
    global_timeout_count ++;
    display_convert ++;
    
    // convert display
    if (50 == display_convert)
    {
      if (DISPLAY_HOUR == global_display_status)
      {
        display_convert_hourbuffer[0] = cathode_number[2];
        display_convert_hourbuffer[1] = cathode_number[3];
        cathode_number[2] = 0x00;
        cathode_number[3] = 0x00;
      }
      else
      {
        display_convert_minutebuffer[0] = cathode_number[0];
        display_convert_minutebuffer[1] = cathode_number[1];
        cathode_number[0] = 0x00;
        cathode_number[1] = 0x00;
      }
    }
    else if (100 == display_convert)
    {
      if (DISPLAY_HOUR == global_display_status)
      {
        cathode_number[2] = display_convert_hourbuffer[0];
        cathode_number[3] = display_convert_hourbuffer[1];
      }
      else
      {
        cathode_number[0] = display_convert_minutebuffer[0];
        cathode_number[1] = display_convert_minutebuffer[1];
      }
      display_convert = 0;
    }

    // If there is no operation for a long time(5s).
    if (500 == global_timeout_count)
    {
      global_display_status = DISPLAY_ON;   // Stop Flashing
      global_timeout_count = 0;             // Clear timeout count
    }
  }
  // If the TBTN is closed, then display the time.
  if (global_display_status != DISPLAY_OFF && global_timer_count_status == TIMER_COUNT_OFF)
  {
    DynamicDisplay(GPIOB, cathode_select, (uint16_t)cathode_number[cathode_select], second_number);
  }
  else if(global_display_status != DISPLAY_OFF && global_timer_count_status == TIMER_COUNT_ON)
  {
    global_second_dot_count++;
    if (50 == global_second_dot_count)
    {
      second_convert_mask = ~second_convert_mask;
      second_number = second_number | (second_convert_mask << 7);
    }
    DynamicDisplay(GPIOB, cathode_select, (uint16_t)cathode_number[cathode_select], second_number);
  }
  cathode_select++;

  /* USER CODE END TIM4_IRQn 1 */
}


/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  if (__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE) == SET )
  {
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);
    HAL_UART_DMAStop(&huart1);
    rx1_len = RX1BUFFERSIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
    memcpy(data_cache1,rx1_buffer,rx1_len);
    
    rx1_len = 0;
    memset(rx1_buffer,0,RX1BUFFERSIZE);
    HAL_UART_Receive_DMA(&huart1,rx1_buffer,RX1BUFFERSIZE);
  }

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
