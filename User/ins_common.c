

#include "ins_common.h"
#include "ins_exe.h"
#include "usart.h"
#include "string.h"
#include "stdlib.h"


_S_InsInfo_t InsList[] = 
{
	{"help",InsHelp,"1.look up the supported command list\r\n"},
	{"relay set",InsRelaySet,"2.relay set(num,on/off);num:relay number\r\n"},
	{"relay get",InsRelayGet,"3.relay get(num);num:relay number\r\n"},
	{"volt get",InsBatVoltGet_Single,"4.volt get(num);num:battery number\r\n"},
	{"pwm freq",InsPwmSetFreq,"5.pwm freq(freq_hz);freq_hz:frequency in hz\r\n"},
	{"pwm duty",InsPwmSetDuty,"6.pwm duty(duty);duty:0-100\r\n"},
	{"pwm out",InsPwmOut,"7.pwm out(on/off)\r\n"},
	{CMD_COM_CFG,InsComCfg,"13.com config(com,baud)\r\n"},
	{CMD_VREF_SET,InsSetVref,"15.vref set(u16)\r\n"},	
	{CMD_VREF_GET,InsGetVref,"16.vref get(1)\r\n"},	
	{NULL,NULL,NULL}//end
};

//use to print the command info
char InsRetString[128];

//------------------------------------------------------

static int InsGetPara(u8 *src,u8 **pParaList,u8 *paracnt,u8 **cmdstr);

//
int InsHandle(u8 *pbuf,u16 length)
{
	int ret;
	u8 i;
	u8 pCnt = 0;
	u8 *pPlist[4],*cmdstr;
	
	memset(InsRetString,0,sizeof(InsRetString));
	
	//command format 
	ret = InsGetPara((u8 *)pbuf,pPlist,&pCnt,&cmdstr);
	//ָ���ʽ����
	if(ret<=0)
	{
		printf("Illegal format!!\r\n");
		return -1;
	}

	//exe
	ret = -2;
	for(i=0;i<INS_COUNT_MAX;i++)
	{
		if(0 == strcmp(InsList[i].InsStr,(const char *)cmdstr))
		{
			if(InsList[i].handle != NULL)
			{
				//ָ��ִ��
				ret = InsList[i].handle(pPlist,pCnt);
				if(ret<0)
				{
					printf("operate failed:%d\r\n",ret);
				}
				//����ִ�н��
				printf("%s",InsRetString);
				break;
			}
		}
		
	}
	//��֧�ָ�ָ��
	if(i == INS_COUNT_MAX)
	{
		printf("command not support!!\r\n");
	}
	
	return ret;
}

/****************************************************************************
* ��		�ƣ�InsGetPara
* ��    �ܣ���ȡ�������
* ��ڲ�����src ���������ַ�����ָ��
*						cmdstr	�����ַ���
*						pParaList �����б�,����֮��ʹ�ö��Ÿ���
* ���ڲ������������,Ŀǰ����ֻ��������
* ע		�⣺pParaList��Ҫ���ⲿ��֤��Խ�����
*						�����ʽ: command(para1,para2,...)
****************************************************************************/	
static int InsGetPara(u8 *src,u8 **pParaList,u8 *paracnt,u8 **cmdstr)
{
	u8 *p1,*p2,*p;
	
	*cmdstr = src;
	
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

	return 1;
}
//-------------------------------------------------------
//ָ�����

//help
int InsHelp(u8 **pplist,u8 pcnt)
{
	u8 i;
	
	printf("help info:\r\n");
	for(i=0;i<INS_COUNT_MAX;i++)
	{
		if(InsList[i].InsStr == NULL)
			break;
		printf("%s",InsList[i].InsNote);
	}
	
	
	return 1;
}











