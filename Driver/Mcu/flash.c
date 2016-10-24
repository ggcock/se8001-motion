#include "flash.h"

// void FlashInit(void)
// {
// 	
// }

// s8 FlashWrite(u16 *buf, u16 len)
// {
// 	u16 i;
// 	
// 	FLASH_Unlock();
// 	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|\
// 						FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
// 	FLASH_Status = FLASH_ErasePage(SAVE_ADDR);
// 	if(FLASH_Status != FLASH_COMPLETE)
// 		return -1;
// 	for(i=0;i++;i<len)
// 	{
// 		FLASH_Status = FLASH_ProgramHalfWord(SAVE_ADDR+(i<<1),*buf);
// 		buf++;
// 		if(FLASH_Status != FLASH_COMPLETE)
// 			return -2;
// 	}
// // 	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|\
// // 						FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
// 	FLASH_Lock();
// 	return 1;
// }

/****************************************************************************
* ��	  �ƣ�STMFLASH_ReadHalfWord 
* ��    �ܣ���ȡָ����ַ�İ���(16λ����)
* ��ڲ�����faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
* ���ڲ�������Ӧ����.
****************************************************************************/
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}
/****************************************************************************
* ��	  �ƣ�STMFLASH_Read 
* ��    �ܣ���ָ����ַ��ʼ����ָ�����ȵ�����
* ��ڲ�����ReadAddr:��ʼ��ַ
*						pBuffer:����ָ��
*						NumToRead:����(16λ)��
* ���ڲ�����
****************************************************************************/
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}

/****************************************************************************
* ��	  �ƣ�STMFLASH_Write_NoCheck 
* ��    �ܣ�������д��
* ��ڲ�����WriteAddr:��ʼ��ַ
*						pBuffer:����ָ��
*						NumToWrite:����(16λ)��  
* ���ڲ�����
****************************************************************************/
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	  WriteAddr+=2;//��ַ����2.
	}  
} 
/****************************************************************************
* ��	  �ƣ�STMFLASH_Write 
* ��    �ܣ���ָ����ַ��ʼд��ָ�����ȵ�����
* ��ڲ�����WriteAddr:��ʼ��ַ
*						pBuffer:����ָ��
*						NumToWrite:����(16λ)��  
* ���ڲ�����
****************************************************************************/
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //�ֽ�
#else 
#define STM_SECTOR_SIZE	2048
#endif		
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];//�����2K�ֽ�
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //������ַ
	u16 secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	u16 secremain; //������ʣ���ַ(16λ�ּ���)	   
 	u16 i;    
	u32 offaddr;   //ȥ��0x08000000��ĵ�ַ
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))
		return;//�Ƿ���ַ
	FLASH_Unlock();						//����
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);	
	offaddr=WriteAddr-STM32_FLASH_BASE;		//ʵ��ƫ�Ƶ�ַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
	if(NumToWrite<=secremain)
		secremain=NumToWrite;//�����ڸ�������Χ
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)
				break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//�����������
			for(i=0;i<secremain;i++)//����
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
		}
		else 
			STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumToWrite==secremain)
			break;//д�������
		else//д��δ����
		{
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		  pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
		  NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))
				secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else 
				secremain=NumToWrite;//��һ����������д����
		}	 
	}	
	FLASH_Lock();//����
}
s8 Test_Write(u32 waddr,u16 wdata)   	
{
	u16 temp;
	u16 old;
	
	STMFLASH_Read(waddr,&old,1);
	STMFLASH_Write(waddr,&wdata,1);
	STMFLASH_Read(waddr,&temp,1);
	STMFLASH_Write(waddr,&old,1);
	if(temp == wdata)
		return TRUE;
	else 
		return FALSE;
}


