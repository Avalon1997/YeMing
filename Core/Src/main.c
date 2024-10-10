/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * ------------------------------------------------------------------
  *
  *                        ____  _   _ _   _ 
  *                       |  _ \| | | | \ | |
  *                       | |_) | | | |  \| |
  *                       |  _ <| |_| | |\  |
  *                       |_| \_\\___/|_| \_|
  *
  *
  *                                                      CharlesYu
  * ------------------------------------------------------------------
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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

enum_PowerStatusTypeDef global_power_status = POWER_OFF;                                // global power output status: Off/On
enum_PowerStatusTypeDef global_timer_status = POWER_OFF;                                // global timer status : Off/On
enum_DisplayStatusTypeDef global_display_status = DISPLAY_OFF;                          // global display clock status: Off/Hour/Minute/All
enum_KeyEventTypeDef global_key_event = KEY_EVENT_NULL;                                 // global key event: Null/Click/Hold
enum_TimerCountStatusTypeDef global_timer_count_status = TIMER_COUNT_OFF;               // global timeout counter status: Off/On

int key_count = 0;                          // Time count of button press          
int global_timeout_count = 0;               // Count and flash hour or minute display.
int global_second_dot_count = 0;            // Count and flash second dot display.

/* ---------- Total time count */
uint8_t minute_count = 0;                   // These three variable are about the time count.
uint8_t hour_count = 0;                     // The total time count is 
uint8_t second_count = 0;                   // (minute_count*60 + hour_count*3600 + second_count), in seconds .


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* ---------- Timer Key Scan Code ---------- */
    // If TBTN is closed
    if (POWER_ON == global_timer_status)
    {
      if (TIMER_COUNT_OFF == global_timer_count_status)
      {
        // If the SW is pressed.
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(SW_GPIO_Port,SW_Pin))
        {
          HAL_Delay(10);
          if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(SW_GPIO_Port,SW_Pin))
          {
            // Determine the event type: click or hold 
            while(1)
            {
              if (GPIO_PIN_SET == HAL_GPIO_ReadPin(SW_GPIO_Port,SW_Pin))
              {
                HAL_Delay(10);
                if(GPIO_PIN_SET == HAL_GPIO_ReadPin(SW_GPIO_Port,SW_Pin))
                {
                  global_key_event = KEY_EVENT_CLICK;
                  break;
                }
              }

              key_count ++;
              HAL_Delay(1);

              if(MAXIMUM_KEY_COUNT == key_count)
              {
                global_key_event = KEY_EVENT_HOLD;
                break;
              }
            }
            // Click Mode Operation: Switch the display(hour/minute).
            if (KEY_EVENT_CLICK == global_key_event)
            {
              if (DISPLAY_OFF == global_display_status || DISPLAY_HOUR == global_display_status)
              {
                global_display_status = DISPLAY_MINUTE;
                global_timeout_count = 0;
              }
              else if (DISPLAY_MINUTE == global_display_status)
              {
                global_display_status = DISPLAY_HOUR;
                global_timeout_count = 0;
              }
            }
            // Hold Mode Operation: Clear the display and count. 
            else if (KEY_EVENT_HOLD == global_key_event)
            {
              // set no flashing.
              global_display_status == DISPLAY_ON;
              // Set timer display 00:00 .
              cathode_number[0] = display_number[0];  
              cathode_number[1] = display_number[0];
              cathode_number[2] = display_number[0];
              cathode_number[3] = display_number[0];
              // Set count to 0 .
              minute_count = 0;
              hour_count = 0;
              
              while (1)
              {
                if (GPIO_PIN_SET == HAL_GPIO_ReadPin(SW_GPIO_Port,SW_Pin))
                {
                  HAL_Delay(10);
                  if(GPIO_PIN_SET == HAL_GPIO_ReadPin(SW_GPIO_Port,SW_Pin))
                  {
                    break;
                  }
                }
              }
            }
            // Clear all key flags. 
            key_count = 0;
            global_key_event = KEY_EVENT_NULL;
          }
        }
        // If the display is flashing, then we can operate the add and reduce key. 
        if (global_display_status == DISPLAY_HOUR || global_display_status == DISPLAY_MINUTE)
        {
          // If the ADD is pressed.
          if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(ADD_GPIO_Port,ADD_Pin))
          {
            HAL_Delay(10);
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(ADD_GPIO_Port,ADD_Pin))
            {
              // Determine the event type: click or hold 
              while (1)
              {
                if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ADD_GPIO_Port,ADD_Pin))
                {
                  HAL_Delay(10);
                  if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ADD_GPIO_Port,ADD_Pin))
                  {
                    global_key_event == KEY_EVENT_CLICK;
                    break;
                  }
                }

                key_count++;
                HAL_Delay(1);

                if (MAXIMUM_KEY_COUNT == key_count)
                {
                  global_key_event = KEY_EVENT_HOLD;
                  break;
                }
              }
              // Click Mode Operation: Increase count and display. 
              if (KEY_EVENT_CLICK == global_key_event)
              {
                if (DISPLAY_MINUTE == global_display_status)
                {
                  if (59 == minute_count)
                  {
                    minute_count = 0;
                  }
                  else
                  {
                    minute_count ++;
                  }
                  cathode_number[0] = display_number[(uint8_t)((int)minute_count % (int)10)];
                  cathode_number[1] = display_number[(uint8_t)((int)minute_count / (int)10)];
                }
                else if (DISPLAY_HOUR == global_display_status)
                {
                  if (24 == hour_count)
                  {
                    hour_count = 0;
                  }
                  else
                  {
                    hour_count ++;
                  }
                  cathode_number[2] = display_number[(uint8_t)((int)hour_count % (int)10)];
                  cathode_number[3] = display_number[(uint8_t)((int)hour_count / (int)10)];
                }
              }
              // Hold Mode Operation: Keep increasing count and display. 
              else if (KEY_EVENT_HOLD == global_key_event)
              {
                key_count = 0;
                while (1)
                {
                  if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ADD_GPIO_Port,ADD_Pin))
                  {
                    HAL_Delay(10);
                    if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ADD_GPIO_Port,ADD_Pin))
                    { //Hold end
                      break;
                    }
                  }
                  HAL_Delay(50);
                  if (10 == key_count)
                  {
                    if (DISPLAY_MINUTE == global_display_status)
                    {
                      if (59 == minute_count)
                      {
                        minute_count = 0;
                      }
                      else
                      {
                        minute_count ++;
                      }
                      cathode_number[0] = display_number[(uint8_t)((int)minute_count % (int)10)];
                      cathode_number[1] = display_number[(uint8_t)((int)minute_count / (int)10)];
                    }
                    else if (DISPLAY_HOUR == global_display_status)
                    {
                      if (24 == hour_count)
                      {
                        hour_count = 0;
                      }
                      else
                      {
                        hour_count ++;
                      }
                      cathode_number[2] = display_number[(uint8_t)((int)hour_count % (int)10)];
                      cathode_number[3] = display_number[(uint8_t)((int)hour_count / (int)10)];
                    }
                    key_count = 0;
                  }
                  key_count ++;
                } 
              }
              // Clear key flags. 
              key_count = 0;
              global_key_event = KEY_EVENT_NULL;
            }
          }
          // If the REDUCE is pressed. 
          if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(REDUCE_GPIO_Port,REDUCE_Pin))
          {
            HAL_Delay(10);
            if (GPIO_PIN_SET == HAL_GPIO_ReadPin(REDUCE_GPIO_Port,REDUCE_Pin))
            {
              // Determine the event type: click or hold 
              while (1)
              {
                if (GPIO_PIN_SET == HAL_GPIO_ReadPin(REDUCE_GPIO_Port,REDUCE_Pin))
                {
                  HAL_Delay(10);
                  if (GPIO_PIN_SET == HAL_GPIO_ReadPin(REDUCE_GPIO_Port,REDUCE_Pin))
                  {
                    global_key_event == KEY_EVENT_CLICK;
                    break;
                  }
                }

                key_count++;
                HAL_Delay(1);

                if (MAXIMUM_KEY_COUNT == key_count)
                {
                  global_key_event = KEY_EVENT_HOLD;
                  break;
                }
              }
              // Click Mode Operation: Decrease count and display. 
              if (KEY_EVENT_CLICK == global_key_event)
              {
                if (DISPLAY_MINUTE == global_display_status)
                {
                  if (0 == minute_count)
                  {
                    minute_count = 59;
                  }
                  else
                  {
                    minute_count --;
                  }
                  cathode_number[0] = display_number[(uint8_t)((int)minute_count % (int)10)];
                  cathode_number[1] = display_number[(uint8_t)((int)minute_count / (int)10)];
                }
                else if (DISPLAY_HOUR == global_display_status)
                {
                  if (0 == hour_count)
                  {
                    hour_count = 24;
                  }
                  else
                  {
                    hour_count --;
                  }
                  cathode_number[2] = display_number[(uint8_t)((int)hour_count % (int)10)];
                  cathode_number[3] = display_number[(uint8_t)((int)hour_count / (int)10)];
                }
              }
              // Hold Mode Operation: Keep decreasing count and display. 
              else if (KEY_EVENT_HOLD == global_key_event)
              {
                key_count = 0;
                while (1)
                {
                  if (GPIO_PIN_SET == HAL_GPIO_ReadPin(REDUCE_GPIO_Port,REDUCE_Pin))
                  {
                    HAL_Delay(10);
                    if (GPIO_PIN_SET == HAL_GPIO_ReadPin(REDUCE_GPIO_Port,REDUCE_Pin))
                    {
                      // Hold end
                      break;
                    }
                  }
                  HAL_Delay(50);
                  if (20 == key_count)
                  {
                    if (DISPLAY_MINUTE == global_display_status)
                    {
                      if (0 == minute_count)
                      {
                        minute_count = 59;
                      }
                      else
                      {
                        minute_count --;
                      }
                      cathode_number[0] = display_number[(uint8_t)((int)minute_count % (int)10)];
                      cathode_number[1] = display_number[(uint8_t)((int)minute_count / (int)10)];
                    }
                    else if (DISPLAY_HOUR == global_display_status)
                    {
                      if (0 == hour_count)
                      {
                        hour_count = 24;
                      }
                      else
                      {
                        hour_count --;
                      }
                      cathode_number[2] = display_number[(uint8_t)((int)hour_count % (int)10)];
                      cathode_number[3] = display_number[(uint8_t)((int)hour_count / (int)10)];
                    }
                  }
                  key_count ++;
                }
              }
              // Clear key flags. 
              key_count = 0;
              global_key_event = KEY_EVENT_NULL;
            }
          }
        }
      }
        // If the ST is pressed. 
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(ST_GPIO_Port,ST_Pin))
      {
        HAL_Delay(10);
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(ST_GPIO_Port,ST_Pin))
        { // ST only has the click mode. 
          while (1)
          {
            if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ST_GPIO_Port,ST_Pin))
            {
              HAL_Delay(10);
              if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ST_GPIO_Port,ST_Pin))
              {
                break;
              }
            }
          }

          if (TIMER_COUNT_OFF == global_timer_count_status)
          {
            // Firstly, check whether the count is equal to 0. 
            if (0 == minute_count && 0 == hour_count)
            {
              // XXXXX Make the "No count" noise. XXXXX 

              // And do nothing.
            }
            else 
            {
              global_timer_count_status = TIMER_COUNT_ON;
              HAL_TIM_Base_Start_IT(&htim3);  // Run the timer.
            }
          }
          else if (TIMER_COUNT_ON == global_timer_count_status)   
          {
            global_timer_count_status = TIMER_COUNT_OFF;
            HAL_TIM_Base_Stop_IT(&htim3);   // Stop the timer.
          }
        }
      }
    }

    
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/**
* @name       fputc
* @brief      Printf redirection.
* @param      ch
* @param      f
* @return     ch
*
*/
int fputc(int ch,FILE *f)
{
  while ((USART2 -> SR & 0x40) == 0);
  USART2 -> DR = (uint8_t)ch;
  return ch;
}

/**
* @name       Determining_Power_Output_Status
* @brief      To determine the status of power output
*             and the corresponding actions.
* @param      NONE
* @return     NONE

*
*/
void Determining_Power_Output_Status(void)
{
  if (global_power_status == POWER_ON)
  { // Output the current power to the load.

  }
  else
  { // Cut off the current power output.

  }
}

void STM32_Init(void)
{
  // Start the USART1 DMA tranmit.
  HAL_UART_Transmit_DMA(&huart1,rx1_buffer,RX1BUFFERSIZE);

  // Start the timer4 to display LED.
  HAL_TIM_Base_Start_IT(&htim4);


}

void LED_Display_Init(void)
{
  memset(cathode_number,0x3F,sizeof(cathode_number));
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
