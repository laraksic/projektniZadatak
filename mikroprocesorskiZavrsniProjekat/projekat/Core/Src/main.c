/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stdlib.h"
#include "string.h"

#define input1 GPIO_PIN_0
#define input2 GPIO_PIN_0
int inputs[]={input1,input2};

#define led1 GPIO_PIN_4
#define led2 GPIO_PIN_5
#define led3 GPIO_PIN_6
#define led4 GPIO_PIN_7
#define led5 GPIO_PIN_8
#define led6 GPIO_PIN_9

#define output1 GPIO_PIN_1
#define output2 GPIO_PIN_2
#define output3 GPIO_PIN_3
int outputs[]={output1,output2,output3};

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  int matricaTaster[3][2]={1,4,2,5,3,0};
  int poeni, inputNumber=0;

  LCD_init();
  char buffer[20];
  char poruka[20]=" osvojena poena";
  int br=0;

  while (1)
  {
	  int runda=3;
	  poeni=0;

	  while(runda>0)
	  {

		  br=paljenjeNasumicneDiode();

		  for(int i=0;i<3;i++)
		  {
			  HAL_GPIO_WritePin(GPIOA, outputs[i], GPIO_PIN_SET);

			  if(HAL_GPIO_ReadPin(GPIOA, input1)){
				  inputNumber=matricaTaster[i][0];
			  }

			  if(HAL_GPIO_ReadPin(GPIOB, input2)){
				  inputNumber=matricaTaster[i][1];
			  }

			  HAL_Delay(25);
			  HAL_GPIO_WritePin(GPIOA, outputs[i], GPIO_PIN_RESET);
		  }

		  if(inputNumber==br)
			  poeni=poeni+1;

		  runda--;

		  HAL_Delay(1000);
	  }

	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4
	                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
	                          |GPIO_PIN_9, GPIO_PIN_SET);

	  sprintf(buffer, "%d", poeni);
	  int i=0;
	  while(buffer[i]){
		  LCD(buffer[i],1);
	  	  HAL_Delay(50);
	  	  i++;
	  }

	  i=0;
	  while(poruka[i]){
		  LCD(poruka[i],1);
	 	  HAL_Delay(50);
	      i++;
	  }

	  HAL_Delay(700);
	  LCD(0x01, 0);
	  HAL_Delay(900);

  }

}


void LCD_init()
{
	LCD(0x38, 0);
	LCD(0x0C, 0);
	LCD(0x06, 0);
	LCD(0x01, 0);
	LCD(0x80, 0);
}

void LCD(uint8_t val_1, uint8_t cmd)
{
	uint8_t data1;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, cmd);

	data1 = val_1 & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, data1);

	data1 = (val_1 >> 1) & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, data1);

	data1 = (val_1 >> 2) & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, data1);

	data1 = (val_1 >> 3) & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, data1);

	data1 = (val_1 >> 4) & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, data1);

	data1 = (val_1 >> 5) & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, data1);

	data1 = (val_1 >> 6) & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, data1);

	data1 = (val_1 >> 7) & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, data1);


	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
}

int paljenjeNasumicneDiode(){

	int br=rand()%6;

	if(br==1){
		 HAL_GPIO_WritePin(GPIOA, led1, GPIO_PIN_RESET);
	 	 HAL_GPIO_WritePin(GPIOA, led2, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led3, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led4, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led5, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led6, GPIO_PIN_SET);
	 }
	 if(br==2){
		 HAL_GPIO_WritePin(GPIOA, led1, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led2, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOA, led3, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led4, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led5, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led6, GPIO_PIN_SET);
	 }
	if(br==3){
		 HAL_GPIO_WritePin(GPIOA, led1, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led2, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led3, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOA, led4, GPIO_PIN_SET);
	     HAL_GPIO_WritePin(GPIOA, led5, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led6, GPIO_PIN_SET);
	 }
	if(br==4){
		 HAL_GPIO_WritePin(GPIOA, led1, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led2, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led3, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led4, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOA, led5, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, led6, GPIO_PIN_SET);
	 }
	 if(br==5){
		HAL_GPIO_WritePin(GPIOA, led1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, led6, GPIO_PIN_SET);
	 }
	 if(br==0){
		HAL_GPIO_WritePin(GPIOA, led1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, led6, GPIO_PIN_RESET);
	  }

	  return br;
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 PA6 PA7 PA8
                           PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 PB6 PB7
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
