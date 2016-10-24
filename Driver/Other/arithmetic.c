/*---------------------------------------------------------------------*/
/*
* File name   : arithmetic.c
* Author      : Neal.deng
* Version     : 2.0.0
* Date        : 2015-12-05
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


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "arithmetic.h"

//-----------------------------------

//get big data  byte length
uint16_t GetDataByteLen(uint8_t *pbuf, uint8_t len)
{
	uint8_t *p;
	int i;

	p = pbuf;
	for(i=len-1; i>=0; i--)
	{
		if(p[i] != 0)
		{
			break;
		}
	}

	return i+1;
}

//compare 
//-1 : x<y
// 0 : x==y
// 1 : x>y
int CompareFloatBigData(S_BigNum_t x, S_BigNum_t y)
{
	uint8_t *p1,*p2;
	uint16_t len_x,len_y;
	int i,j;

	//polarity compare
	if(x.pol > y.pol)
	{
		return 1;
	}
	else if(x.pol < y.pol)
	{
		return -1;
	}

	//integer part compare
	len_x = GetDataByteLen(x.intg,x.int_len);
	len_y = GetDataByteLen(y.intg,y.int_len);

	if(len_x > len_y)
	{
		return 1;
	}
	else if(len_x < len_y)
	{
		return -1;
	}

	p1=x.intg;
	p2=y.intg;
	for(i=len_x-1; i>=0; i--)
	{
		if(p1[i] > p2[i])
		{
			return 1;
		}
		else if(p1[i] < p2[i])
		{
			return -1;
		}
	}

	if((x.point == y.point)&&(0 == x.point))
	{
		return 0;
	}
	else if(x.point > y.point)
	{
		return 1;
	}
	else if(x.point < y.point)
	{
		return -1;
	}

	//decimal part compare
	len_x = GetDataByteLen(x.decm,x.decm_len);
	len_y = GetDataByteLen(y.decm,y.decm_len);

	p1=x.decm;
	p2=y.decm;
	for(i=0,j=0; i<len_x&&j<len_y; i++,j++)
	{
		if(p1[i]>p2[i])
		{
			return 1;
		}
		else if(p1[i] < p2[i])
		{
			return -1;
		}
	}

	if(len_x == len_y)
	{
		return 0;
	}
	else if(len_x > len_y)
	{
		return 1;
	}
	else
	{
		return -1;
	}

}


//compare integer
//-1 : x<y
// 0 : x==y
// 1 : x>y
int CompareIntegBigData(uint8_t *x,uint8_t len_x, 
						uint8_t *y, uint8_t len_y)
{
	int i;

	//integer part compare

	if(len_x > len_y)
	{
		return 1;
	}
	else if(len_x < len_y)
	{
		return -1;
	}

	for(i=len_x-1; i>=0; i--)
	{
		if(x[i] > y[i])
		{
			return 1;
		}
		else if(x[i] < y[i])
		{
			return -1;
		}
	}

	return 0;
}


//Integer
//x=x+y
//>=0,back, back_x size
//<0,error
int BigAdd(uint8_t *x,uint8_t size_x,
			uint8_t *y, uint8_t size_y)
{
	uint8_t len_x, len_y,len;
	uint8_t c_flag=0;
	uint16_t tmp;
	uint64_t tmp_x,tmp_y;
	int i,ret;

	if(size_x < size_y)
	{
		return -1;
	}

	//get true byte len
	len_x = GetDataByteLen(x, size_x);
	len_y = GetDataByteLen(y, size_y);

	len = (len_x>=len_y)?len_x:len_y;

	if(len <= 7)
	{
		tmp_x =0;
		tmp_y = 0;
		for(i=len_x-1; i>=0; i--)
		{
			tmp_x = tmp_x<<8;
			tmp_x |= x[i];
		}
		for(i=len_y-1; i>=0; i--)
		{
			tmp_y = tmp_y<<8;
			tmp_y |= y[i];
		}
    
		tmp_x += tmp_y;
		
		for(i=0; i<len+1; i++)
		{
			x[i] = tmp_x&0xff;
			tmp_x = tmp_x >> 8;
		}
		
		ret = GetDataByteLen(x, len+1);
		return (ret>0)?ret:1;
	}

	//big 
	c_flag = 0;
	tmp=0;
	for(i=0; i<len; i++)
	{
		tmp = x[i] + y[i];
		tmp += c_flag;
		if(tmp >= 0x100)
		{
			c_flag = 1;
			x[i] = tmp-0x100;
		}
		else
		{
			x[i] = tmp;
			c_flag = 0;
		}
//		x[i] = tmp%0x100;
//		c_flag = tmp/0x100;
	}
	x[i++] += c_flag;

	ret = GetDataByteLen(x,i);
	return (ret>0)?ret:1;
}

//x = x-y
//>=0,back, ,x>y
//<0,x<y,back_x size
int BigSub(uint8_t *x,uint8_t size_x,
			uint8_t *y, uint8_t size_y)
{
	uint8_t len_x, len_y,len,len_max;
	uint8_t c_flag=0;
	uint16_t tmp;
//	uint8_t pz[32]={0};
	uint8_t *px,*py;
	uint64_t tmp_x,tmp_y;
	int i,ret;

	if(size_x < size_y)
	{
		return -1;
	}

	//get true byte len
	len_x = GetDataByteLen(x, size_x);
	len_y = GetDataByteLen(y, size_y);

	
	ret = CompareIntegBigData(x, len_x, y, len_y);
	if(0 == ret)
	{
		memset(x,0,size_x);
		return 1;
	}
	else if(ret > 0)
	{
		len = len_y;
		len_max = len_x;
		px = x;
		py = y;
	}
	else
	{
		len = len_x;
		len_max = len_y;
		px = y;
		py = x;
	}

	if(len_max <= 8)
	{
		tmp_x =0;
		tmp_y = 0;
		for(i=len_x-1; i>=0; i--)
		{
			tmp_x = tmp_x<<8;
			tmp_x |= x[i];
		}
		for(i=len_y-1; i>=0; i--)
		{
			tmp_y = tmp_y<<8;
			tmp_y |= y[i];
		}

		if(tmp_x >= tmp_y)
		{
			c_flag = 1;
    		tmp_x -= tmp_y;
		}
		else
		{
			c_flag = 0;
    		tmp_x = tmp_y - tmp_x;
		}

		for(i=0; i<len_max; i++)
		{
			x[i] = tmp_x&0xff;
			tmp_x = tmp_x >> 8;
		}
		
		ret =GetDataByteLen(x, len_max);
		if(c_flag>0)
		{
			return (ret>0)?ret:1;
		}
		else
		{
			ret = (0-ret);
			return (ret>0)?ret:1;
		}

	}

	//big
	tmp = 0;
	c_flag=0;
	for(i=0; i<len; i++)
	{
		if(px[i] >= c_flag)
		{
			tmp = px[i]-c_flag;
			c_flag = 0;
		}
		else
		{
			tmp = px[i]+0x100-c_flag;
			c_flag = 1;
		}
		if(tmp >= py[i])
		{
			tmp = tmp-py[i];
		}
		else
		{
			tmp = tmp+0x100-py[i];
			c_flag = 1;
		}
		//pz[i] = tmp;
		x[i] = tmp;
	}

	for(; i<len_max; i++)
	{
		if(px[i]>=c_flag)
		{
			//pz[i] = px[i]-c_flag;
			x[i] = px[i]-c_flag;
			c_flag = 0;
		}
		else
		{
			//pz[i] = px[i]+0x100-c_flag;
			x[i] = px[i]+0x100-c_flag;
			c_flag = 1;
		}
	}

#if 0
	memset(x,0,size_x);
	for(i=0; i<len_max; i++)
	{
		x[i] = pz[i];
	}
#endif
	ret = GetDataByteLen(x,size_x);
	return (ret>0)?ret:1;
}


//x=x*y
//>=0,back, back_x size
//<0,error
#define BIG_MUL_SIZE	32
uint32_t bigbuf[BIG_MUL_SIZE][BIG_MUL_SIZE]={0};
int BigMul(uint8_t *x,uint8_t size_x,
			uint8_t *y, uint8_t size_y)
{

	uint8_t len_x, len_y,len;
	uint16_t c_flag=0;
	uint8_t tmp;
	uint64_t tmp_x,tmp_y;
	int i,nx,ny,ret;

	//get true byte len
	len_x = GetDataByteLen(x, size_x);
	len_y = GetDataByteLen(y, size_y);

	//count
	len = len_x+len_y;
	if((len > BIG_MUL_SIZE)||(len_x>(size_x-1)))
	{
		//buf too little
		return -1;
	}

	if(len <= 8)
	{
		tmp_x =0;
		tmp_y = 0;
		for(i=len_x-1; i>=0; i--)
		{
			tmp_x = tmp_x<<8;
			tmp_x |= x[i];
		}
		for(i=len_y-1; i>=0; i--)
		{
			tmp_y = tmp_y<<8;
			tmp_y |= y[i];
		}

		tmp_x *=tmp_y;

		for(i=0; i<len; i++)
		{
			x[i] = tmp_x&0xff;
			tmp_x = tmp_x >> 8;
		}
		ret = GetDataByteLen(x, len);
		return (ret>0)?ret:1;
	}


	//big
	memset(bigbuf,0,sizeof(bigbuf));
	//	An...A2A1A0*Bn...B2B1B0
	for(ny=0; ny<len_y; ny++)
	{
		for(nx=0; nx<len_x; nx++)
		{
			bigbuf[nx][ny]=x[nx]*y[ny];
		}
	}

	c_flag = 0;
	for(i=0; i<len; i++)
	{
		for(ny=0,nx=i; ny<i&&i>0; ny++,nx--)
		{
			bigbuf[0][i] += bigbuf[nx][ny];
		}
		
		tmp = bigbuf[0][i]%0x100;
		c_flag = bigbuf[0][i]/0x100;

		bigbuf[0][i+1] += c_flag;
		x[i] = tmp;
	}

	x[i] = bigbuf[0][i];

	ret = GetDataByteLen(x,i+1);
	return (ret>0)?ret:1;
}




#define DIV_BUF_LEN		32
int GetDiv(uint8_t *div, uint8_t index_d,uint8_t cnt, 
			uint8_t *buf,uint8_t index)
{
	int i=0,j;

	//shift
	for(i=index_d-1; i>=0; i--)
	{
		div[i+cnt]=div[i];
	}

	//get value
	for(i=cnt-1,j=1; i>=0; i--,j++)
	{
		div[i] = buf[index-j];
	}

	return GetDataByteLen(div, DIV_BUF_LEN);
}


//x=x%y,q=x/y
int BigDiv(uint8_t *x,uint8_t size_x,
			uint8_t *y, uint8_t size_y,
			uint8_t *q, uint8_t *size_q)
{
	uint8_t len_x, len_y,len;
//	uint8_t c_flag=0;
//	uint16_t tmp;
	uint8_t div[DIV_BUF_LEN]={0};
	uint8_t qu[DIV_BUF_LEN]={0};
	uint8_t index_x,index_d,cnt_qu;
	uint64_t tmp_x,tmp_y,tmp_q;
	int i,j,ret;

	
	//get true byte len
	len_x = GetDataByteLen(x, size_x);
	len_y = GetDataByteLen(y, size_y);

	if(0 == len_y)
	{
		return -1;
	}
	//count
	len = len_x+1-len_y;
	if(*size_q < len)
	{
		//quotient buf too little
		return -2;
	}

	ret = CompareIntegBigData(x, len_x, y, len_y);
	if(ret < 0)
	{
		*size_q = 1;
		return (len_x>0)?len_x:1;
	}
	else if(0 == ret)
	{
		q[0] = 1;
		*size_q = 1;
		memset(x,0,size_x);
		return 1;
	}

	
	if(len_x <= 8)
	{
		tmp_x =0;
		tmp_y = 0;
		for(i=len_x-1; i>=0; i--)
		{
			tmp_x = tmp_x<<8;
			tmp_x |= x[i];
		}
		for(i=len_y-1; i>=0; i--)
		{
			tmp_y = tmp_y<<8;
			tmp_y |= y[i];
		}

		tmp_q = tmp_x / tmp_y;
		for(i=0; i<len; i++)
		{
			q[i] = tmp_q&0xff;
			tmp_q = tmp_q >> 8;
		}
		ret = GetDataByteLen(q, len);
		*size_q = (ret>0)?ret:1;

		tmp_x = tmp_x%tmp_y;

		memset(x,0,sizeof(x)/sizeof(x[0]));
		for(i=0; i<len_x; i++)
		{
			x[i] = tmp_x&0xff;
			tmp_x = tmp_x >> 8;
		}
		ret = GetDataByteLen(x, len_x);
		return (ret>0)?ret:1;
	}
#if 0
	else if(len_y <= 8)
	{
		tmp_x =0;
		tmp_y = 0;
		for(i=len_x-1; i>=0; i--)
		{
			tmp_x = tmp_x<<8;
			tmp_x |= x[i];
		}
		for(i=len_y-1; i>=0; i--)
		{
			tmp_y = tmp_y<<8;
			tmp_y |= y[i];
		}
		while(1)
		{
		
		
		
		}

	}
#endif
	//big
	index_d =0;
	cnt_qu=0;
	index_x = len_x;
	ret = GetDiv(div,index_d,len_y,x,len_x);
	index_x -= len_y;
	index_d = ret;

	while(1)
	{
		ret = CompareIntegBigData(div,index_d,y,len_y);
		if(ret < 0)
		{
			qu[cnt_qu++] += 0;
			if(index_x > 0)
			{
				if((index_d)<DIV_BUF_LEN)
				{
					ret = GetDiv(div,index_d,1,x,index_x);
					index_d = ret;
					index_x--;
				}

				continue;
			}
			else
			{
				break;
			}
		}


		qu[cnt_qu] += 1;
		index_d = BigSub(div,index_d,y,len_y);
	}

	for(i=cnt_qu-1,j=0; i>=0&&j<cnt_qu; i--,j++)
	{
		q[i] = qu[j];
	}


	//*size_q = (cnt_qu>0)?cnt_qu:1;
	ret = GetDataByteLen(q, cnt_qu);
	*size_q = (ret>0)?ret:1;
	
	memset(x,0,size_x);
	index_d = GetDataByteLen(div, DIV_BUF_LEN);
	memcpy(x,div,index_d);
	
	return index_d>0?index_d:1;
}

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




//-------------------------------------------------------------------
//end file
