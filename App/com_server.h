
#ifndef __COM_SERVER_H
#define __COM_SERVER_H

#include "system.h"



int ComServerInitial(void);
int ComServerPeriodicHandle(void);
int ComMsgParse(u8 *pbuf,u16 length);
int ComServerGetPara(u8 *src,u8 **pParaList,u8 *paracnt,u8 **cmdstr);

#endif
