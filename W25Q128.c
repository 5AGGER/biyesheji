#include "W25Q128.h"
#include "SPI.h"

uint8_t W25Q128_ReadWriteByte(uint8_t TxData)//º¯Êý°ü×°Ò»ÏÂ
{     
 	  return SPI1_ReadWriteByte(TxData); 		
}

uint16_t W25Q128_ReadID(void)//¶ÁÈ¡Ð¾Æ¬ID
{
	uint16_t Temp = 0;	  
	W25Q128_CS(0);				    
	W25Q128_ReadWriteByte(W25X_ManufactDeviceID);//·¢ËÍ¶ÁÈ¡IDÃüÁî	    
	W25Q128_ReadWriteByte(0x00); 	    
	W25Q128_ReadWriteByte(0x00); 	    
	W25Q128_ReadWriteByte(0x00); 	 			   
	Temp|=W25Q128_ReadWriteByte(0xFF)<<8;  
	Temp|=W25Q128_ReadWriteByte(0xFF);	 
	W25Q128_CS(1);				    
	return Temp;
}

