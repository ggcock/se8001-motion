/*---------------------------------------------------------------------*/
/*
* File name    : my_string.c
* Author       : Neal.deng
* Version      : 1.0.3
* Date         : 2015-06-11
* Description  : 字符串处理函数
* others       :
* FunctionList :
* History      : 
*  1. Date   :  2015-07-11
*     Reason :  strntok_ch_m()在使用分割时，
                只能分割出制定部分，不能把剩余部分接在最后一部分上
                eeprom 指令应用
*     Author :  Neal.deng
*     Modification:
        1.strntok_ch_m()：在分割中加入判断语句
        2.strncmp_word_m():1=匹配成功，0=匹配失败 -> 0=匹配成功，-1=匹配失败
*  2. Date   :  2015-07-29
*     Reason :  strntok_ch_m函数一个参数无效
*     Author :  Neal.deng
*     Modification:
        1.strntok_ch_m()：ptmp = strchr(p,',');->ptmp = strchr(p,delim);
*/
/*---------------------------------------------------------------------*/


#include "my_string.h"
//----------------------------------------------

/*------------------------------------------------------------
@名    称: strnchr_m
@功    能: 查找某字符在字符串前len个字符中首次出现的位置。
           若len>字符串长度,len=字符串长度
@入口参数: 
    str: 字符串
    len: 字符串前len个字符
    ch:  待查找字符
@出口参数: 无
@返 回 值: 
    查找字符出现位置，NULL=未找到
------------------------------------------------------------*/
char *strnchr_m(const char *str,uint32_t len, int ch)
{
    char *p;
    uint32_t cnt=0;
    
    p = (char *)str;
    
    while(cnt<len)
    {
        if(p[cnt] == ch)
        {
            return &p[cnt];
        }
        else if('\0' == p[cnt])
        {
            return NULL;
        }
        cnt++;
    }
    
    return NULL;
}

/*------------------------------------------------------------
@名    称： strlench_m
@功    能   获取首次出现指定字符前的字符串长度,
	注：不计算字符串前面的空格以及指定字符前面的空格
@入口参数：	
	src: 字符串指针
	ch:	指定字符
@出口参数：无
@返回值：字符串长度
------------------------------------------------------------*/
int strlench_m(const char *src, int ch)
{
    char *p;
    int size=0;
    
    p = (char *)src;
    while(' ' == *p)
    {
        p++;
    }
	
    while(('\0' != *p)&&(ch != *p)&&(' ' != *p))
    {
        size++;
        p++;
    }
	
    return size;
}

/*------------------------------------------------------------
@名    称： strncmp_space_m
@功    能   不计算src字符串指定字符前空格与参照字符串比较
@入口参数：
	ref: 参照字符串指针
	src: 字符串指针	
	ch: 指定字符
@出口参数：无
@返回值：
	0=匹配成功，-1=匹配失败
------------------------------------------------------------*/
int strncmp_space_m(const char *ref,const char *src,int ch)
{
    char *p;
    int size=0;
	
    p = (char *)src;
    
    //去除字符串前面的空格
	while(' ' == *p)
    {
        p++;
    }
    
    //去除字符串前面的空格
	while(' ' == *ref)
    {
        ref++;
    }
    
    size = strlench_m(p,ch);
	
    if((size == strlen(ref))&&(0 == strncmp(p,ref,strlen(ref))))
    {
        return 0;
    }
    return -1;
}


/*------------------------------------------------------------
@名    称: strncmp_word_m
@功    能: 单词匹配，不比较空格
@入口参数: 
      pStr1:  字符串1
      pStr2:  字符串2 
@出口参数: 无
@返 回 值:
    0=匹配成功，-1=匹配失败
------------------------------------------------------------*/
int strncmp_word_m(char *pStr1, char* pStr2)
{
    char *str1,*str2;
    
    str1 = pStr1;
    str2 = pStr2;
    
    do{    
        //找下一个单词,去掉单词前的空格
        if(*str1 != '\0')
        {
            while(' ' == *str1)
                str1++;
        }
        
        if(*str2 != '\0')
        {
            while(' ' == *str2)
                str2++;
        }
            
        //比较单词
        while((*str1 != ' ')&&(*str1 != '\0')&&(*str2 != '\0'))
        {
            if(*str1 != *str2)
                return -1;
            str1++;
            str2++;
        }
        
        if(*str1 != *str2)
        {
            if('\0' == *str2)
            {
                while(' ' == *str1)
                    str1++;
                if(*str1 != '\0')
                    return -1;
            }
            else if('\0' == str1)
            {
                while(' ' == *str2)
                    str2++;
                if(*str2 != '\0')
                    return -1;
            }
            else
                return -1;
        }
        
    }while((*str2 != '\0')&&(*str1 != '\0')); 
    
    return 0;
}


/*------------------------------------------------------------
@名    称: strntok_ch_m
@功    能: 根据指定间隔字符对字符串分割成指定数量部分
           ：注意会破坏字符串完整性,间隔字符变为'\0',分隔前的空格去掉
@入口参数: 
    pStr: 待处理字符串
    pPart:分割字符串存储缓冲区
    part_size: 分割字符串存储缓冲区大小
    delim: 分割间隔字符
@出口参数: 
    pPart[]: 提取到的分割字符串
@返 回 值:
   实际分割部分数量
------------------------------------------------------------*/
int strntok_ch_m(char *pStr, char *pPart[], int part_size, char delim)
{
    int cnt;
    char *p,*ptmp;
    
    //第一个参数
    cnt=0;
    p = pStr;
    if(NULL != p)
    {
        for(; cnt<part_size; )
        {
            //去空格
            while(' ' == *p)
                p++;
            if('\0' == *p)
                return cnt;
            
            pPart[cnt++] = p;
            ptmp = strchr(p,delim);
            if(NULL == ptmp)
            {
                return cnt;
            }
            else
            {
                if(cnt<part_size)
                {
                    p = ptmp; 
                    *p = '\0';
                    p++;
                }
            }
        }
    }
    
    return cnt;
}



/*---------------------------------------------------------------------*/
//end file
