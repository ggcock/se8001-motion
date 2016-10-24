

//串口硬件抽象层
#include "halCom.h"
#include "queue.h"


//串口实例对象
extern USART_TypeDef* COM_USART[COMn];
//串口波特率
extern const uint32_t COM_USART_BAUD[COMn];
//串口发送中断标志
extern const uint32_t DMA_TX_ITFlag[COMn];

//串口发送DMA通道 
extern DMA_Channel_TypeDef *DMA_TX_CHN[COMn];
//串口接收DMA通道
extern DMA_Channel_TypeDef *DMA_RX_CHN[COMn];
//串口发送中断标志
extern const uint32_t DMA_TX_ITFlag[COMn];
//串口接收中断标志
extern const uint32_t DMA_RX_ITFlag[COMn];
	
//串口发送完成标志(DMA)
extern uint8_t COM_TX_DONE[COMn]; 
//串口接收完成标志
extern uint8_t COM_RX_DONE[COMn];
	
S_Queue_t	ComRxQ[COMn];
//应用层接收处理函数
F_ComRcvFun_t ComRcvFun[COMn]={NULL,NULL,NULL,NULL};

OS_EVENT *SemComRcvNewData[COMn];


int halComInitial(E_COM_t com,uint32_t baud)
{
	QueueInitial(&ComRxQ[com]);
	ComRxMsg[com].length = 0;	
	SemComRcvNewData[com] = OSSemCreate(0);

	UsartInitial(com,COM_USART_BAUD[com]);
	
	return 1;
}

/*------------------------------------------------------------
@名    称: COM_PushQueue
@功    能: COM接收数据处理函数：
           压入队列中:向串口接收队列增添数据
@入口参数:
      com: 串口映射号
     pBuf: 待发送数据缓冲区首地址
      fmt: 格式化字符串
@出口参数: 无
@返 回 值: 发送数据字节长度
------------------------------------------------------------*/
void halComPushQueue(E_COM_t com, char data)
{
	
    if(&ComRxQ[com] == NULL)
    {
        return;
    }
	
    if(IsQueueFull(&ComRxQ[com]) != 1)
    {
        PushQueue(&ComRxQ[com],(Qdata_t)data);
    }
    else
    {
        printf("Seeing com: COM%d queue overflow.\r\n",(int)com);
        //在取消息指令中做恢复处理
    }

}

/*------------------------------------------------------------
@名    称: SetComRcvDealFun
@功    能: 设置串口接收处理函数
@入口参数:  
     com:  串口映射编号
     fun:  串口接收处理函数
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
void halSetComRcvDealFun(E_COM_t com, F_ComRcvFun_t fun)
{
    if(((int)com >= COMn)&&((int)com<(int)COM1_NUM))
        return;
    ComRcvFun[com] = fun;
}


/*------------------------------------------------------------
@名    称: Bsp_ComRcvDeal
@功    能: 串口中断处理函数
@入口参数:  
   com:  串口映射号
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
void halComRcvDeal(E_COM_t com)  
{
	uint8_t data;

//	LED1 = ~LED1;
	if(USART_GetITStatus(COM_USART[com], USART_IT_RXNE) != RESET)
	{
		/* Read one byte from the receive data register */
//		data = USART_ReceiveData(COM_USART[com]);	
		data = (COM_USART[com]->DR & (uint16_t)0x01FF);
		//向串口接收数据处理函数
		if(ComRcvFun[com] != NULL)
			ComRcvFun[com](com,data);
	}
	//串口数据接收完成后会进入IDLE中断
	if(USART_GetITStatus(COM_USART[com], USART_IT_IDLE) != RESET)  
	{
		DMA_Cmd(DMA_RX_CHN[com], DISABLE);//关闭DMA，防止干扰	
		USART_ReceiveData(COM_USART[com]);//Clear IDLE interrupt flag bit
		DMA_ClearFlag(DMA_RX_ITFlag[com]);	
		ComRxMsg[com].length = COM_BUF_MAX - DMA_GetCurrDataCounter(DMA_RX_CHN[com]);//接收到的字节数
		COM_RX_DONE[com] = SET;
	}
	
	OSSemPost(SemComRcvNewData[com]);
	//发送缓冲区空中断(发送完成)
//	if(USART_GetFlagStatus(COM_USART[com],USART_IT_TXE) != RESET)
//	{
//		USART_ClearFlag(COM_USART[com],USART_IT_TXE);
//		USART_ITConfig(COM_USART[com], USART_IT_TXE, DISABLE);	
//	}	
}

//串口发送完成中断处理函数
void halComSndDeal(E_COM_t com)  
{
	//串口数据发送完成会进入该中断	
	
	if(DMA_GetITStatus(DMA_TX_ITFlag[com])!= RESET)
	{
		DMA_ClearITPendingBit( DMA_TX_ITFlag[com]);
//			DMA_ClearFlag(DMA_TX_ITFlag[com]);
		DMA_Cmd(DMA_TX_CHN[com], DISABLE);
		COM_TX_DONE[com] = SET;
	}
	
}









