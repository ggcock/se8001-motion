#include "i2c.h"
#include "delay.h"
/****************************************************************************
* ��	�ƣ�IIC_Init
* ��    �ܣ���ʼ��IIC1
* ��ڲ�������          
* ���ڲ�������
* ע	�⣺IIC1��ӳ�� IIC1_SCL->PB8��IIC1_SDA->PB9
****************************************************************************/
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;	
	I2C_InitTypeDef  I2C_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //���ÿ�©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9); 	//PB8,PB9 �����
	
#ifdef IIC_SIM  //���ʹ��ģ��IIC

#else 
	I2C_DeInit(I2C1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE ); //�򿪸��ù���
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE ); //��I2C1ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);//��ӳ�䵽PB8 PB9
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
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	DelayUs(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	DelayUs(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	DelayUs(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	DelayUs(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;  

		SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		DelayUs(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		DelayUs(2); 
		IIC_SCL=0;	
		DelayUs(2);
    }
		 
} 
//дһ������
void IIC_Write(u8 *str,u16 len)
{

}	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;

	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   

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