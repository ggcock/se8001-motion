/*---------------------------------------------------------------------*/
/*
* File name    : my_string.c
* Author       : Neal.deng
* Version      : 1.0.3
* Date         : 2015-06-11
* Description  : �ַ���������
* others       :
* FunctionList :
* History      : 
*  1. Date   :  2015-07-11
*     Reason :  strntok_ch_m()��ʹ�÷ָ�ʱ��
                ֻ�ָܷ���ƶ����֣����ܰ�ʣ�ಿ�ֽ������һ������
                eeprom ָ��Ӧ��
*     Author :  Neal.deng
*     Modification:
        1.strntok_ch_m()���ڷָ��м����ж����
        2.strncmp_word_m():1=ƥ��ɹ���0=ƥ��ʧ�� -> 0=ƥ��ɹ���-1=ƥ��ʧ��
*  2. Date   :  2015-07-29
*     Reason :  strntok_ch_m����һ��������Ч
*     Author :  Neal.deng
*     Modification:
        1.strntok_ch_m()��ptmp = strchr(p,',');->ptmp = strchr(p,delim);
*/
/*---------------------------------------------------------------------*/


#include "my_string.h"
//----------------------------------------------

/*------------------------------------------------------------
@��    ��: strnchr_m
@��    ��: ����ĳ�ַ����ַ���ǰlen���ַ����״γ��ֵ�λ�á�
           ��len>�ַ�������,len=�ַ�������
@��ڲ���: 
    str: �ַ���
    len: �ַ���ǰlen���ַ�
    ch:  �������ַ�
@���ڲ���: ��
@�� �� ֵ: 
    �����ַ�����λ�ã�NULL=δ�ҵ�
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
@��    �ƣ� strlench_m
@��    ��   ��ȡ�״γ���ָ���ַ�ǰ���ַ�������,
	ע���������ַ���ǰ��Ŀո��Լ�ָ���ַ�ǰ��Ŀո�
@��ڲ�����	
	src: �ַ���ָ��
	ch:	ָ���ַ�
@���ڲ�������
@����ֵ���ַ�������
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
@��    �ƣ� strncmp_space_m
@��    ��   ������src�ַ���ָ���ַ�ǰ�ո�������ַ����Ƚ�
@��ڲ�����
	ref: �����ַ���ָ��
	src: �ַ���ָ��	
	ch: ָ���ַ�
@���ڲ�������
@����ֵ��
	0=ƥ��ɹ���-1=ƥ��ʧ��
------------------------------------------------------------*/
int strncmp_space_m(const char *ref,const char *src,int ch)
{
    char *p;
    int size=0;
	
    p = (char *)src;
    
    //ȥ���ַ���ǰ��Ŀո�
	while(' ' == *p)
    {
        p++;
    }
    
    //ȥ���ַ���ǰ��Ŀո�
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
@��    ��: strncmp_word_m
@��    ��: ����ƥ�䣬���ȽϿո�
@��ڲ���: 
      pStr1:  �ַ���1
      pStr2:  �ַ���2 
@���ڲ���: ��
@�� �� ֵ:
    0=ƥ��ɹ���-1=ƥ��ʧ��
------------------------------------------------------------*/
int strncmp_word_m(char *pStr1, char* pStr2)
{
    char *str1,*str2;
    
    str1 = pStr1;
    str2 = pStr2;
    
    do{    
        //����һ������,ȥ������ǰ�Ŀո�
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
            
        //�Ƚϵ���
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
@��    ��: strntok_ch_m
@��    ��: ����ָ������ַ����ַ����ָ��ָ����������
           ��ע����ƻ��ַ���������,����ַ���Ϊ'\0',�ָ�ǰ�Ŀո�ȥ��
@��ڲ���: 
    pStr: �������ַ���
    pPart:�ָ��ַ����洢������
    part_size: �ָ��ַ����洢��������С
    delim: �ָ����ַ�
@���ڲ���: 
    pPart[]: ��ȡ���ķָ��ַ���
@�� �� ֵ:
   ʵ�ʷָ������
------------------------------------------------------------*/
int strntok_ch_m(char *pStr, char *pPart[], int part_size, char delim)
{
    int cnt;
    char *p,*ptmp;
    
    //��һ������
    cnt=0;
    p = pStr;
    if(NULL != p)
    {
        for(; cnt<part_size; )
        {
            //ȥ�ո�
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
