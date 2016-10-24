#ifndef	_I2C_H
#define _I2C_H

#include "system.h"

#ifdef 	EVAL_BOARD	//����ÿ�����
//IO��������
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<28;}

//IO��������	 
#define IIC_SCL    		PBout(6) //SCL
#define IIC_SDA    		PBout(7) //SDA	 
#define READ_SDA   		PBin(7)  //����SDA 

#else
//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

//IO��������	 
#define IIC_SCL    		PBout(8) //SCL
#define IIC_SDA    		PBout(9) //SDA	 
#define READ_SDA   		PBin(9)  //����SDA 

#endif

#define I2C_OWN_ADDRESS	0xA0
//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void 	I2C_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 		I2C_Read_One_Byte(u8 daddr,u8 addr);
bool	I2C_Read_Multi_Bytes(uint8_t iMainAddr, uint8_t iSubAddr, uint8_t iCount, uint8_t	*pData);



#endif
