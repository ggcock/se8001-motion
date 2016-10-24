#include "app.h"
#include "delay.h"
#include "halCom.h"
#include "exti.h"
#include "timer.h"
#include "flash.h" 
#include "instruction.h" 

 
//--------------------------------------------------------

/****************************************************************************
* 名		称：InstructionTask
* 功    能：串口指令任务
* 入口参数：无          
* 出口参数：无
* 注		意：
****************************************************************************/	
void InstructionTask(void *pdata)
{

	while(1)
	{	

	}
}
/****************************************************************************
* 名		称：SysInit
* 功    能：系统初始化
* 入口参数：无          
* 出口参数：无
* 注		意：
****************************************************************************/	
s8 SysInit(void)
{
	s8 err = 1;
	
	NVIC_Configuration(); 
	DelayInitial();
	halComInitial(COM1_NUM,115200);	
	TimerInitial(); 
	DelayMs(1);
	
#if DEBUG>0
	printf("\r\n-----------------------\r\n");
	printf("%s\r\n",__DATE__);
	printf("%s\r\n",__TIME__);
	printf("-----------------------\r\n");		
#endif 

	
	return err;
}












