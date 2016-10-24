#include "instruction.h"
#include "frame.h"
#include "usart.h"
#include "app.h"


/****************************************************************************
* ��		�ƣ�InstructionPasre
* ��    �ܣ��򵥵��������
* ��ڲ�����src ���������ַ�����ָ��
*						cmd	�����ַ���
*						pParaList �����б�,����֮��ʹ�ö��Ÿ���
* ���ڲ������������,Ŀǰ����ֻ��������
* ע		�⣺pParaList��Ҫ���ⲿ��֤��Խ�����
*						�����ʽ: command(para1,para2,...)
****************************************************************************/	
s32 InstructionPasre(u8 *src,u8 **pParaList,u8 *paracnt,u8 **cmd)
{
	u8 *p1,*p2,*p;
	
//	p1 = src;
//	
//	//ȥ��ǰ��Ŀո�
//	while(*p1 != '\0')
//	{
//		if(*p1 != ' ')
//			break;
//		
//		p1++;
//	}
//	
//	if(p1 == '\0')
//	{
//		return -1;
//	}
	*cmd = src;
	
	p1 = (u8 *)strchr((const char *)src,'(');
	if(p1 == NULL)
	{
		return -2;
	}
	*p1 = '\0';
	p1++;
	p2 = (u8 *)strchr((const char *)p1,')');
	if(p2 == NULL || p2 == p1 || *p1 == ',')//invalid format
		return -3;
	*p2 = '\0';
	p = p1;
	*paracnt = 0;
	pParaList[*paracnt] = p;
	(*paracnt)++;
	while(p!= p2)
	{
		if(*p == ',')
		{
			*p = '\0';
			pParaList[*paracnt] = p+1;
			(*paracnt)++;
		}
		p++;		
	}
//	para = atoi(p1);
	
	return 1;
}
/****************************************************************************
* ��		�ƣ�ProtocolParse
* ��    �ܣ�ͨ��Э�����
* ��ڲ�����src ���������ַ�����ָ��
* ���ڲ�����
* ע		�⣺
****************************************************************************/	
s8 ProtocolParse(const char *src,u8 *cmd)
{
	s8 err = 1;
	u8 *p1,*p2,*datapr; 
	u8 len,crc;
	
	datapr = (u8 *)0;
	p1 = (u8 *)strchr((const char *)src,SOF0);//find the start flag
	if(p1 == NULL)
	{
		return -1;
	}	
	p2 = p1;
	p1++;
	*cmd = *p1++;

	len = *p1++;
	if(len>0)
		datapr = p1;
	
	crc = p2[len+3];
	err = CRC_Check((u8 *)p2,crc,len+3);
	if(err<0)
	{
		return -2;
	}
	
	switch(*cmd)
	{
		case 1:
			
		break;
		default:break;
	}
	return err;
}






