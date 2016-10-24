#include "system.h"
#include "usart.h"	
#include "queue.h"

#include "halCom.h"				


//USART��COM������ӳ��

//��������
char *COM_STR[COMn] = {COM1_STR,COM2_STR,COM3_STR,COM4_STR};
//����ʵ������
USART_TypeDef* COM_USART[COMn] = {COM1,COM2,COM3,COM4};  
//����ʱ��
const uint32_t COM_USART_CLK[COMn] = {COM1_CLK,COM2_CLK,COM3_CLK,COM4_CLK}; 
//�����жϺ�
const uint16_t COM_IRQn[COMn] = {COM1_IRQn,COM2_IRQn,COM3_IRQn,COM4_IRQn};

//���ڲ�����
const uint32_t COM_USART_BAUD[COMn] = {COM1_BAUD,COM2_BAUD,COM3_BAUD,COM4_BAUD};

//���Ŷ˿�
GPIO_TypeDef* COM_TX_PORT[COMn] = {COM1_TX_GPIO_PORT,COM2_TX_GPIO_PORT,COM3_TX_GPIO_PORT,COM4_TX_GPIO_PORT};
GPIO_TypeDef* COM_RX_PORT[COMn] = {COM1_RX_GPIO_PORT,COM2_RX_GPIO_PORT,COM3_RX_GPIO_PORT,COM4_RX_GPIO_PORT};

//����ʱ��
const uint32_t COM_TX_PORT_CLK[COMn] = {COM1_TX_GPIO_CLK,COM2_TX_GPIO_CLK,COM3_TX_GPIO_CLK,COM4_TX_GPIO_CLK}; 
const uint32_t COM_RX_PORT_CLK[COMn] = {COM1_RX_GPIO_CLK,COM2_RX_GPIO_CLK,COM3_RX_GPIO_CLK,COM4_RX_GPIO_CLK};
//����Pin
const uint16_t COM_TX_PIN[COMn] = {COM1_TX_PIN,COM2_TX_PIN,COM3_TX_PIN,COM4_TX_PIN};
const uint16_t COM_RX_PIN[COMn] = {COM1_RX_PIN,COM2_RX_PIN,COM3_RX_PIN,COM4_RX_PIN};

//DMA
//���ڷ���DMAͨ�� 
DMA_Channel_TypeDef *DMA_TX_CHN[COMn] = {COM1_TX_DMA_CHN,COM2_TX_DMA_CHN,COM3_TX_DMA_CHN,COM4_TX_DMA_CHN};
//���ڽ���DMAͨ��
DMA_Channel_TypeDef *DMA_RX_CHN[COMn] = {COM1_RX_DMA_CHN,COM2_RX_DMA_CHN,COM3_RX_DMA_CHN,COM4_RX_DMA_CHN};
//���ڷ���DMA�ж�
uint8_t DMA_TX_IRQn[COMn] = {COM1_TX_DMA_IRQ,COM2_TX_DMA_IRQ,COM3_TX_DMA_IRQ,COM4_TX_DMA_IRQ};
//���ڷ����жϱ�־
const uint32_t DMA_TX_ITFlag[COMn] = {COM1_TX_DMA_FLAG,COM2_TX_DMA_FLAG,COM3_TX_DMA_FLAG,COM4_TX_DMA_FLAG};
//���ڽ����жϱ�־
const uint32_t DMA_RX_ITFlag[COMn] = {COM1_RX_DMA_FLAG,COM2_RX_DMA_FLAG,COM3_RX_DMA_FLAG,COM4_RX_DMA_FLAG};
//�Ƿ�ʹ��DMA
const uint8_t COM_TX_USE_DMA[COMn] = {COM1_TX_USE_DMA,COM2_TX_USE_DMA,COM3_TX_USE_DMA,COM4_TX_USE_DMA};
const uint8_t COM_RX_USE_DMA[COMn] = {COM1_RX_USE_DMA,COM2_RX_USE_DMA,COM3_RX_USE_DMA,COM4_RX_USE_DMA};
//���ڷ�����ɱ�־(DMA)
uint8_t COM_TX_DONE[COMn] = {SET,SET,SET,SET}; 
//���ڽ�����ɱ�־
uint8_t COM_RX_DONE[COMn] = {RESET,RESET,RESET,RESET};
//�����շ�������
S_ComBufInfo_t ComSndBuf[COMn];
S_ComBufInfo_t ComRcvBuf[COMn]; 

//------------------------------
S_ComBufInfo_t ComRxMsg[COMn];



//------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((SERVER_COM->SR&0X40)==0);
	SERVER_COM->DR = (u8) ch;      
	return ch;
}
#endif
 
/*------------------------------------------------------------
@��    ��: UsartInitial
@��    ��: ����1��ʼ��
@��ڲ���: ��
@���ڲ���: ��
@�� �� ֵ: ��
------------------------------------------------------------*/
int UsartInitial(E_COM_t com,uint32_t baud)
{
   //GPIO�˿�����
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
		//���ڿ����ж�,�����ڽ�����һ������֮�����������ж�
		USART_ITConfig(COM_USART[com], USART_IT_IDLE, ENABLE);
	}
	else
	{
		//�����ʹ��DMA�������ջ���ǿ��ж�
		USART_ITConfig(COM_USART[com], USART_IT_RXNE, ENABLE);
	}

	USART_Cmd(COM_USART[com], ENABLE);
	
	return 1;
}
//------------------------------------------------------

/*------------------------------------------------------------
@��    ��: Bsp_ComTxDmaConfig
@��    ��: ���ڽ���DMA����
@��ڲ���: 
     com:  ����ӳ����
@���ڲ���: ��
@�� �� ֵ: ��
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
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //DlisDataBuf�����ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݿ��8λ��1�ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;        //���δ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//�ر��ڴ浽�ڴ�DMA
	DMA_Init(DMA_TX_CHN[com], &DMA_InitStructure);
	
//--------------------------------------------------------------	

	//DMA�����ж�����
	NVIC_InitStructure.NVIC_IRQChannel = DMA_TX_IRQn[com];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);			

	//transfer complete interrupt
	DMA_ITConfig(DMA_TX_CHN[com], DMA_IT_TC, ENABLE);	
	//����DMA��ʽ����
  USART_DMACmd(COM_USART[com],USART_DMAReq_Tx,ENABLE);

	DMA_ClearITPendingBit( DMA_TX_ITFlag[com]);
//	DMA_ClearFlag( DMA_TX_ITFlag[com]);//���DMA���б�־
	DMA_Cmd(DMA_TX_CHN[com], DISABLE); 
	
}
/*------------------------------------------------------------
@��    ��: ComRxDmaConfig
@��    ��: ���ڽ���DMA����
@��ڲ���: 
     com:  ����ӳ����
@���ڲ���: ��
@�� �� ֵ: ��
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
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&COM_USART[com]->DR);//�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ComRxMsg[com].buf;  //�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;     //�����贫���ڴ�           
	DMA_InitStructure.DMA_BufferSize = COM_BUF_MAX;   //�����ܴ���ĳ���                  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݿ��1�ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //�ڴ����ݿ��1�ֽ�  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //���δ���     
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA���ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //�ر��ڴ浽�ڴ��DMAģʽ           
	DMA_Init(DMA_RX_CHN[com], &DMA_InitStructure);


	USART_DMACmd(COM_USART[com], USART_DMAReq_Rx, ENABLE);
	DMA_ClearFlag(DMA_RX_ITFlag[com]); 
	DMA_Cmd(DMA_RX_CHN[com], ENABLE);
	
}

/*------------------------------------------------------------
@��    ��: UsartSendByDma
@��    ��: ���� DMA���ͺ���
@��ڲ���: 
     com:  ����ӳ����
     buf:  ���������ݻ���
  length:  �����͵����ݳ���
@���ڲ���: ��
@�� �� ֵ: ��
------------------------------------------------------------*/
int UsartSendByDma(E_COM_t com, uint8_t *buf,uint16_t length)
{
	//�ȴ���һ�����ݷ������
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
@��    ��: ComDmaRcvSet
@��    ��: ���ڽ���DMAʹ��/��ֹ
@��ڲ���:  
     com:  ����ӳ����
NewState:  ���ڽ���״̬,ENABLE or DISABLE
@���ڲ���: ��
@�� �� ֵ: ��
------------------------------------------------------------*/
void UsartDmaRcvSet(E_COM_t com,FunctionalState NewState)
{
	DMA_Cmd(DMA_RX_CHN[com], DISABLE); //����֮ǰ��Ҫ�ȹرգ�����������Ч
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
@��    ��: UsartSendChar
@��    ��: USART �����ֽ����ݺ���
@��ڲ���:  
   USARTx:  ������
       ch:  �������ַ�
@���ڲ���: ��
@�� �� ֵ: ��
------------------------------------------------------------*/
void UsartSendChar(USART_TypeDef* USARTx,char ch)
{	
	if(NULL == USARTx)
			return;

	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET); 
	USARTx->DR = (ch & (uint16_t)0x01FF); 
	
}


/*------------------------------------------------------------
@��    ��: UsartSendString
@��    ��: USART �ַ������ͺ���,������������
@��ڲ���:  
   USARTx:  ������
     pStr:  �ַ���
@���ڲ���: ��
@�� �� ֵ: �������ݸ���
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
@��    ��: UsartSendDatas
@��    ��: USART ָ���ֽ������ͺ���
@��ڲ���:  
   USARTx:  ������
     pBuf:  ���������ݻ������׵�ַ
      num:  ���������ݸ���
@���ڲ���: ��
@�� �� ֵ: �������ݸ���
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
				//�ȴ���һ���ֽڷ������
				while (USART_GetFlagStatus(COM_USART[com], USART_FLAG_TXE) == RESET){}; 
				// write a character to the USART
				COM_USART[com]->DR = (pBuf[index++] & (uint16_t)0x01FF); 
		}  
	}
	//�ȴ����һ���ֽڷ������
//	while (USART_GetFlagStatus(COM_USART[com], USART_FLAG_TXE) == RESET){}; 
	
	return index;
}






//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

//�жϽ��պ���
//COM1���ջ���ǿ��ж�
void COM1_IRQHandler(void)
{
	
	halComRcvDeal(COM1_NUM); 	
}
//COM1 ��������ж�
void COM1_DMA_IRQHandler(void)
{
	halComSndDeal(COM1_NUM);
}

//COM2
void COM2_IRQHandler(void)
{
	halComRcvDeal(COM2_NUM); 	
}
//COM2 ��������ж�
void COM2_DMA_IRQHandler(void)
{
	halComSndDeal(COM2_NUM);
}

//COM3
void COM3_IRQHandler(void)
{
	halComRcvDeal(COM3_NUM);
}
//COM3 ��������ж�
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
//COM4 ��������ж�
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















