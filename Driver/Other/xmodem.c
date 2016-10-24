/*---------------------------------------------------------------*/
/*
* File name   : xmodem.c
* Author      : neal.deng
* Version     : 2.0.0
* Date        : 
* Description : xmodemЭ���������������׼xmodem��1K-xmodemЭ��
*				У�鷽ʽCRC	
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
//xmodem Э�鶨��
#define SOH  0x01 		//��׼xmodem֡ͷ
#define STX  0x02		//1K-xmodem֡ͷ
#define EOT  0x04 		//����
#define ACK  0x06 		//�Ͽ���Ӧ
#define NAK  0x15		//���Ͽ���Ӧ
#define CAN  0x18		//��������
#define CTRLZ 0x1A		//֡�����ֵ

/*--------------------------------------*/
#define MAX_RETRANS 	25			//�ط�������
#define RE_TRY_COUNT	20			//�ȴ����յı�׼��ʱ����
#define DELAY_1_SEC		0x600000	//1�볬ʱ����

//�Ƿ����������
static int last_error=0;


//���Ź�ˢ�º���
#define Xmd_IwdgFeed()  Seeing_WdgFeed()

//Xmodem �ֽڷ��ͺ���
//ch: Ҫ���͵��ֽ�
#define Xmd_SendByte(fd, ch) COM_PutChar((E_COM_t) fd, ch)


//xmodem ��ȡ�����ֽ�
//timedout����ʱ����
//����ֵС��0��û�н�������	������Ϊ��������
static int Xmd_GetByte(int fd, uint32_t timedout)
{
	int ch=-1;
	last_error = 1;
	while(timedout-- > 0)
	{
		//ι��
		Xmd_IwdgFeed();
	 	//�鿴���ն������Ƿ�������
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

//У���㷨
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

//��ս��ջ���
void Xmd_FlushRcvBuffer(int fd)
{
	QueueInitial(COM_MSG[fd]);
}


//�洢���򿪹�
//0=flash_if
//1=�ⲿflash
static uint8_t _fFlashSW=0;

//ת���ⲿflash
void Xmd_SwitchToFlash(void)
{
	_fFlashSW = 1;
}

//ת���ڲ�Flash
void Xmd_SwitchToFlashIf(void)
{
	_fFlashSW = 0;
}

/*------------------------------------------------------------
@��    �ƣ� XmodemReceive
@��    ��:  xmodem ���պ���
@��ڲ�����
	com �� ���ں�
	write: �������ݴ洢����
	arg:
	size:	�洢�ռ��С	
@���ڲ�����	��	
@�� �� ֵ�� ��
------------------------------------------------------------*/
static char xm_buf[1030];	//������ ���ں����⣬��ֹ��ջ���
int XmodemReceive(int fd, F_WriteFun_t write_fun, void *arg, uint32_t dst_size)
{
	int retry=0;
	int retrans = MAX_RETRANS;
	char try_char='C';			//Ĭ��У��
	int16_t ch=-1;				//�����ַ�
	uint16_t buf_size=0;
	int crc=0;	
	uint32_t len=0,i;			//�����ֽڼ���
	uint8_t packetno=1; 		//���ݰ�����
	uint32_t count=0;
	char *p;
	uint32_t addr=0;
	
	if(1 == _fFlashSW)
	{
		addr = 0;
	}
	memset(xm_buf,0,sizeof(xm_buf));
	//��ջ���
//	xm_FlushRcvBuffer(com);

	while(1)
	{
		//����xmodem����
		for(retry=0; retry<RE_TRY_COUNT; retry++)
		{
			if(try_char)
			{
				//���������ַ������
			 	Xmd_SendByte(fd, try_char);
			}

			//��ȡӦ��
			ch = Xmd_GetByte(fd, DELAY_1_SEC);
			if(last_error != 0)
			{
				continue;
			}

			switch(ch)
			{
				case SOH:		//128 bytes  xmodem��׼����
					buf_size = 128;
					goto xm_start_rcv;
				case STX:		//1024 bytes 1K-xmodem����
					buf_size = 1024;
					goto xm_start_rcv;
				case EOT:		//���ݴ������
					Xmd_FlushRcvBuffer(fd);
					Xmd_SendByte(fd, ACK);
					return len;
				case CAN:
					ch = Xmd_GetByte(fd, DELAY_1_SEC);
					if(ch == CAN)
					{
					//��������
						Xmd_SendByte(fd, ACK);
						return -1;
					}
					break;
				default:
					break;			
			}//end switch first
		}//end for retry start

		//��һ��У����㷨
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
//��ʼ��
xm_start_rcv:
		if(try_char == 'C')
			crc = 1;

		try_char = 0;	//����������
		p = xm_buf;
		*p++ = ch;		
		for (i = 0;  i < (buf_size+(crc?1:0)+3); ++i)
		{
			ch = Xmd_GetByte(fd, DELAY_1_SEC);
			if(last_error != 0)
				goto xm_reject;
			*p++ = ch;
		}

		//���ݰ�����
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
						//�ⲿFlash
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
