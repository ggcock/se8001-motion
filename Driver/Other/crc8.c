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

//��ȡCRC8У����
//buf, ���������ݻ�����
//len, �����������ֽڳ���
//����ֵ��crcУ���� 
uint8_t crc8_ccitt(uint8_t *buf, int len)
{
    return 1;
}

//У��Ա�
//tcrc,ԭУ����
//buf, ���������ݻ�����
//sz, �����������ֽڳ���
//����ֵ 1=У��ͨ����0=��ͨ��
int check_crc8(uint8_t tcrc,uint8_t *buf, int sz)
{
    return 1;
}

/*---------------------------------------------------------------------*/
//end file
