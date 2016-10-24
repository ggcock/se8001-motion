#include "system.h"  

OS_STK START_TASK_STK[START_STK_SIZE];
OS_STK INS_TASK_STK[INS_STK_SIZE];

/*------------------------------------------------------------
@��    ��: Bsp_NVIC_Configuration
@��    ��: Ƕ�������жϿ������ض�������
@��ڲ���: ��
@���ڲ���: ��
@�� �� ֵ: ��
------------------------------------------------------------*/
void NVIC_Configuration(void)
{
    //USEBOOT Ϊ����bootload����
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

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//���������ж�
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
















