#include "i2c.h"
#include "delay.h"
/****************************************************************************
* 名	称：IIC_Init
* 功    能：初始化IIC1
* 入口参数：无          
* 出口参数：无
* 注	意：IIC1重映射 IIC1_SCL->PB8，IIC1_SDA->PB9
****************************************************************************/
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;	
	I2C_InitTypeDef  I2C_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //复用开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9); 	//PB8,PB9 输出高
	
#ifdef IIC_SIM  //如果使用模拟IIC

#else 
	I2C_DeInit(I2C1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE ); //打开复用功能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE ); //打开I2C1时钟
	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);//重映射到PB8 PB9
	I2C_InitStructure.I2C_ClockSpeed = 20000;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = I2C_OWN_ADDRESS;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

	I2C_Cmd(I2C1, ENABLE);// 
	I2C_Init(I2C1, &I2C_InitStructure);
#endif

}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	DelayUs(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	DelayUs(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	DelayUs(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	DelayUs(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;DelayUs(1);	   
	IIC_SCL=1;DelayUs(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	DelayUs(2);
	IIC_SCL=1;
	DelayUs(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	DelayUs(2);
	IIC_SCL=1;
	DelayUs(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;  

		SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		DelayUs(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		DelayUs(2); 
		IIC_SCL=0;	
		DelayUs(2);
    }
		 
} 
//写一串数据
void IIC_Write(u8 *str,u16 len)
{

}	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;

	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        DelayUs(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		DelayUs(1); 
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   

	return receive;
}
void I2C_Write_One_Byte(u8 daddr,u8 addr,u8 data)
{
	return;
}

u8 I2C_Read_One_Byte(u8 daddr,u8 addr)
{
	return 0;
}

bool	I2C_Read_Multi_Bytes(uint8_t iMainAddr, uint8_t iSubAddr, uint8_t iCount, uint8_t	*pData)
{
	return TRUE;
}