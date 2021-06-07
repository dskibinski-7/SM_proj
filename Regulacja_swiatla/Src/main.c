/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "eth.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bh1750.h"
#include "stm32f7xx_hal_i2c.h"
#include<stdlib.h>
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
	int BH1750_int;
	int wypelnienie=0;
	char wyswietl_lcd[200];
	char zadana[4]; // wartosc zadana z apki - uart
	int int_zadana=70; // wartosc zadana zmieniona na int
	//HAL_StatusTypeDef status;
	HAL_StatusTypeDef status_odbior;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //odbior wiadomosci z uarta (wartosc zadana)
{
	//odbior zadanej - zamiana na int
	int_zadana = atoi(zadana);
	status_odbior = HAL_UART_Receive_IT(&huart3, (uint8_t*)zadana, 4);
}

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
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
//  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  BH1750_Init();

  LCD_Init();
  HAL_Delay(500);
  LCD_Send_Str_Pos("Natezenie",0,0);
  LCD_Send_Str_Pos("swiatla",0,1);

  status_odbior = HAL_UART_Receive_IT(&huart3, (uint8_t*)zadana, 4); //przerwanie od uarta
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, wypelnienie); //ustawia zadane wypelnienei na pwm (poczatkowe -> 0)


  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  BH1750_int=(int)BH1750_Receive();

	  sprintf(wyswietl_lcd, "[lx]:%d", BH1750_int);
	  LCD_Send_Str_Pos(wyswietl_lcd,7,1);
	  //HAL_Delay(500);
	  if (BH1750_int<1000) // aby na ostatnim miejscu 'nie zawieszala' sie ostatnia cyfra (np. przejscie z 120 na 80)
	  {
		  LCD_Send_Str_Pos(" ",15,1);
	  }
	  if(BH1750_int<100)
	  {
		  LCD_Send_Str_Pos(" ",14,1);
	  }


	  // ^wyswietla wynik na wyswietlaczu // gdy zejdziemy np ze 103 do 84 to wyswietla 843 (zostawia 3 miejsce po przecinku)
	  // mozna dac po prostu zakres powyzej 100 hehe

	  //regulator dwupolozeniowy:
	  if (BH1750_int <= int_zadana && wypelnienie <=1000 && abs(BH1750_int-int_zadana)>10 ) // jezeli wartosc odiberana przez czujnik jest mniejsza od zadanej -> zwieksz swiecenie diody
	  {
		  wypelnienie +=10;
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, wypelnienie);
	  }
	  else if(BH1750_int <= int_zadana && wypelnienie <=1000 && abs(BH1750_int-int_zadana)<10)
	  {
		  wypelnienie +=1;
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, wypelnienie);
		  HAL_Delay(200); // w dokladniejszym manipuluj wolniej
	  }
	  else if (BH1750_int > int_zadana && wypelnienie > 0 && abs(BH1750_int-int_zadana)>10) // jezeli wieksza - zmniejsz //zabezpieczenie,aby wyp ni spadlo ponizej 0
	  {
		  wypelnienie -=10;
		  if(wypelnienie<0) //aby wypelnienei nie bylo ujemne - wtedy dioda swieci na maxa
		  {
			  wypelnienie =0;
		  }
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, wypelnienie); //ustaw zadane wypelnienie na diodzie
	  }
	  else if (BH1750_int > int_zadana && wypelnienie > 0 && abs(BH1750_int-int_zadana)<10)
	  {
		  wypelnienie -=1;
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, wypelnienie);
		  HAL_Delay(200); // w dokladniejszym manipuluj wolniej
	  }



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
