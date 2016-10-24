

#include "com_server.h"
#include "halCom.h"
#include "ins_exe.h"


#include "string.h"
#include "stdlib.h"


int ComServerInitial(void)
{ 
	int ret;
	
	halSetComRcvDealFun(SERVER_COM_NUM,halComPushQueue);
	ret = halComInitial(SERVER_COM_NUM,115200);	
	
	return ret;
}



//
int ComServerPeriodicHandle(void)
{
	
	//Ω” ’ª∫≥Â∑«ø’
	while(0 == IsQueueEmpty(&ComRxQ[SERVER_COM_NUM]))
	{
		if(ComRxMsg[SERVER_COM_NUM].length < COM_BUF_MAX)
		ComRxMsg[SERVER_COM_NUM].buf[ComRxMsg[SERVER_COM_NUM].length++] = PopQueue(&ComRxQ[SERVER_COM_NUM]);
		ComRxMsg[SERVER_COM_NUM].buf[ComRxMsg[SERVER_COM_NUM].length] = '\0';
	}

	if(ComRxMsg[SERVER_COM_NUM].length>0)
	{
		InsHandle(ComRxMsg[SERVER_COM_NUM].buf,ComRxMsg[SERVER_COM_NUM].length);
		ComRxMsg[SERVER_COM_NUM].length = 0;
		ComRxMsg[SERVER_COM_NUM].buf[ComRxMsg[SERVER_COM_NUM].length] = '\0';
	}
	
	return 1;
}







