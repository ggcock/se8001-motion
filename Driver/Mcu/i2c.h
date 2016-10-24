#ifndef	_I2C_H
#define _I2C_H

#include "system.h"

#ifdef 	EVAL_BOARD	//如果用开发板
//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<28;}

//IO操作函数	 
#define IIC_SCL    		PBout(6) //SCL
#define IIC_SDA    		PBout(7) //SDA	 
#define READ_SDA   		PBin(7)  //输入SDA 

#else
//IO方向设置
#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

//IO操作函数	 
#define IIC_SCL    		PBout(8) //SCL
#define IIC_SDA    		PBout(9) //SDA	 
#define READ_SDA   		PBin(9)  //输入SDA 

#endif

#define I2C_OWN_ADDRESS	0xA0
//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void 	I2C_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 		I2C_Read_One_Byte(u8 daddr,u8 addr);
bool	I2C_Read_Multi_Bytes(uint8_t iMainAddr, uint8_t iSubAddr, uint8_t iCount, uint8_t	*pData);



#endif
