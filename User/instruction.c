#include "instruction.h"
#include "frame.h"
#include "usart.h"
#include "app.h"


/****************************************************************************
* 名		称：InstructionPasre
* 功    能：简单的命令解析
* 入口参数：src 包含命令字符串的指针
*						cmd	命令字符串
*						pParaList 参数列表,参数之间使用逗号隔开
* 出口参数：命令参数,目前参数只能是整数
* 注		意：pParaList需要由外部保证不越界访问
*						命令格式: command(para1,para2,...)
****************************************************************************/	
s32 InstructionPasre(u8 *src,u8 **pParaList,u8 *paracnt,u8 **cmd)
{
	u8 *p1,*p2,*p;
	
//	p1 = src;
//	
//	//去掉前面的空格
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
* 名		称：ProtocolParse
* 功    能：通信协议解析
* 入口参数：src 包含命令字符串的指针
* 出口参数：
* 注		意：
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






