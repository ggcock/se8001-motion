/*---------------------------------------------------------------------*/
/*
* File name   : IrSensor.c
* Author      : wuku.zeng
* Version     : 
* Date        : 2016-10-15
* Description : ���⴫��������
* others      :
* FunctionList:
* History     :
*   1. Date:
*      Reason:
*      Author:
*      Modification:
*/
/*---------------------------------------------------------------------*/

#include "IrSensor.h"

int IrSensorGpioInitial(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
//	NVIC_InitTypeDef NVIC_InitStructure;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//MVCC-PB13, TV-PB12 ��ͨ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 	
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13);
	
	//RS-PC8,MS-PC7,LS-PC6;��ʱ�����벶��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC, &GPIO_InitStructure); 	
	
	//MA-PB14,RMA-PB15,ENA-PB0,ENB-PB1;PWM���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|\
		GPIO_Pin_14|GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	//nock_RA-PD15,PWM���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	
	//LC-PD8,MC-PD9,RC-PD10,LMC-PD11,RMC-PD12,Knock_LC-PD13,Knock_RC-PD14,�ⲿ�ж�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10\
		|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//IN1-PE7,IN2-PE8,IN3-PE9,IN4-PE10;��ͨIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|\
		GPIO_Pin_9|GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOE, &GPIO_InitStructure); 	
	GPIO_SetBits(GPIOE,GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
	
	
	return 1;
}
























