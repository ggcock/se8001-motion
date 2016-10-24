

//����Ӳ�������
#include "halCom.h"
#include "queue.h"


//����ʵ������
extern USART_TypeDef* COM_USART[COMn];
//���ڲ�����
extern const uint32_t COM_USART_BAUD[COMn];
//���ڷ����жϱ�־
extern const uint32_t DMA_TX_ITFlag[COMn];

//���ڷ���DMAͨ�� 
extern DMA_Channel_TypeDef *DMA_TX_CHN[COMn];
//���ڽ���DMAͨ��
extern DMA_Channel_TypeDef *DMA_RX_CHN[COMn];
//���ڷ����жϱ�־
extern const uint32_t DMA_TX_ITFlag[COMn];
//���ڽ����жϱ�־
extern const uint32_t DMA_RX_ITFlag[COMn];
	
//���ڷ�����ɱ�־(DMA)
extern uint8_t COM_TX_DONE[COMn]; 
//���ڽ�����ɱ�־
extern uint8_t COM_RX_DONE[COMn];
	
S_Queue_t	ComRxQ[COMn];
//Ӧ�ò���մ�����
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
@��    ��: COM_PushQueue
@��    ��: COM�������ݴ�������
           ѹ�������:�򴮿ڽ��ն�����������
@��ڲ���:
      com: ����ӳ���
     pBuf: ���������ݻ������׵�ַ
      fmt: ��ʽ���ַ���
@���ڲ���: ��
@�� �� ֵ: ���������ֽڳ���
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
        //��ȡ��Ϣָ�������ָ�����
    }

}

/*------------------------------------------------------------
@��    ��: SetComRcvDealFun
@��    ��: ���ô��ڽ��մ�����
@��ڲ���:  
     com:  ����ӳ����
     fun:  ���ڽ��մ�����
@���ڲ���: ��
@�� �� ֵ: ��
------------------------------------------------------------*/
void halSetComRcvDealFun(E_COM_t com, F_ComRcvFun_t fun)
{
    if(((int)com >= COMn)&&((int)com<(int)COM1_NUM))
        return;
    ComRcvFun[com] = fun;
}


/*------------------------------------------------------------
@��    ��: Bsp_ComRcvDeal
@��    ��: �����жϴ�����
@��ڲ���:  
   com:  ����ӳ���
@���ڲ���: ��
@�� �� ֵ: ��
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
		//�򴮿ڽ������ݴ�����
		if(ComRcvFun[com] != NULL)
			ComRcvFun[com](com,data);
	}
	//�������ݽ�����ɺ�����IDLE�ж�
	if(USART_GetITStatus(COM_USART[com], USART_IT_IDLE) != RESET)  
	{
		DMA_Cmd(DMA_RX_CHN[com], DISABLE);//�ر�DMA����ֹ����	
		USART_ReceiveData(COM_USART[com]);//Clear IDLE interrupt flag bit
		DMA_ClearFlag(DMA_RX_ITFlag[com]);	
		ComRxMsg[com].length = COM_BUF_MAX - DMA_GetCurrDataCounter(DMA_RX_CHN[com]);//���յ����ֽ���
		COM_RX_DONE[com] = SET;
	}
	
	OSSemPost(SemComRcvNewData[com]);
	//���ͻ��������ж�(�������)
//	if(USART_GetFlagStatus(COM_USART[com],USART_IT_TXE) != RESET)
//	{
//		USART_ClearFlag(COM_USART[com],USART_IT_TXE);
//		USART_ITConfig(COM_USART[com], USART_IT_TXE, DISABLE);	
//	}	
}

//���ڷ�������жϴ�����
void halComSndDeal(E_COM_t com)  
{
	//�������ݷ�����ɻ������ж�	
	
	if(DMA_GetITStatus(DMA_TX_ITFlag[com])!= RESET)
	{
		DMA_ClearITPendingBit( DMA_TX_ITFlag[com]);
//			DMA_ClearFlag(DMA_TX_ITFlag[com]);
		DMA_Cmd(DMA_TX_CHN[com], DISABLE);
		COM_TX_DONE[com] = SET;
	}
	
}









