/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,徐氏伟业
 * All rights reserved.
 *
 * 以下所有内容版权均属徐氏伟业所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留徐氏伟业的版权声明。
 *
 * @file       		UART
 * @company	   		华北理工大学
 * @author     		徐氏伟业
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-02-03
 ********************************************************************************************************************/
#include "headfile.h"
#include "uart.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      USART初始化
//  @param      USARTx            	  选择USART（USART1、USART2、USART3、USART6）
//  @param      bound              	  波特率设置（常用9600、115200）
//  @return     void
//  Sample usage:             		  Usart_Init(USART6,9600);    //串口USART6初始化
//-------------------------------------------------------------------------------------------------------------------
void Usart_Init(USART_TypeDef* USARTx,u32 bound)
{
	float temp;
	u32 mantissa;			//USARTDIV整数部分
	u32 fraction;			//USARTDIV小数部分
	
	if(USARTx==USART6||USARTx==USART1)
		temp=(float)(PCLK2)/(16*bound);
	else
		temp=(float)(PCLK1)/(16*bound);
	mantissa=temp;
	fraction=(u32)(temp-mantissa)*16;
	mantissa<<=4;
	mantissa|=fraction;
	
	switch((u32)USARTx)
	{
		case (u32)USART1:
		  	RCC->APB2ENR|=1<<4;
				GPIO_Select(GPIOA,P9,MUX,F);		//Tx
				GPIO_AF_Set(GPIOA,9,7);
				GPIO_Select(GPIOA,P10,MUX,F);		//Rx
				GPIO_AF_Set(GPIOA,10,7);
				break;
		case (u32)USART2:
				RCC->APB1ENR|=1<<17;
				GPIO_Select(GPIOA,P2,MUX,F);		//Tx
				GPIO_AF_Set(GPIOA,2,7);
			  GPIO_Select(GPIOA,P3,MUX,F);		//Rx
				GPIO_AF_Set(GPIOA,3,7);
				break;
		case (u32)USART3:
				RCC->APB1ENR|=1<<18;
				GPIO_Select(GPIOB,P10,MUX,F);		//Tx
				GPIO_AF_Set(GPIOB,10,7);
				GPIO_Select(GPIOB,P11,MUX,F);		//Rx
				GPIO_AF_Set(GPIOB,11,7);
				break;
		case (u32)USART6:
				RCC->APB2ENR|=1<<5;
				GPIO_Select(GPIOC,P6,MUX,F);		//Tx
				GPIO_AF_Set(GPIOC,6,8);
				GPIO_Select(GPIOC,P7,MUX,F);		//Rx
				GPIO_AF_Set(GPIOC,7,8);
				break;
	}
	
	USARTx->BRR|=(u16)mantissa;
		
	USARTx->CR1|=1<<3;		//发送器使能
	
	USARTx->CR1|=1<<2;		//接收器使能
	
#if  USART_RXIT_EN
	USARTx->CR1|=1<<5;		//RXNE中断使能
	switch((u32)USARTx)
	{
		case (u32)USART1:
				MY_NVIC_Init(1,2,USART1_IRQn,2);
				break;
		case (u32)USART2:
				MY_NVIC_Init(1,2,USART2_IRQn,2);
				break;
		case (u32)USART3:
				MY_NVIC_Init(1,2,USART3_IRQn,2);
				break;
		case (u32)USART6:
				MY_NVIC_Init(1,2,USART6_IRQn,2);
				break;
	}
#endif
	
	USARTx->CR1|=1<<13;		//USART使能
	USARTx->SR&=~(1<<6);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      USART发送数据
//  @param      USARTx            	  选择USART（USART1、USART2、USART3、USART6）
//  @param      data              	  待发送数据（8位）
//  @return     void
//  Sample usage:             		  Usart_Send(USART6,'s');    //USART6发送字符's'
//-------------------------------------------------------------------------------------------------------------------
void Usart_Send(USART_TypeDef* USARTx,u8 data)
{
	USARTx->SR&=~(1<<6);
	USARTx->DR=data;
	while(!(USARTx->SR&0x40));
}



int theta_err,rho_err;

void Optical_Flow_Receive_Prepare(u8 data)
{
    /* 局部静态变量：接收缓存 */
    static u8 RxBuffer[4];
    /* 数据长度 *//* 数据数组下标 */
    static u8  _data_cnt = 0;
    /* 接收状态 */
    static u8 state = 0;
 
    /* 帧头1 */
    if(state==0&&data==TITLE1)
    {
        state=1;
    }
    /* 帧头2 */
    else if(state==1&&data==TITLE2)
    {
        state=2;
        _data_cnt = 0;
    }
    /* 接收数据租 */
    else if(state==2)
    {
        RxBuffer[++_data_cnt]=data;
        if(_data_cnt>=2)
        {
            state = 0;
            Data_Processing(RxBuffer,_data_cnt);
						flag_control = 1;	//控制周期标志位置位
        }
    }
    /* 若有错误重新等待接收帧头 */
    else
        state = 0;
}
 
 

void Data_Processing(u8 *data_buf,u8 num)
{
	int theta_org,rho_org;
    /* 读取偏移角度原始数据  */
    //theta_org = (int)(*(data_buf+1)<<0) | (int)(*(data_buf+2)<<8) | (int)(*(data_buf+3)<<16) | (int)(*(data_buf+4)<<24) ;
    //theta_err = theta_org;
	
	  theta_org = (char)(*(data_buf+1)<<0); //| (char)(*(data_buf+2)<<8); //| (int)(*(data_buf+3)<<16) | (int)(*(data_buf+4)<<24) ;
    theta_err = theta_org;
    /* 读取偏移尺寸原始数据 */
    //rho_org = (int)(*(data_buf+5)<<0) | (int)(*(data_buf+6)<<8) | (int)(*(data_buf+7)<<16) | (int)(*(data_buf+8)<<24) ;
    //rho_err = rho_org;
	  rho_org = (char)(*(data_buf+2)<<0); //| (char)(*(data_buf+4)<<8);//| (int)(*(data_buf+7)<<16) | (int)(*(data_buf+8)<<24) ;
	  rho_err = rho_org;
		X=theta_org;
		Y=rho_org;
}










