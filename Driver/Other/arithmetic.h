/*---------------------------------------------------------------------*/
/*
* File name   : arithmetic.h
* Author      : Neal.deng
* Version     : 1.1.0
* Date        : 2015-03-11
* Description : 大数四则运算
* others      :
* FunctionList:
* History     :
*   1. Date:   2015-11-25
*      Reason: BigMul大于64Bit运算时进位大于0xff时出错
*      Author: Neal.deng
*      Modification:
            1. uint16_t bigbuf -> uint32_t
            2. uint8_t c_flag  -> uint16_t
*/
/*---------------------------------------------------------------------*/
//arithmetic

#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H

#include <stdint.h>
//---------------------------
	
typedef struct{
	uint8_t pol;		//polarity:  0=positive;1=negative
	uint8_t point;		//decimal point: 0=none,1=have 
	uint8_t *intg;		//integer part,low->high
	uint8_t int_len;	//integer part length
	uint8_t *decm;		//8bit decimal part: samll denomiator -> big
	uint8_t decm_len;	//integer part length
}S_BigNum_t;


//Integer
//x=x+y
//>=0,back, back_x size
//<0,error
int BigAdd(uint8_t *x,uint8_t size_x,
			uint8_t *y, uint8_t size_y);
//x = x-y
//>=0,back, back_x size
//<0,x<y size
int BigSub(uint8_t *x,uint8_t size_x,
			uint8_t *y, uint8_t size_y);
//x=x*y
//>=0,back, back_x size
//<0,error
int BigMul(uint8_t *x,uint8_t size_x,
			uint8_t *y, uint8_t size_y);
//x=x%y,q=x/y
int BigDiv(uint8_t *x,uint8_t size_x,
			uint8_t *y, uint8_t size_y,
			uint8_t *q, uint8_t *size_q);

#if 0
//float
//x=x+y
int BigFloatAdd(S_BigNum_t *x, S_BigNum_t y);
//x = x-y
int BigFloatSub(S_BigNum_t *x, S_BigNum_t y);
//y=x*y
int BigFloatMul(S_BigNum_t *x, S_BigNum_t y);
//x=x/y
int BigFloatDiv(S_BigNum_t *x, S_BigNum_t y);
#endif

#endif
//-----------------------------------------------------------------------
//end file

