#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "system.h" 
#include "queue.h"


//----------------------�Զ������������------------------
//֧��4������
#define COMn							4
#define COM_BUF_MAX				128


//���ں�ӳ��
typedef enum 
{
  COM1_NUM = 0,	//��0��ʼ����(���������)
  COM2_NUM = 1,
  COM3_NUM = 2,
	COM4_NUM = 3,
} E_COM_t;


//������Ϣ���ݽṹ
typedef struct
{
	u16 length;
	u8 buf[COM_BUF_MAX];
}S_ComBufInfo_t;


//���ڳ�ʼ���ṹ
typedef struct
{
	E_COM_t	ComId;
	uint8_t	RxInt;//�Ƿ񿪽����ж�
	uint8_t TxInt;//�Ƿ񿪷����ж�
	uint8_t RxDma;//�Ƿ�ʹ�ý���DMA
	uint8_t TxDma;//�Ƿ�ʹ�÷���DMA
	uint32_t Baud;//������
} S_ComInit_t;

//--------------------------------------------------------

//----------------------GPIO����ӳ����------------------

//COM1
#define COM1_STR                    "USART1"
#define COM1	                  		USART1
#define	COM1_BAUD										115200
#define COM1_CLK                    RCC_APB2Periph_USART1

#define COM1_TX_PIN                 GPIO_Pin_9
#define COM1_TX_GPIO_PORT           GPIOA
#define COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA

#define COM1_TX_DMA_CHN             DMA1_Channel4
#define	COM1_TX_DMA_IRQ							DMA1_Channel4_IRQn
//#define COM1_TX_DMA_FLAG            DMA1_FLAG_GL4
#define COM1_TX_DMA_FLAG            DMA1_IT_TC4

#define COM1_RX_PIN                 GPIO_Pin_10
#define COM1_RX_GPIO_PORT           GPIOA
#define COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA

#define COM1_RX_DMA_CHN             DMA1_Channel5
#define COM1_RX_DMA_FLAG            DMA1_FLAG_GL5

#define COM1_IRQn                   USART1_IRQn
#define COM1_IRQHandler             USART1_IRQHandler
#define COM1_DMA_IRQHandler				 	DMA1_Channel4_IRQHandler

//COM2
#define COM2_STR                    "USART2"
#define COM2	                  		USART2
#define	COM2_BAUD										115200
#define COM2_CLK                    RCC_APB1Periph_USART2

#define COM2_TX_PIN                 GPIO_Pin_2
#define COM2_TX_GPIO_PORT           GPIOA
#define COM2_TX_GPIO_CLK            RCC_APB2Periph_GPIOA

#define COM2_TX_DMA_CHN             DMA1_Channel7
#define	COM2_TX_DMA_IRQ							DMA1_Channel7_IRQn
//#define COM2_TX_DMA_FLAG            DMA1_FLAG_GL7
#define COM2_TX_DMA_FLAG            DMA1_IT_TC7

#define COM2_RX_PIN                 GPIO_Pin_3
#define COM2_RX_GPIO_PORT           GPIOA
#define COM2_RX_GPIO_CLK            RCC_APB2Periph_GPIOA

#define COM2_RX_DMA_CHN             DMA1_Channel3
#define COM2_RX_DMA_FLAG            DMA1_FLAG_GL3

#define COM2_IRQn                   USART2_IRQn
#define COM2_IRQHandler             USART2_IRQHandler
#define COM2_DMA_IRQHandler				 	DMA1_Channel7_IRQHandler

//COM3
#define COM3_STR                    "USART3"
#define COM3	                  		USART3
#define	COM3_BAUD										115200
#define COM3_CLK                    RCC_APB1Periph_USART3

#define COM3_TX_PIN                 GPIO_Pin_10
#define COM3_TX_GPIO_PORT           GPIOB
#define COM3_TX_GPIO_CLK            RCC_APB2Periph_GPIOB

#define COM3_TX_DMA_CHN             DMA1_Channel2
#define	COM3_TX_DMA_IRQ							DMA1_Channel2_IRQn
//#define COM3_TX_DMA_FLAG            DMA1_FLAG_GL2
#define COM3_TX_DMA_FLAG            DMA1_IT_TC2

#define COM3_RX_PIN                 GPIO_Pin_11
#define COM3_RX_GPIO_PORT           GPIOB
#define COM3_RX_GPIO_CLK            RCC_APB2Periph_GPIOB

#define COM3_RX_DMA_CHN             DMA1_Channel3
#define COM3_RX_DMA_FLAG            DMA1_FLAG_GL3

#define COM3_IRQn                   USART3_IRQn
#define COM3_IRQHandler             USART3_IRQHandler
#define COM3_DMA_IRQHandler				 	DMA1_Channel2_IRQHandler


//COM4
#define COM4_STR                    "UART4"
#define COM4                   			UART4
#define	COM4_BAUD										9600
#define COM4_CLK                    RCC_APB1Periph_UART4

#define COM4_TX_PIN                 GPIO_Pin_10
#define COM4_TX_AF_PIN              GPIO_PinSource10
#define COM4_TX_GPIO_PORT           GPIOC
#define COM4_TX_GPIO_CLK            RCC_APB2Periph_GPIOC

#define COM4_TX_DMA_CHN             DMA2_Channel5
#define	COM4_TX_DMA_IRQ							DMA2_Channel4_5_IRQn
//#define COM4_TX_DMA_FLAG            DMA2_FLAG_GL5
#define COM4_TX_DMA_FLAG            DMA2_IT_TC5

#define COM4_RX_PIN                 GPIO_Pin_11
#define COM4_RX_AF_PIN              GPIO_PinSource11
#define COM4_RX_GPIO_PORT           GPIOC
#define COM4_RX_GPIO_CLK            RCC_APB2Periph_GPIOC

#define COM4_RX_DMA_CHN             DMA2_Channel3
#define COM4_RX_DMA_FLAG            DMA2_FLAG_GL3

#define COM4_IRQn                   UART4_IRQn
#define COM4_IRQHandler             UART4_IRQHandler
#define COM4_DMA_IRQHandler				 	DMA2_Stream5_IRQHandler

//--------------------------------------------------------

//--------------------------------------------------------

#define	ComSendByte(com,ch)							UsartSendChar(COM_USART[com], ch)
#define	ComSendString(com, pStr)				UsartSendString(com, pStr)
#define	ComSendDatas(com, pBuf, num)		UsartSendDatas(com, pBuf, num)


extern S_Queue_t	ComRxQ[COMn];
extern S_ComBufInfo_t ComRxMsg[COMn];

int UsartInitial(E_COM_t com,uint32_t baud);
//int ComInitial(E_COM_t com,uint32_t baud);
int ComServerPeriodicHandle(void);

void UsartTxDmaConfig(E_COM_t com);
void UsartRxDmaConfig(E_COM_t com);
int UsartSendByDma(E_COM_t com, uint8_t *buf,uint16_t length);
void UsartDmaRcvSet(E_COM_t com,FunctionalState NewState);

void UsartSendChar(USART_TypeDef* USARTx,char ch);
int UsartSendString(E_COM_t com, char *pStr);
int UsartSendDatas(E_COM_t com, uint8_t *pBuf,int num);

#endif


