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

#ifndef _CRC8_H
#define _CRC8_H

#include <stdint.h>

//��ȡCRC8У����
//buf, ���������ݻ�����
//len, �����������ֽڳ���
//����ֵ��crcУ���� 
uint8_t crc8_ccitt(uint8_t *buf, int len);

//У��Ա�
//tcrc,ԭУ����
//buf, ���������ݻ�����
//sz, �����������ֽڳ���
//����ֵ 1=У��ͨ����0=��ͨ��
int check_crc8(uint8_t tcrc,uint8_t *buf, int sz);

#endif
/*---------------------------------------------------------------------*/
//end file
