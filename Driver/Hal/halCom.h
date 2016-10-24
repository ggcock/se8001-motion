

#ifndef __HALCOM_H
#define __HALCOM_H

#include "system.h"
#include "usart.h"


//是否使用DMA
//COM1
#define	COM1_TX_USE_DMA		1
#define	COM1_RX_USE_DMA		1
//COM2
#define	COM2_TX_USE_DMA		0
#define	COM2_RX_USE_DMA		0
//COM3
#define	COM3_TX_USE_DMA		0
#define	COM3_RX_USE_DMA		0
//COM4
#define	COM4_TX_USE_DMA		0
#define	COM4_RX_USE_DMA		1

//--------------------------------------------------------

//指令服务器
#define	SERVER_COM						COM1
#define	SERVER_COM_NUM				COM1_NUM

//modbus 触摸屏通信
#define	MB_UI_COM							COM2
#define	MB_UI_COM_NUM					COM2_NUM

//modbus 本地通信
#define	MB_LOCAL_COM					COM3
#define	MB_LOCAL_COM_NUM			COM3_NUM

//GPRS 通信
#define	WRL_COM								COM4
#define	WRL_COM_NUM						COM4_NUM

//串口接收处理函数类型
typedef void (*F_ComRcvFun_t )(E_COM_t com,char data);


extern OS_EVENT *SemComRcvNewData[COMn];

int halComInitial(E_COM_t com,uint32_t baud);
void halComPushQueue(E_COM_t com, char data);
void halSetComRcvDealFun(E_COM_t com, F_ComRcvFun_t fun);
void halComRcvDeal(E_COM_t com);
void halComSndDeal(E_COM_t com);

#endif















