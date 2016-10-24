/*---------------------------------------------------------------*/
/*
* File name   : xmodem.h
* Author      : neal.deng
* Version     : 1.0.0
* Date        : 
* Description : xmodem协议操作函数包括标准xmodem和1K-xmodem协议
*				校验方式CRC	适用于串口
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
//下载文件
int XmodemReceive(int fd, F_WriteFun_t write_fun,void *arg,uint32_t sz);
//上传文件
int XmodemTransmit(unsigned char *src, int srcsz);
void Xmd_FlushRcvBuffer(int fd);

//转向外部flash
void Xmd_SwitchToFlash(void);
//转向内部Flash
void Xmd_SwitchToFlashIf(void);


#endif
/*----------------------------------------------------------------------*/
//end file
