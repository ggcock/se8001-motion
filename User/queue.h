/*---------------------------------------------------------------------*/
/*
* File name    : seeing_queue.h
* Author       : Neal.deng
* Version      : 1.0.0
* Date         : 2015-04-19
* Description  : ���в�������
* others       :
* FunctionList :
* History      : 
*  1. Date   :
*     Reason :
*     Author :
*     Modification:
*/
/*---------------------------------------------------------------------*/

#ifndef __QUEUE_H
#define __QUEUE_H

//-----------------------ͷ�ļ���-------------------------

#include <stdint.h>
//--------------------------------------------------------

//----------------------�Զ������������------------------


//��������С������Դ���������£��������ô�һЩ����ֹ���
#define QUEUE_MAX_SIZE 1024
typedef uint8_t 	Qdata_t;
typedef int	 		Qsize_t;

typedef struct
{						
    volatile Qsize_t head;	//����ͷ��
    volatile Qsize_t tail;	//����β��
    volatile Qdata_t data[QUEUE_MAX_SIZE];	//�������ݻ�����
}S_Queue_t;//��Ϣ���ն��нṹ��
//--------------------------------------------------------


//----------------------�ӿں�����------------------------

/*���г�ʼ��*/
void QueueInitial(S_Queue_t *q);
/*���г���*/
int QueueSize(S_Queue_t *q);
/*�����п�*/
int IsQueueEmpty(S_Queue_t *q);
/*��������*/
int IsQueueFull(S_Queue_t *q);
/*����*/
Qdata_t PopQueue(S_Queue_t *q);
/*���*/
int	PushQueue(S_Queue_t *q, Qdata_t data);

//--------------------------------------------------------

#endif
/*---------------------------------------------------------------------*/
//end file
