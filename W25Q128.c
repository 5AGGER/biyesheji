#include "W25Q128.h"
#include "SPI.h"
#include "usart.h"

extern SPI_HandleTypeDef hspi1;	

uint8_t W25Q128_ReadWriteByte(uint8_t TxData)//º¯Êý°ü×°Ò»ÏÂ
{   
	uint8_t RxData;
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  if (HAL_SPI_TransmitReceive(&hspi1, &TxData, &RxData, 1, HAL_MAX_DELAY) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 
  return RxData; 
}

uint16_t W25Q128_ReadID(void)//¶ÁÈ¡Ð¾Æ¬ID
{
	uint8_t TxData[4] = {0x90, 0x00, 0x00, 0x00}; 
  uint8_t rxData[3];
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 
  HAL_SPI_TransmitReceive(&hspi1, TxData, rxData, 4, HAL_MAX_DELAY); 
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 

	printf("Manufacturer ID: 0x%x\r\n", rxData[0]);
  printf("Memory Type: 0x%x\r\n", rxData[1]);
  printf("Capacity: 0x%x\r\n", rxData[2]);
	
	char txBuf[50];
  sprintf(txBuf, "Manufacturer ID: 0x%x\r\n", rxData[0]);
  HAL_UART_Transmit(&huart1, (uint8_t *)txBuf, strlen(txBuf), HAL_MAX_DELAY);
  sprintf(txBuf, "Memory Type: 0x%x\r\n", rxData[1]);
  HAL_UART_Transmit(&huart1, (uint8_t *)txBuf, strlen(txBuf), HAL_MAX_DELAY);
  sprintf(txBuf, "Capacity: 0x%x\r\n", rxData[2]);
  HAL_UART_Transmit(&huart1, (uint8_t *)txBuf, strlen(txBuf), HAL_MAX_DELAY);
    
   return *((uint16_t*)rxData + 1);
}
