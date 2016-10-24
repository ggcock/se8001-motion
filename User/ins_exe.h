

#ifndef __INS_EXE_H
#define __INS_EXE_H


#include "system.h"

//WE CAN 
#define	INS_COUNT_MAX					20
#define	PARA_ERR							(-40)
#define	DONE_ERR							(-80)
//--------------------------------------------
//command list

#define	CMD_HELP							"help"
#define	CMD_RLY_SET						"relay set"
#define	CMD_RLY_GET						"relay get"
#define	CMD_VOLT_GET					"volt get"
#define	CMD_TIME_SET					"time set"
#define	CMD_TIME_GET					"time get"
#define	CMD_DATE_SET					"date set"
#define	CMD_DATE_GET					"date get"
#define	CMD_COM_CFG						"com cfg"
#define	CMD_VOLT_CTL					"volt ctl"
#define	CMD_VREF_SET					"vref set"
#define	CMD_VREF_GET					"vref get"

#define	PARA_SWCH_ON					"on"
#define	PARA_SWCH_OFF					"off"

#define	PARA_RTC_AM						"am"
#define	PARA_RTC_PM						"pm"






int InsHandle(u8 *pbuf,u16 length);
int InsHelp(u8 **pplist,u8 pcnt);
int InsRelaySet(u8 **pplist,u8 pcnt);
int InsRelayGet(u8 **pplist,u8 pcnt);
int InsBatVoltGet_Single(u8 **pplist,u8 pcnt);
int InsPwmSetFreq(u8 **pplist,u8 pcnt);
int InsPwmSetDuty(u8 **pplist,u8 pcnt);
int InsPwmOut(u8 **pplist,u8 pcnt);
int InsClrSul(u8 **pplist,u8 pcnt);
int InsRtcTimeSet(u8 **pplist,u8 pcnt);
int InsRtcTimeGet(u8 **pplist,u8 pcnt);
int InsRtcDateSet(u8 **pplist,u8 pcnt);
int InsRtcDateGet(u8 **pplist,u8 pcnt);
int InsRtcGet(u8 **pplist,u8 pcnt);
int InsComCfg(u8 **pplist,u8 pcnt);
int InsVoltCtrl(u8 **pplist,u8 pcnt);
int InsSetVref(u8 **pplist,u8 pcnt);
int InsGetVref(u8 **pplist,u8 pcnt);
#endif
















