#ifndef __FLASH_H
#define __FLASH_H	 
#include "system.h"

//用户根据自己的需要设置
#define STM32_FLASH_SIZE 	128 	 		//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 	1        //使能FLASH写入(0，不是能;1，使能)

#define STM32_FLASH_BASE 	0x08000000 	//STM32 FLASH的起始地址
#define FLASH_SAVE_ADDR  	0x0801FC00 
#define PARA_SAVE_ADDR		FLASH_SAVE_ADDR
#define	CAL_BASE_ADDR			(PARA_SAVE_ADDR + 32)


u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据

//测试写入
s8 Test_Write(u32 waddr,u16 wdata);								   

#endif
