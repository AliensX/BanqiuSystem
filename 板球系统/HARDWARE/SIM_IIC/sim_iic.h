#ifndef _SIM_IIC_H
#define _SIM_IIC_H

#include "headfile.h"

//IO方向设置
#define SDA_IN()  {GPIO_Select(GPIOF,P8,INPUT,H);}
#define SDA_OUT() {GPIO_Select(GPIOF,P8,OUTPUT,H);}
//IO操作函数	 
#define IIC_SCL    PFout(9) 	//SCL
#define IIC_SDA    PFout(8) 	//SDA	 
#define READ_SDA   PFin(8) 	  //输入SDA 
//IIC所有操作函数
void IIC_Init(void);               	  //初始化IIC的IO口				 
void IIC_Start(void);									//发送IIC开始信号
void IIC_Stop(void);	  								//发送IIC停止信号
void IIC_Send_Byte(u8 txd);							//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);		//IIC读取一个字节
u8 IIC_Wait_Ack(void); 									//IIC等待ACK信号
void IIC_Ack(void);										//IIC发送ACK信号
void IIC_NAck(void);									  //IIC不发送ACK信号

u8 IIC_Set_Reg(u8 addr,u8 data,u8 Dev_addr);				//IIC器件寄存器配置
u8 IIC_Read_Reg(u8 addr,u8 Dev_addr);								//IIC器件寄存器读取



#endif



