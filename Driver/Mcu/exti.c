#include "delay.h"
#include "exti.h"
#include "timer.h"
#include "app.h"
#include "includes.h"


void ExtiInit(void)
{
/*	
	GPIO_InitTypeDef GPIO_InitStructure; 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;	 	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);


	//paulse_in - PA12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);
	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
	NVIC_Init(&NVIC_InitStructure);	
*/
}

void EXTI2_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line2);  
}

void EXTI9_5_IRQHandler(void)
{
	
	if(EXTI_GetITStatus(EXTI_Line5)==SET)
	{  
		EXTI_ClearITPendingBit(EXTI_Line5); 


	}
	
}


void EXTI15_10_IRQHandler(void)
{

	if(EXTI_GetITStatus(EXTI_Line12)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line12);

	}
}


