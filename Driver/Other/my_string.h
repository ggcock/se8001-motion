/*---------------------------------------------------------------------*/
/*
* File name    : my_string.h
* Author       : Neal.deng
* Version      : 1.0.0
* Date         : 2015-06-12
* Description  : �ַ���������
* others       :
* FunctionList :
* History      : 
*  1. Date   :
*     Reason :
*     Author :
*     Modification:
*/
/*---------------------------------------------------------------------*/

#ifndef _MY_STRING_H
#define _MY_STRING_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//-------------------------------------------

//����ĳ�ַ����ַ���ǰlen���ַ����״γ��ֵ�λ��
char *strnchr_m(const char *str,uint32_t len, int ch);
//��ȡ�״γ���ָ���ַ�ǰ���ַ�������,
//ע���������ַ���ǰ��Ŀո��Լ�ָ���ַ�ǰ��Ŀո�
int strlench_m(const char *src, int ch);

//������src�ַ���ָ���ַ�ǰ��ո�������ַ����Ƚ�
int strncmp_space_m(const char *ref,const char *src,int ch);
//����ƥ�䣬���ȽϿո�
int strncmp_word_m(char *pStr1, char* pStr2);
//����ָ������ַ����ַ����ָ��ָ����������
//��ע����ƻ��ַ���������,����ַ���Ϊ'\0'
int strntok_ch_m(char *pStr, char *pPart[], int part_size, char delim);
#endif
/*---------------------------------------------------------------------*/
//end file
