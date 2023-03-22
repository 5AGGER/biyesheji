#ifndef __W25Q128_H
#define	__W25Q128_H

#include <stdint.h>

//²Ù×÷Ö¸Áî±í
#define W25X_ManufactDeviceID	 0x90       //ÖÆÔìÉÌ+Éè±¸ID

#define W25Q128_CS(a) SPI_CS(a)	

uint8_t W25Q128_ReadWriteByte(uint8_t TxData);//º¯Êý°ü×°Ò»ÏÂ
uint16_t W25Q128_ReadID(void);//¶ÁÈ¡Ð¾Æ¬ID

#endif 
