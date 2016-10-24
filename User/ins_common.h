
#ifndef __INS_COMMON_H
#define __INS_COMMON_H

#include "system.h"


//--------------------------------------------
typedef struct
{
	char *InsStr;//instruction string
	int (*handle)(u8 **pplist,u8 pcnt);
	char *InsNote;//Ö¸ÁîËµÃ÷
}_S_InsInfo_t;




#endif














