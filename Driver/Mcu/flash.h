#ifndef __FLASH_H
#define __FLASH_H	 
#include "system.h"

//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 	128 	 		//��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 	1        //ʹ��FLASHд��(0��������;1��ʹ��)

#define STM32_FLASH_BASE 	0x08000000 	//STM32 FLASH����ʼ��ַ
#define FLASH_SAVE_ADDR  	0x0801FC00 
#define PARA_SAVE_ADDR		FLASH_SAVE_ADDR
#define	CAL_BASE_ADDR			(PARA_SAVE_ADDR + 32)


u16 STMFLASH_ReadHalfWord(u32 faddr);		  //��������  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
s8 Test_Write(u32 waddr,u16 wdata);								   

#endif
