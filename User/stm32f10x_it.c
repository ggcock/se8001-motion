/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "app.h"

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
	uint32_t r_sp ;
	r_sp = __get_PSP(); //获取SP值 
	printf("\n\r Error : HardFault_Handler %x\r\n",r_sp);
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
	printf("\r\nMemManage!\r\n");
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
	printf("\r\nBusFault!\r\n");
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
	printf("\r\nUsageFault!\r\n");
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
/* 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}
*/
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
//TIM3 general purpose 
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  
		
	}
}
/****************************************************************************
* 名		称：TIM4_IRQHandler
* 功    能：定时器4中断处理
* 入口参数：无          
* 出口参数：无
* 注		意：若产生中断说明云台转速太低了
****************************************************************************/
void TIM4_IRQHandler(void)   
{ 
	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		
	}
}
/****************************************************************************
* 名		称：TIM1_UP_IRQHandler
* 功    能：定时器1计数器中断处理
* 入口参数：无          
* 出口参数：无
* 注		意：
****************************************************************************/
void TIM1_UP_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET) 
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		
		
	}
	
}

//void USART1_IRQHandler(void)                	
//{
//	u8 data;
//	
//	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  
//	{
//		DMA_Cmd(DMA1_Channel5, DISABLE);//关闭DMA，防止干扰	
//		USART_ReceiveData(USART1);//Clear IDLE interrupt flag bit
//		DMA_ClearFlag(DMA1_FLAG_GL5);	
//		rxComBuf.len = COM_BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5);//接收到的字节数
//		rxComBuf.buf[rxComBuf.len]='\0';
//		
//	}
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//	{
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//		data = (USART1->DR & (uint16_t)0x01FF);
//		if(IsQueueFull(&ComRxQ) != 1)
//    {
//        PushQueue(&ComRxQ,(Qdata_t)data);
//    }
//		
//	}
//	
//} 

////usart 发送完成后会进入该中断
//void DMA1_Channel4_IRQHandler(void)
//{
//	u8 busy;
//	
//	if(DMA_GetITStatus(DMA1_FLAG_TC4))
//	{
//			DMA_ClearFlag(DMA1_FLAG_GL4);
//			DMA_Cmd(DMA1_Channel4, DISABLE);
//			
////			SendBuf.pbuf[SendBuf.busy].len = 0;
////			SendBuf.done = 1;
//			sendDoneFlag = 0;
//		
////			busy = (SendBuf.busy == 0) ? 1:0;
////			
////			if(SendBuf.pbuf[busy].len > 0)
////			{
//////				sendDoneFlag = 0;
////				SendBuf.busy = busy; 
////				SendBuf.done = 0;
////				DMA1_Channel4->CMAR=(u32)SendBuf.pbuf[SendBuf.busy].buf;
////				DMA1_Channel4->CPAR=(u32)(&USART1->DR);
////				DMA1_Channel4->CNDTR = SendBuf.pbuf[SendBuf.busy].len;
////				DMA_Cmd(DMA1_Channel4, ENABLE);
////			}

////			OSMboxPost(mbModuleTx, (void*)1);//发送完成标志 
//	}
//}



