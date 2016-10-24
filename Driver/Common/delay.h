

#ifndef __SEEING_DELAY_H
#define __SEEING_DELAY_H

#include "system.h"
#include "includes.h"

//当delay_us/delay_ms需要支持OS的时候需要三个与OS相关的宏定义和函数来支持
//首先是3个宏定义:
//  DelayOsrunning:用于表示OS当前是否正在运行,以决定是否可以使用相关函数
//	DelayOstickspersec:用于表示OS设定的时钟节拍,delay_init将根据这个参数来初始哈systick
// 	DelayOsintnesting:用于表示OS中断嵌套级别,因为中断里面不可以调度,delay_ms使用该参数来决定如何运行
//然后是3个函数:
//  DelayOsschedlock:用于锁定OS任务调度,禁止调度
//	DelayOsschedunlock:用于解锁OS任务调度,重新开启调度
//  DelayOstimedly:用于OS延时,可以引起任务调度.

//本例程仅作UCOSII和UCOSIII的支持,其他OS,请自行参考着移植
//支持UCOSII
#ifdef 	OS_CRITICAL_METHOD						//OS_CRITICAL_METHOD定义了,说明要支持UCOSII				
#define DelayOsrunning				OSRunning			//OS是否运行标记,0,不运行;1,在运行
#define DelayOstickspersec		OS_TICKS_PER_SEC	//OS时钟节拍,即每秒调度次数
#define DelayOsintnesting 		OSIntNesting		//中断嵌套级别,即中断嵌套次数
#endif

//支持UCOSIII
#ifdef 	CPU_CFG_CRITICAL_METHOD						//CPU_CFG_CRITICAL_METHOD定义了,说明要支持UCOSIII	
#define DelayOsrunning				OSRunning			//OS是否运行标记,0,不运行;1,在运行
#define DelayOstickspersec		OSCfg_TickRate_Hz	//OS时钟节拍,即每秒调度次数
#define DelayOsintnesting 		OSIntNestingCtr		//中断嵌套级别,即中断嵌套次数
#endif


#if SYSTEM_SUPPORT_UCOS>0

#define SYSTEMTICK_PERIOD_MS		(DelayOstickspersec/1000)
#define SYS_CLOCK_TICKS 						(SysTick->LOAD)
#else
//本地时间计数基数
#define SYSTEMTICK_PERIOD_MS    1      //ms(小于100ms)
//系统时钟滴答计数
#define SYS_CLOCK_TICKS         ((SystemCoreClock/1000)*SYSTEMTICK_PERIOD_MS)
#endif

typedef void(*F_WorldTimeFun_t)(uint16_t tick);


void DelayInitial(void);
void DelayUs(u32 nus);
void DelayMs(u16 nms);

void SetWorldTimeFun(F_WorldTimeFun_t fun);
uint32_t GetLocalTimeCnt(void);

#endif





























