#include "system.h"  

OS_STK START_TASK_STK[START_STK_SIZE];
OS_STK INS_TASK_STK[INS_STK_SIZE];

/*------------------------------------------------------------
@名    称: Bsp_NVIC_Configuration
@功    能: 嵌套向量中断控制器重定向设置
@入口参数: 无
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
void NVIC_Configuration(void)
{
    //USEBOOT 为带有bootload程序
#ifdef USEBOOT
	/* Set the Vector Table base location at 0x08004000 */
	/*use update_STM32 command*/
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);
#else
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0);
#endif
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
















