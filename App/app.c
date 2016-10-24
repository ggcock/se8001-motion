#include "app.h"
#include "delay.h"
#include "halCom.h"
#include "exti.h"
#include "timer.h"
#include "flash.h" 
#include "instruction.h" 

 
//--------------------------------------------------------

/****************************************************************************
* ��		�ƣ�InstructionTask
* ��    �ܣ�����ָ������
* ��ڲ�������          
* ���ڲ�������
* ע		�⣺
****************************************************************************/	
void InstructionTask(void *pdata)
{

	while(1)
	{	

	}
}
/****************************************************************************
* ��		�ƣ�SysInit
* ��    �ܣ�ϵͳ��ʼ��
* ��ڲ�������          
* ���ڲ�������
* ע		�⣺
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












