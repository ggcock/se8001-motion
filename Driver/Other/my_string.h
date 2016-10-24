/*---------------------------------------------------------------------*/
/*
* File name    : my_string.h
* Author       : Neal.deng
* Version      : 1.0.0
* Date         : 2015-06-12
* Description  : 字符串处理函数
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

//查找某字符在字符串前len个字符中首次出现的位置
char *strnchr_m(const char *str,uint32_t len, int ch);
//获取首次出现指定字符前的字符串长度,
//注：不计算字符串前面的空格以及指定字符前面的空格
int strlench_m(const char *src, int ch);

//不计算src字符串指定字符前后空格与参照字符串比较
int strncmp_space_m(const char *ref,const char *src,int ch);
//单词匹配，不比较空格
int strncmp_word_m(char *pStr1, char* pStr2);
//根据指定间隔字符对字符串分割成指定数量部分
//：注意会破坏字符串完整性,间隔字符变为'\0'
int strntok_ch_m(char *pStr, char *pPart[], int part_size, char delim);
#endif
/*---------------------------------------------------------------------*/
//end file
