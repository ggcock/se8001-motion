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

//��ȡCRC16У����
//buf, ���������ݻ�����
//len, �����������ֽڳ���
//����ֵ��crcУ���� 
unsigned short crc16_ccitt(const char *buf, int len);

//У��Ա�
//tcrc,ԭУ����
//buf, ���������ݻ�����
//sz, �����������ֽڳ���
//����ֵ 1=У��ͨ����0=��ͨ��
int check_crc(unsigned short tcrc,const unsigned char *buf, int sz);
#endif
/*-------------------------------end file--------------------------------------*/

