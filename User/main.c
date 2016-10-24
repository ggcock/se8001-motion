#include "app.h"  
#include "system.h" 
#include "usart.h" 
 
void StartTask(void *pdata);

int main(void)
{	 
	
	
	NVIC_Configuration();
	
	OSInit();  	 			
	OSTaskCreate(StartTask,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );
	OSStart();	
  
}

//开始任务
void StartTask(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	pdata = pdata; 		  
	
	SysInit();
//	OSStatInit();		
		
 	OS_ENTER_CRITICAL();			 	 				   

	OSTaskCreate(InstructionTask,(void *)0,(OS_STK*)&INS_TASK_STK[INS_STK_SIZE-1],INS_TASK_PRIO);	
	
	OS_EXIT_CRITICAL();	

	while(1)
	{
		OSTimeDlyHMSM(0,0,0,500);
		OSTaskDel(START_TASK_PRIO);
	}

	
}	
