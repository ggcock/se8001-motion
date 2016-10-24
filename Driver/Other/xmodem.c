/*---------------------------------------------------------------*/
/*
* File name   : xmodem.c
* Author      : neal.deng
* Version     : 2.0.0
* Date        : 
* Description : xmodem协议操作函数包括标准xmodem和1K-xmodem协议
*				校验方式CRC	
* others      :
* FunctionList:
* History     :
*   1. Date:
*      Reason:
*      Author:
*      Modification: 
*/
/*---------------------------------------------------------------*/


#include <stdint.h>
#include <string.h>

#include "crc16.h"
#include "queue.h"
#include "seeing_com.h"
#include "seeing_system.h"

#include "xmodem.h"
/*--------------------------------------*/
//xmodem 协议定义
#define SOH  0x01 		//标准xmodem帧头
#define STX  0x02		//1K-xmodem帧头
#define EOT  0x04 		//结束
#define ACK  0x06 		//认可响应
#define NAK  0x15		//不认可响应
#define CAN  0x18		//撤销传送
#define CTRLZ 0x1A		//帧短填充值

/*--------------------------------------*/
#define MAX_RETRANS 	25			//重发最大次数
#define RE_TRY_COUNT	20			//等待接收的标准延时次数
#define DELAY_1_SEC		0x600000	//1秒超时计数

//是否接收有数据
static int last_error=0;


//看门狗刷新函数
#define Xmd_IwdgFeed()  Seeing_WdgFeed()

//Xmodem 字节发送函数
//ch: 要发送的字节
#define Xmd_SendByte(fd, ch) COM_PutChar((E_COM_t) fd, ch)


//xmodem 获取接收字节
//timedout：超时计数
//返回值小于0，没有接收数据	，其他为接收数据
static int Xmd_GetByte(int fd, uint32_t timedout)
{
	int ch=-1;
	last_error = 1;
	while(timedout-- > 0)
	{
		//喂狗
		Xmd_IwdgFeed();
	 	//查看接收队列里是否有数据
		if(IsQueueEmpty(COM_MSG[fd])==1)
		{
			continue;
		}
		last_error = 0;
		ch = PopQueue(COM_MSG[fd]);
		return ch;
	}

	return ch;
}

//校验算法
static int check(int flag, const unsigned char *buf, int sz)
{
	if (flag)
	{
		unsigned short crc = crc16_ccitt((char *)buf, sz);
		unsigned short tcrc = (buf[sz]<<8)+buf[sz+1];
		if (crc == tcrc)
			return 1;
	}
	else
	{
		int i;
		unsigned char cks = 0;
		for (i = 0; i < sz; ++i)
		{
			cks += buf[i];
		}
		if (cks == buf[sz])
			return 1;
	}
	return 0;
}

//清空接收缓存
void Xmd_FlushRcvBuffer(int fd)
{
	QueueInitial(COM_MSG[fd]);
}


//存储方向开关
//0=flash_if
//1=外部flash
static uint8_t _fFlashSW=0;

//转向外部flash
void Xmd_SwitchToFlash(void)
{
	_fFlashSW = 1;
}

//转向内部Flash
void Xmd_SwitchToFlashIf(void)
{
	_fFlashSW = 0;
}

/*------------------------------------------------------------
@名    称： XmodemReceive
@功    能:  xmodem 接收函数
@入口参数：
	com ： 串口号
	write: 接收数据存储函数
	arg:
	size:	存储空间大小	
@出口参数：	无	
@返 回 值： 无
------------------------------------------------------------*/
static char xm_buf[1030];	//大数组 放在函数外，防止堆栈溢出
int XmodemReceive(int fd, F_WriteFun_t write_fun, void *arg, uint32_t dst_size)
{
	int retry=0;
	int retrans = MAX_RETRANS;
	char try_char='C';			//默认校验
	int16_t ch=-1;				//接收字符
	uint16_t buf_size=0;
	int crc=0;	
	uint32_t len=0,i;			//接收字节计数
	uint8_t packetno=1; 		//数据包编码
	uint32_t count=0;
	char *p;
	uint32_t addr=0;
	
	if(1 == _fFlashSW)
	{
		addr = 0;
	}
	memset(xm_buf,0,sizeof(xm_buf));
	//清空缓存
//	xm_FlushRcvBuffer(com);

	while(1)
	{
		//启动xmodem传输
		for(retry=0; retry<RE_TRY_COUNT; retry++)
		{
			if(try_char)
			{
				//发送启动字符或结束
			 	Xmd_SendByte(fd, try_char);
			}

			//获取应答
			ch = Xmd_GetByte(fd, DELAY_1_SEC);
			if(last_error != 0)
			{
				continue;
			}

			switch(ch)
			{
				case SOH:		//128 bytes  xmodem标准传输
					buf_size = 128;
					goto xm_start_rcv;
				case STX:		//1024 bytes 1K-xmodem传输
					buf_size = 1024;
					goto xm_start_rcv;
				case EOT:		//数据传输结束
					Xmd_FlushRcvBuffer(fd);
					Xmd_SendByte(fd, ACK);
					return len;
				case CAN:
					ch = Xmd_GetByte(fd, DELAY_1_SEC);
					if(ch == CAN)
					{
					//撤销传送
						Xmd_SendByte(fd, ACK);
						return -1;
					}
					break;
				default:
					break;			
			}//end switch first
		}//end for retry start

		//换一种校验和算法
		if (try_char == 'C')
		{
			try_char = NAK;
			continue;
		}
		Xmd_FlushRcvBuffer(fd);
		Xmd_SendByte(fd,CAN);
		Xmd_SendByte(fd,CAN);
		Xmd_SendByte(fd,CAN);
		return -2;
//开始收
xm_start_rcv:
		if(try_char == 'C')
			crc = 1;

		try_char = 0;	//无需再启动
		p = xm_buf;
		*p++ = ch;		
		for (i = 0;  i < (buf_size+(crc?1:0)+3); ++i)
		{
			ch = Xmd_GetByte(fd, DELAY_1_SEC);
			if(last_error != 0)
				goto xm_reject;
			*p++ = ch;
		}

		//数据包处理
		if((xm_buf[1] == (unsigned char)(~xm_buf[2])) &&
				((xm_buf[1] == packetno || xm_buf[1] == packetno-1)) &&
				check(crc, (unsigned char*)&xm_buf[3], buf_size))
		{
			if (xm_buf[1] == packetno) 
			{
				count = dst_size - len;
				if (count > buf_size)
					count = buf_size;
				if (count > 0)
				{
					if(1 == _fFlashSW)
					{
						//外部Flash
						write_fun(&xm_buf[3], (void*)addr,count);
						addr += count;
					}
					else
					{
						write_fun(arg, &xm_buf[3], count);
					}
					len += count;
				}
				++packetno;
				retrans = MAX_RETRANS+1;
			}

			if (--retrans <= 0)
			{
				Xmd_FlushRcvBuffer(fd);
				Xmd_SendByte(fd,CAN);
				Xmd_SendByte(fd,CAN);
				Xmd_SendByte(fd,CAN);
				return -3;
			}

			Xmd_SendByte(fd,ACK);
			continue;
		}
xm_reject:
//		xm_FlushRcvBuffer(com);
		Xmd_SendByte(fd,NAK);	
	}//end rcv while
}

/*---------------------------------------------------------------*/
//end file
