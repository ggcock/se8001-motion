#ifndef __APP_H
#define __APP_H	 
#include "system.h"
#include "includes.h"
	
	
//---------------------------------------------------------------------
/////////////////UCOSII任务堆栈设置////////////////////
////START 任务
//#define START_TASK_PRIO      		10 //开始任务的优先级设置为最低
//#define START_STK_SIZE  				64	
//extern OS_STK START_TASK_STK[START_STK_SIZE];
//void StartTask(void *pdata);	

//#define IMG_TASK_PRIO       			7 
//#define IMG_STK_SIZE  		    		256
//extern OS_STK IMG_TASK_STK[IMG_STK_SIZE];
//void ImageTask(void *pdata);

//#define SPD_TASK_PRIO       		4 
//#define SPD_STK_SIZE  					64
//extern OS_STK SPD_TASK_STK[SPD_STK_SIZE];
//void SpeedTask(void *pdata);

//#define COM_TASK_PRIO       		3 
//#define COM_STK_SIZE  					256
//extern OS_STK COM_TASK_STK[COM_STK_SIZE];
//void ComTask(void *pdata);
//-----------------------------------------------------------
//command list			
#define	CMD_SET_CAL		"set cal"
#define	SET_CAL_INFO	"-set cal(level,gain,offset)\r\nlevel:1-4;1:0-1000mm,\
2:1000-2000mm,3:2000-3000mm,4:>3000mm\r\n"
#define	CMD_GET_CAL		"get cal"
#define	GET_CAL_INFO	"-get cal(level)\r\nlevel:1-4\r\n"
#define	CMD_SET_DST		"set dst"
#define	SET_DST_INFO	"-set dst(x)\r\nx:distance in milimeter(0-65535)\r\n"
#define	CMD_GET_DST		"get dst"
#define	GET_DST_INFO	"-get dst()\r\nget the current distance in milimeter.\r\n"
#define	CMD_GET_FSS0	"get fss0"
#define	GET_FSS0_INFO	"-get fss0()\r\nset struct parameter fs and s0.\r\n"
#define	CMD_SET_FSS0	"set fss0"
#define	SET_FSS0_INFO	"-set fss0()\r\nset struct parameter fs and s0.\r\n"
//---------------------------------------------------
#define SE_MODEL				1	//SE8001-MCU-2K
#define	FIRM_VER_MN			0x00
#define	FIRM_VER_MJ			0x01
#define	HARD_VER				0x01
#define	SERIAL_NUM			"0123456789ABCDE"

//-------------------------------------------------------
#define	MAX_ANGLE_CNT		800
//ccd 阀值
#define	CCD_TH_VAL			0x25
#define	CCD_DEFAULT_VAL	0x40
#define	PHASE_OFFSET		(6)
#define	SET_START_TIMER(NewState)		do{TIM1->CNT = 0;TIM_Cmd(TIM1, (NewState));}while(0)//TIM1 用于控制START脉冲的
//#define	SET_PHS_TIMER(NewState)			TIM_Cmd(TIM4, (NewState));//TIM4用于计算相位和速度的



typedef struct{
	u8	usecal;
	u16 angle;
	u16 distance;
	u16 rpm;
	u32	period;
}_S_DistantInfo_t;

typedef struct{
	u8 start;
	u16	Ph;
	u32 Tmax;
	u32 Tacc;
	u32 Ts;
	u32	Tn;
}_S_PhsInfo_t;

typedef enum{
	CAL = 0,//校准
	DEBG,//调试模式
	IDLE,
	NORMAL,
	FORCE,
	FAST,
	RAW
}_E_SystemState_t; 

extern OS_EVENT *mbDlis;
extern OS_EVENT *mbSpeed;
extern OS_EVENT *mbCalibrate,*mbGetDist;
extern OS_EVENT *ComMsgQ;
extern void *MsgGrp[2];
extern _S_DistantInfo_t msr;
extern _S_PhsInfo_t phs;
extern _E_SystemState_t SystemState;
extern u16 MaxStartCnt;
extern u32 DispBuf;
extern u16 CcdValue0;
//----------------------------------------------
s8 SysInit(void);
//s8 ReadPara(_S_ParaInfo_t *para,u16 len);
//void SavePara(_S_ParaInfo_t *para,u16 len);
//void Calibration(void);
#endif

