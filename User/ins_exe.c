
#include "ins_exe.h"
#include "ins_common.h"
#include "halCom.h"
#include "string.h"
#include "stdlib.h"

extern char InsRetString[128];

//setting the relays
int InsRelaySet(u8 **pplist,u8 pcnt)
{
	int ptemp;
	int ret = 0;
	
	if(pcnt != 2)
	{
		return PARA_ERR;
	}
	
	ptemp = atoi((const char *)pplist[0]);
	if(strcmp((const char *)pplist[1],(const char *)PARA_SWCH_ON) == 0)
	{
//		ret = RelaySet(ptemp);
	}
	else if(strcmp((const char *)pplist[1],(const char *)PARA_SWCH_OFF) == 0)
	{
//		ret = RelayReset(ptemp);
	}	
	
	if(ret<0)
		return DONE_ERR + ret;
	return ret;
}

//read the relays
int InsRelayGet(u8 **pplist,u8 pcnt)
{
	int ptemp;
	int ret = 0;
	u8 status;
		
	if(pcnt != 1)
	{
		return PARA_ERR;
	}
	
	
	ptemp = atoi((const char *)pplist[0]);
//	ret = RelayStatusRead(ptemp,&status);
	if(ret>0)
	{
		//断开(常闭端)
		if(status>0)
		{
			sprintf(InsRetString,"relay %d disconnect!\r\n",ptemp);
		}
		else
		{
			sprintf(InsRetString,"relay %d connected!\r\n",ptemp);
		}
	}	
	else
	{
		return DONE_ERR + ret;
	}
	
	return ret;
}

//read one battery volt
int InsBatVoltGet_Single(u8 **pplist,u8 pcnt)
{
	int ptemp;
	int ret = 0;
	u16 volt;

	if(pcnt != 1)
	{
		return PARA_ERR;
	}
	
	ptemp = atoi((const char *)pplist[0]);
//	ret = BatGetVolt_Single(ptemp,&volt);
	if(ret>0)
	{
		sprintf(InsRetString,"battery %d is:%d mV.\r\n",ptemp,volt);
	}	
	else
	{
		return DONE_ERR + ret;
	}
	
	return ret;
}

//set the pwm frequency
int InsPwmSetFreq(u8 **pplist,u8 pcnt)
{
	int ptemp;
	int ret = 0;	

	if(pcnt != 1)
	{
		return PARA_ERR;
	}
	
	ptemp = atoi((const char *)pplist[0]);
//	ret = PwmSetFreq(ptemp);
	if(ret<0)
	{
		return DONE_ERR + ret;
	}
		
	return ret;
}

//set the pwm duty
int InsPwmSetDuty(u8 **pplist,u8 pcnt)
{
	int ptemp;
	int ret = 0;	

	if(pcnt != 1)
	{
		return PARA_ERR;
	}
	
	ptemp = atoi((const char *)pplist[0]);
	if(ptemp>100)
	{
		ret = PARA_ERR + 1;
	}
	else
	{
//		ret = PwmSetDuty(ptemp);
	}
	if(ret<0)
	{
		return DONE_ERR + ret;
	}
	
	return ret;
}

//set the pwm Out
int InsPwmOut(u8 **pplist,u8 pcnt)
{
	int ret;	

	if(pcnt != 1)
	{
		return PARA_ERR;
	}
	
	if(strcmp((const char *)pplist[0],(const char *)PARA_SWCH_ON) == 0)
	{
//		ret = PwmStart();
	}
	else if(strcmp((const char *)pplist[0],(const char *)PARA_SWCH_OFF) == 0)
	{
//		ret = PwmStop();
	}	
	else
	{
		return PARA_ERR + 1;
	}
	if(ret<0)
	{
		return DONE_ERR + ret;
	}	
	
	return ret;
}

//串口波特率配置
int InsComCfg(u8 **pplist,u8 pcnt)
{
	int ret;	
	u8 com;
	u32 baud;

	if(pcnt != 2)
	{
		return PARA_ERR;
	}
	
	com = atoi((const char *)pplist[0]);
	if(com >= COMn)
	{
		return PARA_ERR + 1;
	}
	baud = atoi((const char *)pplist[1]);

	ret = halComInitial((E_COM_t)com,baud);
	
	return ret;	
}



//设置ADC参考电压 +
int InsSetVref(u8 **pplist,u8 pcnt)
{
//	u16 temp;
//	
//	if(pcnt != 1)
//	{
//		return PARA_ERR;
//	}
//	
//	temp = atoi((const char *)pplist[0]);
////	SetVref(temp);

	return 1;
}

//读取ADC参考电压
int InsGetVref(u8 **pplist,u8 pcnt)
{
	u16 temp;
	
	temp = atoi((const char *)pplist[0]);
//	temp = GetVref();
	sprintf(InsRetString,"Vref+:%dmv\r\n",temp);	
	
	return 1;
}





