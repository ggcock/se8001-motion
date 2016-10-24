

#ifndef __SEEING_DELAY_H
#define __SEEING_DELAY_H

#include "system.h"
#include "includes.h"

//��delay_us/delay_ms��Ҫ֧��OS��ʱ����Ҫ������OS��صĺ궨��ͺ�����֧��
//������3���궨��:
//  DelayOsrunning:���ڱ�ʾOS��ǰ�Ƿ���������,�Ծ����Ƿ����ʹ����غ���
//	DelayOstickspersec:���ڱ�ʾOS�趨��ʱ�ӽ���,delay_init�����������������ʼ��systick
// 	DelayOsintnesting:���ڱ�ʾOS�ж�Ƕ�׼���,��Ϊ�ж����治���Ե���,delay_msʹ�øò����������������
//Ȼ����3������:
//  DelayOsschedlock:��������OS�������,��ֹ����
//	DelayOsschedunlock:���ڽ���OS�������,���¿�������
//  DelayOstimedly:����OS��ʱ,���������������.

//�����̽���UCOSII��UCOSIII��֧��,����OS,�����вο�����ֲ
//֧��UCOSII
#ifdef 	OS_CRITICAL_METHOD						//OS_CRITICAL_METHOD������,˵��Ҫ֧��UCOSII				
#define DelayOsrunning				OSRunning			//OS�Ƿ����б��,0,������;1,������
#define DelayOstickspersec		OS_TICKS_PER_SEC	//OSʱ�ӽ���,��ÿ����ȴ���
#define DelayOsintnesting 		OSIntNesting		//�ж�Ƕ�׼���,���ж�Ƕ�״���
#endif

//֧��UCOSIII
#ifdef 	CPU_CFG_CRITICAL_METHOD						//CPU_CFG_CRITICAL_METHOD������,˵��Ҫ֧��UCOSIII	
#define DelayOsrunning				OSRunning			//OS�Ƿ����б��,0,������;1,������
#define DelayOstickspersec		OSCfg_TickRate_Hz	//OSʱ�ӽ���,��ÿ����ȴ���
#define DelayOsintnesting 		OSIntNestingCtr		//�ж�Ƕ�׼���,���ж�Ƕ�״���
#endif


#if SYSTEM_SUPPORT_UCOS>0

#define SYSTEMTICK_PERIOD_MS		(DelayOstickspersec/1000)
#define SYS_CLOCK_TICKS 						(SysTick->LOAD)
#else
//����ʱ���������
#define SYSTEMTICK_PERIOD_MS    1      //ms(С��100ms)
//ϵͳʱ�ӵδ����
#define SYS_CLOCK_TICKS         ((SystemCoreClock/1000)*SYSTEMTICK_PERIOD_MS)
#endif

typedef void(*F_WorldTimeFun_t)(uint16_t tick);


void DelayInitial(void);
void DelayUs(u32 nus);
void DelayMs(u16 nms);

void SetWorldTimeFun(F_WorldTimeFun_t fun);
uint32_t GetLocalTimeCnt(void);

#endif





























