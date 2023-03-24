/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
 
}
GPIO_InitTypeDef GPIO_InitStruct = {0};

uint32_t read_w25q128_device_id(SPI_HandleTypeDef *hspi)
{
  uint8_t tx_buf[4] = {0x90, 0x00, 0x00, 0x00}; // Command to read device ID
  uint8_t rx_buf[4] = {0};

  // Activate chip select
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  // Send read command and receive response
  HAL_SPI_TransmitReceive(hspi, tx_buf, rx_buf, 4, HAL_MAX_DELAY);

  // Deactivate chip select
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

  // Return device ID
  return ((uint32_t)rx_buf[1] << 16) | ((uint32_t)rx_buf[2] << 8) | rx_buf[3];
	if (hspi == NULL)
		{
    return 0; 
    }


HAL_StatusTypeDef status = HAL_SPI_Init(hspi);
if (status != HAL_OK)
	{
    return 0; 
   }
}


/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
