/*---------------------------------------------------------------------*/
/*
* File name   : crc16.h
* Author      : Neal.deng
* Version     : 1.0.0
* Date        : 2014-10-28
* Description : crc16
* others      :
* FunctionList:
* History     :
*   1. Date:
*      Reason:
*      Author:
*      Modification:
*/
/*---------------------------------------------------------------------*/

#ifndef _CRC16_H
#define _CRC16_H

//获取CRC16校验码
//buf, 待计算数据缓冲区
//len, 待计算数据字节长度
//返回值，crc校验码 
unsigned short crc16_ccitt(const char *buf, int len);

//校验对比
//tcrc,原校验码
//buf, 待计算数据缓冲区
//sz, 待计算数据字节长度
//返回值 1=校验通过，0=不通过
int check_crc(unsigned short tcrc,const unsigned char *buf, int sz);
#endif
/*-------------------------------end file--------------------------------------*/

