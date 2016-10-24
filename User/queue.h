/*---------------------------------------------------------------------*/
/*
* File name    : seeing_queue.h
* Author       : Neal.deng
* Version      : 1.0.0
* Date         : 2015-04-19
* Description  : 队列操作函数
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

//-----------------------头文件区-------------------------

#include <stdint.h>
//--------------------------------------------------------

//----------------------自定义变量类型区------------------


//缓冲区大小，在资源容许的情况下，尽量设置大一些，防止溢出
#define QUEUE_MAX_SIZE 1024
typedef uint8_t 	Qdata_t;
typedef int	 		Qsize_t;

typedef struct
{						
    volatile Qsize_t head;	//队列头部
    volatile Qsize_t tail;	//队列尾部
    volatile Qdata_t data[QUEUE_MAX_SIZE];	//队列数据缓冲区
}S_Queue_t;//消息接收队列结构体
//--------------------------------------------------------


//----------------------接口函数区------------------------

/*队列初始化*/
void QueueInitial(S_Queue_t *q);
/*队列长度*/
int QueueSize(S_Queue_t *q);
/*队列判空*/
int IsQueueEmpty(S_Queue_t *q);
/*队列判满*/
int IsQueueFull(S_Queue_t *q);
/*出队*/
Qdata_t PopQueue(S_Queue_t *q);
/*入队*/
int	PushQueue(S_Queue_t *q, Qdata_t data);

//--------------------------------------------------------

#endif
/*---------------------------------------------------------------------*/
//end file
