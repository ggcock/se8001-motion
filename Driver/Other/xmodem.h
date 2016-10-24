/*---------------------------------------------------------------*/
/*
* File name   : xmodem.h
* Author      : neal.deng
* Version     : 1.0.0
* Date        : 
* Description : xmodemЭ���������������׼xmodem��1K-xmodemЭ��
*				У�鷽ʽCRC	�����ڴ���
* others      :
* FunctionList:
* History     :
*   1. Date:
*      Reason:
*      Author:
*      Modification: 
*/
/*---------------------------------------------------------------*/

#ifndef _XMODEM_H
#define _XMODEM_H

#include <stdint.h>
//----------------------------------------------

typedef struct{
	uint32_t addr;
	uint8_t remsize;
	uint8_t remByte[4];
}S_Xmd_t;
//-----------------------------------------------

typedef void(*F_WriteFun_t)(void *arg,void *data,uint32_t len);
//�����ļ�
int XmodemReceive(int fd, F_WriteFun_t write_fun,void *arg,uint32_t sz);
//�ϴ��ļ�
int XmodemTransmit(unsigned char *src, int srcsz);
void Xmd_FlushRcvBuffer(int fd);

//ת���ⲿflash
void Xmd_SwitchToFlash(void);
//ת���ڲ�Flash
void Xmd_SwitchToFlashIf(void);


#endif
/*----------------------------------------------------------------------*/
//end file
