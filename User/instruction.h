#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include "system.h"

#ifndef RPLIDAR	
#define	STOP				0x81//turn to idle
#define	RESET				0x82//restart 
#define	TEST				0x83//just for test
#define	SCAN				0x41//scan
#define	FORCE_SCAN	0x42
#define	FAST_SCAN		0x43
#define	RAW_SCAN		0x4F//return raw data
#define	CALIBRATE		0x31//进入校准过程
#define	SET_CAL			0x32//设置是否使用校准系数
#define	GET_INFO		0x21
#define	GET_HEALTH	0x22
#else
#define	STOP				0x25//turn to idle
#define	RESET				0x40//restart 
#define	TEST				0xFF//just for test
#define	SCAN				0x20//scan
#define	FORCE_SCAN	0x21
#define	FAST_SCAN		0xFE
#define	RAW_SCAN		0xFD//return raw data
#define	CALIBRATE		0x31//进入校准过程
#define	SET_CAL			0xFC//设置是否使用校准系数
#define	GET_INFO		0x50
#define	GET_HEALTH	0x51
#endif

typedef struct{
	char prio;//命令 优先级
	char *id;//命令 id，即命令字符串 
	s8 (*pHandler)(u8 *pcmd,u8 pcnt,u8 **plist,void *pdata);	//命令处理函数 
}_S_CommandHandle_t;


u8 WaitInstruction(void *commsg,u32 timeout);
s32 InstructionPasre(u8 *src,u8 **pParaList,u8 *paracnt,u8 **cmd);
s8 ProtocolParse(const char *src,u8 *cmd);

s8 SetDstHandle(u8 pcnt,u8 **plist,void *pdata);
//s8 SetDstHandle(u8 *pcmd,u8 pcnt,u8 **plist,void *pdata);
s8 SetFss0Handle(u8 pcnt,u8 **plist,void *pdata);
s8 GetDstHandle(u8 pcnt,u8 **plist);
//s8 GetDstHandle(u8 *pcmd,u8 pcnt,u8 **plist,void *pdata);
s8 GetFss0Handle(u8 *pcmd,u8 pcnt,u8 **plist,void *pdata);

s8 SetCalHandle(u8 pcnt,u8 **plist);
//s8 SetCalHandle(u8 *pcmd,u8 pcnt,u8 **plist,void *pdata);
s8 GetCalHandle(u8 pcnt,u8 **plist);
//s8 GetCalHandle(u8 *pcmd,u8 pcnt,u8 **plist,void *pdata);

void GetDeviceInfo(u8 *info);
void GetDeviceHealth(u8 *hlth);
#endif
