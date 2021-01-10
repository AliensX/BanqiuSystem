#ifndef _SIM_IIC_H
#define _SIM_IIC_H

#include "headfile.h"

//IO��������
#define SDA_IN()  {GPIO_Select(GPIOF,P8,INPUT,H);}
#define SDA_OUT() {GPIO_Select(GPIOF,P8,OUTPUT,H);}
//IO��������	 
#define IIC_SCL    PFout(9) 	//SCL
#define IIC_SDA    PFout(8) 	//SDA	 
#define READ_SDA   PFin(8) 	  //����SDA 
//IIC���в�������
void IIC_Init(void);               	  //��ʼ��IIC��IO��				 
void IIC_Start(void);									//����IIC��ʼ�ź�
void IIC_Stop(void);	  								//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);							//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);		//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 									//IIC�ȴ�ACK�ź�
void IIC_Ack(void);										//IIC����ACK�ź�
void IIC_NAck(void);									  //IIC������ACK�ź�

u8 IIC_Set_Reg(u8 addr,u8 data,u8 Dev_addr);				//IIC�����Ĵ�������
u8 IIC_Read_Reg(u8 addr,u8 Dev_addr);								//IIC�����Ĵ�����ȡ



#endif



