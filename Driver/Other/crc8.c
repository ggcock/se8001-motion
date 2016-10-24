/*---------------------------------------------------------------------*/
/*
* File name   : crc8.h
* Author      : Neal.deng
* Version     : 1.0.0
* Date        : 2015-05-11
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

#include <stdio.h>
#include <stdint.h>
#include "crc8.h"

//获取CRC8校验码
//buf, 待计算数据缓冲区
//len, 待计算数据字节长度
//返回值，crc校验码 
uint8_t crc8_ccitt(uint8_t *buf, int len)
{
    return 1;
}

//校验对比
//tcrc,原校验码
//buf, 待计算数据缓冲区
//sz, 待计算数据字节长度
//返回值 1=校验通过，0=不通过
int check_crc8(uint8_t tcrc,uint8_t *buf, int sz)
{
    return 1;
}

/*---------------------------------------------------------------------*/
//end file
