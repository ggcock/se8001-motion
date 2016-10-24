/*---------------------------------------------------------------------*/
/*
* File name   : timer.c
* Author      : wuku.zeng
* Version     : 
* Date        : 2016-04-28
* Description : ��ʱ����غ���
* others      :
* FunctionList:
* History     :
*   1. Date:
*      Reason:
*      Author:
*      Modification:
*/
/*---------------------------------------------------------------------*/
#include "timer.h"
#include "system.h"

//----------------------------------------------------------------------

//-------------------------------------------------------------------------
/****************************************************************************
* ��		�ƣ�TIM1_Init
* ��    �ܣ���ʱ��1��ʼ��,
* ��ڲ�������          
* ���ڲ�������
* ע		�⣺
****************************************************************************/
//��ͨ��ʱ
#if 0
void Tim1Initial(u16 period)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	TIM_DeInit(TIM1);

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000-1); 
	TIM_TimeBaseStructure.TIM_Period = period - 1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�߼���ʱ���������ã�0��ʾÿ������������ж�
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  	

	TIM_ClearITPendingBit(TIM1,TIM_IT_Update); 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM1,DISABLE); 	
}
#endif

#if 0
//PA12 ETR ���������
void Tim1Initial(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 	

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA,ENABLE);
	
	TIM_DeInit(TIM1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_Period = 2; //1����������һ���ж�
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  	

	//TIM_ExtTRGPolarity_NonInverted:trigger operations at high level or rising edge
	TIM_ETRClockMode2Config(TIM1,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0);   
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update); 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM1, 0);    
	TIM_Cmd(TIM1, ENABLE); 	
}
#endif

//TIM1-CH2N,TIM1-CH3N PWM���
void Tim1Initial(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;// 
	TIM_OCInitTypeDef TIM_OCInitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_DeInit(TIM1); 
//PA11  PWM	
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000-1);//Ԥ��Ƶ(ʱ�ӷ�Ƶ)72M/4000=18K
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 9;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);  

	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; 
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period>>1;
	
	//CH2N
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);	
	
	//CH3N
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);	
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); 
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_Cmd(TIM1,DISABLE);
}

//����PWMռ�ձ�
s8 SetT1PwmPulse(u16 pulse) 
{
	u16 tmp = 0;
	tmp = TIM1->ARR;
	if(pulse>100)
	{
		return -1;
	}	
	TIM1->CCR4=(pulse*tmp)/100;  
	return 1;
}
//����PWM����
s8 SetT1PwmPeriod(u16 period) 
{
	u8 per;
	s8 ret;
	
	per = TIM1->CCR4*100/TIM1->ARR;	
	TIM1->ARR = period;	
	ret = SetT1PwmPulse(per);
	if(ret < 0)
	{
		return -1;
	}
	return ret;
}


//-------------------------------------------------------------------------
//tim2,use to supply clk for image sensor 

/****************************************************************************
* ��		�ƣ�TIM2_Init
* ��    �ܣ���ʱ��2��ʼ��
* ��ڲ�������          
* ���ڲ�������
* ע		�⣺TIM2-CH2 output a 18Mhz PWM
****************************************************************************/
TIM_ICInitTypeDef  TIM2_ICInitStructure;
void Tim2Initial(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	
	TIM_DeInit(TIM2); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
//-----------------------------------------------------------	
    /*PCLK1 = 72MHz*/   
    /* Time base configuration */                                            
	TIM_TimeBaseStructure.TIM_Period = 4;  //PWM ����, ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 0;		//Ԥ��Ƶ,������1/72M * 4 = 55.2ns ,��PWMƵ��Լ18MHz 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;		//ʱ�ӷ�Ƶ  (CR1-CK)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  
//-----------------------------------------------------------	
    /* PWM1 Mode configuration: Channel2 */  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//PWMģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 	
	TIM_OCInitStructure.TIM_Pulse = 2;		//�����������������ֵʱ�����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;	//������ֵС��TIM_Pulseʱ�ĵ�ƽ״̬
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	     
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(TIM2, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);//ʹ��PWM���
//-----------------------------------------------------------
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
//	TIM_DMACmd(TIM2, TIM_DMA_CC3, ENABLE); 
	TIM_Cmd(TIM2, ENABLE); 
				
}

//-------------------------------------------------------------------------
/****************************************************************************
* ��		�ƣ�Tim3Initial
* ��    �ܣ���ʱ��3��ʼ��,CH3,CH4���PWM
* ��ڲ�������          
* ���ڲ�������
* ע		�⣺
****************************************************************************/
void Tim3Initial(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_DeInit(TIM3); 
	
	/*PCLK1 = 72MHz*/   
	/* Time base configuration */                                            
	TIM_TimeBaseStructure.TIM_Period =10 - 1;  //PWM ����, ARR 10 * 1us = 10us����PWMƵ��100khz
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000-1);		//Ԥ��Ƶ,������1/72M  = 1us 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ�ӷָ�  (CR1-CK)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
//-----------------------------------------------------------	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 	
	TIM_OCInitStructure.TIM_Pulse = 7;	
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;	//������ֵС��TIM_Pulseʱ�ĵ�ƽ״̬
	
	//CH3
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	     
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	
	//CH4
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	     
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); 
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
  TIM_Cmd(TIM3, ENABLE);  
}

/****************************************************************************
* ��		�ƣ�Tim4Initial
* ��    �ܣ���ʱ��4��ʼ��,CH4���PWM
* ��ڲ�������          
* ���ڲ�������
* ע		�⣺
****************************************************************************/
void Tim4Initial(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  
  TIM_DeInit(TIM4);
  
	TIM_TimeBaseStructure.TIM_Period = 10 - 1;//20ms �ж�һ��
  TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000-1); //72��Ƶ,��1us TIM4->CNT ��1
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//-----------------------------------------------------------	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 	
	TIM_OCInitStructure.TIM_Pulse = 7;	
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;	
	
	//CH4
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);	     
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  
	 
	TIM_ARRPreloadConfig(TIM4, ENABLE); 
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
  TIM_Cmd(TIM4, ENABLE); 
}

//TIM8 CH1,CH2,CH3���ں������
void Tim8Initial(void)
{
	
	
}

void TimerInitial(void)
{
	Tim4Initial();
	Tim1Initial();	
	Tim2Initial();
	Tim3Initial();
}



