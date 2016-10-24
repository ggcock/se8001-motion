#include "system.h"
#include "usart.h"	
#include "queue.h"

#include "halCom.h"				


//USART到COM的引脚映射

//串口名称
char *COM_STR[COMn] = {COM1_STR,COM2_STR,COM3_STR,COM4_STR};
//串口实例对象
USART_TypeDef* COM_USART[COMn] = {COM1,COM2,COM3,COM4};  
//串口时钟
const uint32_t COM_USART_CLK[COMn] = {COM1_CLK,COM2_CLK,COM3_CLK,COM4_CLK}; 
//串口中断号
const uint16_t COM_IRQn[COMn] = {COM1_IRQn,COM2_IRQn,COM3_IRQn,COM4_IRQn};

//串口波特率
const uint32_t COM_USART_BAUD[COMn] = {COM1_BAUD,COM2_BAUD,COM3_BAUD,COM4_BAUD};

//引脚端口
GPIO_TypeDef* COM_TX_PORT[COMn] = {COM1_TX_GPIO_PORT,COM2_TX_GPIO_PORT,COM3_TX_GPIO_PORT,COM4_TX_GPIO_PORT};
GPIO_TypeDef* COM_RX_PORT[COMn] = {COM1_RX_GPIO_PORT,COM2_RX_GPIO_PORT,COM3_RX_GPIO_PORT,COM4_RX_GPIO_PORT};

//引脚时钟
const uint32_t COM_TX_PORT_CLK[COMn] = {COM1_TX_GPIO_CLK,COM2_TX_GPIO_CLK,COM3_TX_GPIO_CLK,COM4_TX_GPIO_CLK}; 
const uint32_t COM_RX_PORT_CLK[COMn] = {COM1_RX_GPIO_CLK,COM2_RX_GPIO_CLK,COM3_RX_GPIO_CLK,COM4_RX_GPIO_CLK};
//引脚Pin
const uint16_t COM_TX_PIN[COMn] = {COM1_TX_PIN,COM2_TX_PIN,COM3_TX_PIN,COM4_TX_PIN};
const uint16_t COM_RX_PIN[COMn] = {COM1_RX_PIN,COM2_RX_PIN,COM3_RX_PIN,COM4_RX_PIN};

//DMA
//串口发送DMA通道 
DMA_Channel_TypeDef *DMA_TX_CHN[COMn] = {COM1_TX_DMA_CHN,COM2_TX_DMA_CHN,COM3_TX_DMA_CHN,COM4_TX_DMA_CHN};
//串口接收DMA通道
DMA_Channel_TypeDef *DMA_RX_CHN[COMn] = {COM1_RX_DMA_CHN,COM2_RX_DMA_CHN,COM3_RX_DMA_CHN,COM4_RX_DMA_CHN};
//串口发送DMA中断
uint8_t DMA_TX_IRQn[COMn] = {COM1_TX_DMA_IRQ,COM2_TX_DMA_IRQ,COM3_TX_DMA_IRQ,COM4_TX_DMA_IRQ};
//串口发送中断标志
const uint32_t DMA_TX_ITFlag[COMn] = {COM1_TX_DMA_FLAG,COM2_TX_DMA_FLAG,COM3_TX_DMA_FLAG,COM4_TX_DMA_FLAG};
//串口接收中断标志
const uint32_t DMA_RX_ITFlag[COMn] = {COM1_RX_DMA_FLAG,COM2_RX_DMA_FLAG,COM3_RX_DMA_FLAG,COM4_RX_DMA_FLAG};
//是否使用DMA
const uint8_t COM_TX_USE_DMA[COMn] = {COM1_TX_USE_DMA,COM2_TX_USE_DMA,COM3_TX_USE_DMA,COM4_TX_USE_DMA};
const uint8_t COM_RX_USE_DMA[COMn] = {COM1_RX_USE_DMA,COM2_RX_USE_DMA,COM3_RX_USE_DMA,COM4_RX_USE_DMA};
//串口发送完成标志(DMA)
uint8_t COM_TX_DONE[COMn] = {SET,SET,SET,SET}; 
//串口接收完成标志
uint8_t COM_RX_DONE[COMn] = {RESET,RESET,RESET,RESET};
//串口收发缓冲区
S_ComBufInfo_t ComSndBuf[COMn];
S_ComBufInfo_t ComRcvBuf[COMn]; 

//------------------------------
S_ComBufInfo_t ComRxMsg[COMn];



//------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((SERVER_COM->SR&0X40)==0);
	SERVER_COM->DR = (u8) ch;      
	return ch;
}
#endif
 
/*------------------------------------------------------------
@名    称: UsartInitial
@功    能: 串口1初始化
@入口参数: 无
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
int UsartInitial(E_COM_t com,uint32_t baud)
{
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Enable GPIO clock
	RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[com] | COM_RX_PORT_CLK[com]|RCC_APB2Periph_AFIO, ENABLE);
	if (com == COM1_NUM)
	{
		RCC_APB2PeriphClockCmd(COM_USART_CLK[com], ENABLE);
	}
	else if (com == COM2_NUM)
	{
		// Enable the USART2 Pins Software Remapping
		RCC_APB1PeriphClockCmd(COM_USART_CLK[com], ENABLE);
	}
	else if (com == COM3_NUM)
	{
		// Enable the USART2 Pins Software Remapping
		RCC_APB1PeriphClockCmd(COM_USART_CLK[com], ENABLE);

	}
	else if (com == COM4_NUM)
	{
			// Enable the UART4 Pins Software Remapping
		RCC_APB1PeriphClockCmd(COM_USART_CLK[com], ENABLE);
	}		
	else
	{
			return -1;
	}
	
	/* Configure USART Tx and Rx as alternate function push-pull */	
	GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[com];
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(COM_TX_PORT[com], &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[com];
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(COM_RX_PORT[com], &GPIO_InitStructure); 
	
	//---------------------------------------------------------    
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(COM_USART[com], &USART_InitStructure);		
	
//---------------------------------------------------------
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = COM_IRQn[com];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);			
	
	//if use DMA to send data
	if(COM_TX_USE_DMA[com])
	{
		UsartTxDmaConfig(com);
	}
	
	if(COM_RX_USE_DMA[com])
	{
		UsartRxDmaConfig(com);
		//串口空闲中断,当串口接收完一次数据之后会产生空闲中断
		USART_ITConfig(COM_USART[com], USART_IT_IDLE, ENABLE);
	}
	else
	{
		//如果不使用DMA则开启接收缓冲非空中断
		USART_ITConfig(COM_USART[com], USART_IT_RXNE, ENABLE);
	}

	USART_Cmd(COM_USART[com], ENABLE);
	
	return 1;
}
//------------------------------------------------------

/*------------------------------------------------------------
@名    称: Bsp_ComTxDmaConfig
@功    能: 串口接收DMA配置
@入口参数: 
     com:  串口映射编号
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
void UsartTxDmaConfig(E_COM_t com)
{
	DMA_InitTypeDef  DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	if(com == COM4_NUM)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	}
	else
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	}


	DMA_Cmd(DMA_TX_CHN[com], DISABLE);//TX 
	DMA_DeInit(DMA_TX_CHN[com]);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&COM_USART[com]->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ComSndBuf[com].buf;; 
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//memory to peripheral
	DMA_InitStructure.DMA_BufferSize = (u16)COM_BUF_MAX;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //DlisDataBuf数组地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据宽度8位即1字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;        //单次传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//关闭内存到内存DMA
	DMA_Init(DMA_TX_CHN[com], &DMA_InitStructure);
	
//--------------------------------------------------------------	

	//DMA发送中断配置
	NVIC_InitStructure.NVIC_IRQChannel = DMA_TX_IRQn[com];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);			

	//transfer complete interrupt
	DMA_ITConfig(DMA_TX_CHN[com], DMA_IT_TC, ENABLE);	
	//采用DMA方式发送
  USART_DMACmd(COM_USART[com],USART_DMAReq_Tx,ENABLE);

	DMA_ClearITPendingBit( DMA_TX_ITFlag[com]);
//	DMA_ClearFlag( DMA_TX_ITFlag[com]);//清除DMA所有标志
	DMA_Cmd(DMA_TX_CHN[com], DISABLE); 
	
}
/*------------------------------------------------------------
@名    称: ComRxDmaConfig
@功    能: 串口接收DMA配置
@入口参数: 
     com:  串口映射编号
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
void UsartRxDmaConfig(E_COM_t com)
{
	DMA_InitTypeDef  DMA_InitStructure;
	
	if(com == COM4_NUM)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	}
	else
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	}

	DMA_Cmd(DMA_RX_CHN[com], DISABLE);                       
	DMA_DeInit(DMA_RX_CHN[com]);                               
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&COM_USART[com]->DR);//外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ComRxMsg[com].buf;  //内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;     //从外设传到内存           
	DMA_InitStructure.DMA_BufferSize = COM_BUF_MAX;   //最大可能传输的长度                  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址不调整
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址调整
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据宽度1字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //内存数据宽度1字节  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //单次传输     
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //关闭内存到内存的DMA模式           
	DMA_Init(DMA_RX_CHN[com], &DMA_InitStructure);


	USART_DMACmd(COM_USART[com], USART_DMAReq_Rx, ENABLE);
	DMA_ClearFlag(DMA_RX_ITFlag[com]); 
	DMA_Cmd(DMA_RX_CHN[com], ENABLE);
	
}

/*------------------------------------------------------------
@名    称: UsartSendByDma
@功    能: 串口 DMA发送函数
@入口参数: 
     com:  串口映射编号
     buf:  待发送数据缓冲
  length:  待发送的数据长度
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
int UsartSendByDma(E_COM_t com, uint8_t *buf,uint16_t length)
{
	//等待上一次数据发送完成
	if(COM_TX_DONE[com] != SET)
	{
		return -1;
	}	

	COM_TX_DONE[com] = RESET;

	DMA_TX_CHN[com]->CCR &= (uint16_t)(~DMA_CCR1_EN);//disable
	DMA_TX_CHN[com]->CMAR=(u32)ComSndBuf[com].buf;
	DMA_TX_CHN[com]->CPAR=(u32)(&COM_USART[com]->DR);	
	DMA_TX_CHN[com]->CNDTR = length;
	DMA_TX_CHN[com]->CCR |= DMA_CCR1_EN;//enable
	
	return 1;
}
/*------------------------------------------------------------
@名    称: ComDmaRcvSet
@功    能: 串口接收DMA使能/禁止
@入口参数:  
     com:  串口映射编号
NewState:  串口接收状态,ENABLE or DISABLE
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
void UsartDmaRcvSet(E_COM_t com,FunctionalState NewState)
{
	DMA_Cmd(DMA_RX_CHN[com], DISABLE); //设置之前需要先关闭，否则设置无效
	DMA_ClearFlag(DMA_RX_ITFlag[com]);	
	if(NewState == ENABLE)
	{
		DMA_RX_CHN[com]->CMAR=(u32)(u32)ComRxMsg[com].buf;
		DMA_RX_CHN[com]->CPAR=(u32)(&COM_USART[com]->DR);	
		DMA_RX_CHN[com]->CNDTR = (u16)COM_BUF_MAX;	
		DMA_Cmd(DMA_RX_CHN[com], ENABLE); 
	}	

}



/*------------------------------------------------------------
@名    称: UsartSendChar
@功    能: USART 发送字节数据函数
@入口参数:  
   USARTx:  串口名
       ch:  待发送字符
@出口参数: 无
@返 回 值: 无
------------------------------------------------------------*/
void UsartSendChar(USART_TypeDef* USARTx,char ch)
{	
	if(NULL == USARTx)
			return;

	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET); 
	USARTx->DR = (ch & (uint16_t)0x01FF); 
	
}


/*------------------------------------------------------------
@名    称: UsartSendString
@功    能: USART 字符串发送函数,结束符不发送
@入口参数:  
   USARTx:  串口名
     pStr:  字符串
@出口参数: 无
@返 回 值: 发送数据个数
------------------------------------------------------------*/
int UsartSendString(E_COM_t com, char *pStr)
{
	int index=0;

	if(NULL == COM_USART[com])
			return -1;

	if(COM_TX_USE_DMA[com])
	{
		index = strlen((const char *)pStr);
		UsartSendByDma(com,(uint8_t *)pStr,index);
	}
	else
	{
		while(pStr[index] != '\0')
		{
				while(USART_GetFlagStatus(COM_USART[com],USART_FLAG_TC)==RESET); 	
//				while (USART_GetFlagStatus(COM_USART[com], USART_FLAG_TXE) == RESET){}; 
				// write a character to the USART
				COM_USART[com]->DR = (pStr[index++] & (uint16_t)0x01FF); 
		}  
	}

	
	return index;
}


/*------------------------------------------------------------
@名    称: UsartSendDatas
@功    能: USART 指定字节数发送函数
@入口参数:  
   USARTx:  串口名
     pBuf:  待发送数据缓冲区首地址
      num:  待发送数据个数
@出口参数: 无
@返 回 值: 发送数据个数
------------------------------------------------------------*/
int UsartSendDatas(E_COM_t com, uint8_t *pBuf,int num)
{
	int index=0;
	if(NULL == COM_USART[com])
			return -1;
	
	if(COM_TX_USE_DMA[com])
	{
		UsartSendByDma(com,pBuf,num);
	}	
	else
	{
		while(index < num)
		{
				//等待上一个字节发送完成
				while (USART_GetFlagStatus(COM_USART[com], USART_FLAG_TXE) == RESET){}; 
				// write a character to the USART
				COM_USART[com]->DR = (pBuf[index++] & (uint16_t)0x01FF); 
		}  
	}
	//等待最后一个字节发送完成
//	while (USART_GetFlagStatus(COM_USART[com], USART_FLAG_TXE) == RESET){}; 
	
	return index;
}






//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

//中断接收函数
//COM1接收缓冲非空中断
void COM1_IRQHandler(void)
{
	
	halComRcvDeal(COM1_NUM); 	
}
//COM1 发送完成中断
void COM1_DMA_IRQHandler(void)
{
	halComSndDeal(COM1_NUM);
}

//COM2
void COM2_IRQHandler(void)
{
	halComRcvDeal(COM2_NUM); 	
}
//COM2 发送完成中断
void COM2_DMA_IRQHandler(void)
{
	halComSndDeal(COM2_NUM);
}

//COM3
void COM3_IRQHandler(void)
{
	halComRcvDeal(COM3_NUM);
}
//COM3 发送完成中断
void COM3_DMA_IRQHandler(void)
{
	halComSndDeal(COM3_NUM);
}

//COM4
void COM4_IRQHandler(void)
{
	halComRcvDeal(COM4_NUM); 	
/*	
//	LED1 = ~LED1;
	if(DMA_GetITStatus(COM4_RX_DMA_STRM, COM4_RX_DMA_FLAG) == SET ) 
	{
		//DMA_ClearFlag(DMA1_Stream2, DMA_FLAG_TCIF2);
		DMA_ClearITPendingBit(COM4_RX_DMA_STRM, COM4_RX_DMA_FLAG);
		DMA_Cmd(COM4_RX_DMA_STRM, ENABLE);
//		ComRxMsg[3].length = COM_BUF_MAX - DMA_RX_STRM[3]->NDTR;
//		COM_RX_DONE[3] = SET;	
//		ComDmaRcvSet(3,ENABLE);
	}
*/
	
}
//COM4 发送完成中断
void COM4_DMA_IRQHandler(void)
{
	halComSndDeal(COM4_NUM);

/*	
	if(DMA_GetITStatus(COM4_TX_DMA_STRM, COM4_TX_DMA_FLAG) == SET ) 
 {
   //DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
   DMA_Cmd(COM4_TX_DMA_STRM, DISABLE);
   DMA_ClearITPendingBit(COM4_TX_DMA_STRM, COM4_TX_DMA_FLAG);  
   DMA_Cmd(COM4_TX_DMA_STRM, ENABLE);
 }
*/
	
}

//-----------------------------------------------

/*---------------------------------------------------------------------*/
//end file















