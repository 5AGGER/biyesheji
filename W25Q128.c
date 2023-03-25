#include "W25Q128.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi1;	


uint32_t read_W25Q128_ID(void)
{
  uint8_t command = 0x9F;
  uint8_t id[3];

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 
  HAL_SPI_Transmit(&hspi1, &command, 1, HAL_MAX_DELAY); 
  HAL_SPI_Receive(&hspi1, id, 3, HAL_MAX_DELAY);       
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);  

  uint32_t result = (id[0] << 16) | (id[1] << 8) | id[2];
  return result;

}
