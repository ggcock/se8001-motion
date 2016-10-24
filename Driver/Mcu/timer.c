/*---------------------------------------------------------------------*/
/*
* File name   : timer.c
* Author      : wuku.zeng
* Version     : 
* Date        : 2016-04-28
* Description : 定时器相关函数
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
* 名		称：TIM1_Init
* 功    能：定时器1初始化,
* 入口参数：无          
* 出口参数：无
* 注		意：
****************************************************************************/
//普通定时
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
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//高级定时器必须设置，0表示每次溢出都产生中断
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  	

	TIM_ClearITPendingBit(TIM1,TIM_IT_Update); 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM1,DISABLE); 	
}
#endif

#if 0
//PA12 ETR 脉冲计数器
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
	TIM_TimeBaseStructure.TIM_Period = 2; //1个脉冲后产生一个中断
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

//TIM1-CH2N,TIM1-CH3N PWM输出
void Tim1Initial(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;// 
	TIM_OCInitTypeDef TIM_OCInitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_DeInit(TIM1); 
//PA11  PWM	
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000-1);//预分频(时钟分频)72M/4000=18K
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
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

//设置PWM占空比
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
//设置PWM周期
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
* 名		称：TIM2_Init
* 功    能：定时器2初始化
* 入口参数：无          
* 出口参数：无
* 注		意：TIM2-CH2 output a 18Mhz PWM
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
	TIM_TimeBaseStructure.TIM_Period = 4;  //PWM 周期, ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 0;		//预分频,周期是1/72M * 4 = 55.2ns ,即PWM频率约18MHz 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;		//时钟分频  (CR1-CK)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  
//-----------------------------------------------------------	
    /* PWM1 Mode configuration: Channel2 */  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//PWM模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 	
	TIM_OCInitStructure.TIM_Pulse = 2;		//当计数器计数到这个值时输出电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;	//当计数值小于TIM_Pulse时的电平状态
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	     
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(TIM2, ENABLE); //使能TIMx在ARR上的预装载寄存器	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);//使能PWM输出
//-----------------------------------------------------------
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
//	TIM_DMACmd(TIM2, TIM_DMA_CC3, ENABLE); 
	TIM_Cmd(TIM2, ENABLE); 
				
}

//-------------------------------------------------------------------------
/****************************************************************************
* 名		称：Tim3Initial
* 功    能：定时器3初始化,CH3,CH4输出PWM
* 入口参数：无          
* 出口参数：无
* 注		意：
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
	TIM_TimeBaseStructure.TIM_Period =10 - 1;  //PWM 周期, ARR 10 * 1us = 10us，即PWM频率100khz
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000-1);		//预分频,周期是1/72M  = 1us 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分割  (CR1-CK)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
//-----------------------------------------------------------	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 	
	TIM_OCInitStructure.TIM_Pulse = 7;	
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;	//当计数值小于TIM_Pulse时的电平状态
	
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
* 名		称：Tim4Initial
* 功    能：定时器4初始化,CH4输出PWM
* 入口参数：无          
* 出口参数：无
* 注		意：
****************************************************************************/
void Tim4Initial(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  
  TIM_DeInit(TIM4);
  
	TIM_TimeBaseStructure.TIM_Period = 10 - 1;//20ms 中断一次
  TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000-1); //72分频,即1us TIM4->CNT 加1
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

//TIM8 CH1,CH2,CH3用于红外解码
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



