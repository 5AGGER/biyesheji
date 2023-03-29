#include "W25Q128.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi1;	


int32_t read_W25Q128_ID(void)
{
  uint8_t command = 0x9F;
  uint8_t id[3];

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); 
  HAL_SPI_Transmit(&hspi1, &command, 1, HAL_MAX_DELAY); 
	HAL_Delay(1);
  HAL_SPI_Receive(&hspi1, id, 3, HAL_MAX_DELAY);       
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);  

  uint32_t result = (id[0] << 16) | (id[1] << 8) | id[2];
  return result;

}

//next

void W25Q128_Init(void) 
	{
     HAL_Delay(100);//
  }

void W25Q128_WaitForWriteEnd(SPI_HandleTypeDef *hspi1) {
  uint8_t status = 0;
  uint8_t cmd[] = {W25Q128_CMD_READ_STATUS_REG1};

  do {
    HAL_SPI_Transmit(hspi1, cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(hspi1, &status, 1, HAL_MAX_DELAY);
  } while (status & W25Q128_WIP_FLAG);
}
  HAL_StatusTypeDef W25Q128_EraseSector(SPI_HandleTypeDef *hspi1, uint32_t address) {
  uint8_t cmd[4] = {W25Q128_CMD_WRITE_ENABLE};
  HAL_StatusTypeDef status;

  status = HAL_SPI_Transmit(hspi1, cmd, 1, HAL_MAX_DELAY);
  if (status != HAL_OK) return status;

  cmd[0] = W25Q128_CMD_SECTOR_ERASE;
  cmd[1] = (address >> 16) & 0xFF;
  cmd[2] = (address >> 8) & 0xFF;
  cmd[3] = address & 0xFF;

  status = HAL_SPI_Transmit(hspi1, cmd, 4, HAL_MAX_DELAY);
  if (status != HAL_OK) return status;

  W25Q128_WaitForWriteEnd(hspi1);
  
  return HAL_OK;
}
	HAL_StatusTypeDef W25Q128_WritePage(SPI_HandleTypeDef *hspi1, uint8_t *buffer, uint32_t address, uint16_t size) {
  uint8_t cmd[4] = {W25Q128_CMD_WRITE_ENABLE};
  HAL_StatusTypeDef status;

  status = HAL_SPI_Transmit(hspi1, cmd, 1, HAL_MAX_DELAY);
  if (status != HAL_OK) return status;

  cmd[0] = W25Q128_CMD_PAGE_PROGRAM;
  cmd[1] = (address >> 16) & 0xFF;
  cmd[2] = (address >> 8) & 0xFF;
  cmd[3] = address & 0xFF;
	
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
  
	status = HAL_SPI_Transmit(hspi1, cmd, 4, HAL_MAX_DELAY);
  if (status != HAL_OK) return status;

  status = HAL_SPI_Transmit(hspi1, buffer, size, HAL_MAX_DELAY);
  if (status != HAL_OK) return status;
	
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
  
	W25Q128_WaitForWriteEnd(hspi1);
  
	return HAL_OK;
}
	HAL_StatusTypeDef W25Q128_ReadPage(SPI_HandleTypeDef *hspi1, uint8_t *buffer, uint32_t address, uint16_t size) {
  uint8_t cmd[4] = {W25Q128_CMD_READ_DATA, (address >> 16) & 0xFF, (address >> 8) & 0xFF, address & 0xFF};
  HAL_StatusTypeDef status;
	
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
  
	status = HAL_SPI_Transmit(hspi1, cmd, 4, HAL_MAX_DELAY);
  if (status != HAL_OK) return status;

  status = HAL_SPI_Receive(hspi1, buffer, size, HAL_MAX_DELAY);
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
  
	return status;
}
