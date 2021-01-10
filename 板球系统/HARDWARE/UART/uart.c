/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,����ΰҵ
 * All rights reserved.
 *
 * �����������ݰ�Ȩ��������ΰҵ���У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣������ΰҵ�İ�Ȩ������
 *
 * @file       		UART
 * @company	   		��������ѧ
 * @author     		����ΰҵ
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-02-03
 ********************************************************************************************************************/
#include "headfile.h"
#include "uart.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      USART��ʼ��
//  @param      USARTx            	  ѡ��USART��USART1��USART2��USART3��USART6��
//  @param      bound              	  ���������ã�����9600��115200��
//  @return     void
//  Sample usage:             		  Usart_Init(USART6,9600);    //����USART6��ʼ��
//-------------------------------------------------------------------------------------------------------------------
void Usart_Init(USART_TypeDef* USARTx,u32 bound)
{
	float temp;
	u32 mantissa;			//USARTDIV��������
	u32 fraction;			//USARTDIVС������
	
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
		
	USARTx->CR1|=1<<3;		//������ʹ��
	
	USARTx->CR1|=1<<2;		//������ʹ��
	
#if  USART_RXIT_EN
	USARTx->CR1|=1<<5;		//RXNE�ж�ʹ��
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
	
	USARTx->CR1|=1<<13;		//USARTʹ��
	USARTx->SR&=~(1<<6);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      USART��������
//  @param      USARTx            	  ѡ��USART��USART1��USART2��USART3��USART6��
//  @param      data              	  ���������ݣ�8λ��
//  @return     void
//  Sample usage:             		  Usart_Send(USART6,'s');    //USART6�����ַ�'s'
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
    /* �ֲ���̬���������ջ��� */
    static u8 RxBuffer[4];
    /* ���ݳ��� *//* ���������±� */
    static u8  _data_cnt = 0;
    /* ����״̬ */
    static u8 state = 0;
 
    /* ֡ͷ1 */
    if(state==0&&data==TITLE1)
    {
        state=1;
    }
    /* ֡ͷ2 */
    else if(state==1&&data==TITLE2)
    {
        state=2;
        _data_cnt = 0;
    }
    /* ���������� */
    else if(state==2)
    {
        RxBuffer[++_data_cnt]=data;
        if(_data_cnt>=2)
        {
            state = 0;
            Data_Processing(RxBuffer,_data_cnt);
						flag_control = 1;	//�������ڱ�־λ��λ
        }
    }
    /* ���д������µȴ�����֡ͷ */
    else
        state = 0;
}
 
 

void Data_Processing(u8 *data_buf,u8 num)
{
	int theta_org,rho_org;
    /* ��ȡƫ�ƽǶ�ԭʼ����  */
    //theta_org = (int)(*(data_buf+1)<<0) | (int)(*(data_buf+2)<<8) | (int)(*(data_buf+3)<<16) | (int)(*(data_buf+4)<<24) ;
    //theta_err = theta_org;
	
	  theta_org = (char)(*(data_buf+1)<<0); //| (char)(*(data_buf+2)<<8); //| (int)(*(data_buf+3)<<16) | (int)(*(data_buf+4)<<24) ;
    theta_err = theta_org;
    /* ��ȡƫ�Ƴߴ�ԭʼ���� */
    //rho_org = (int)(*(data_buf+5)<<0) | (int)(*(data_buf+6)<<8) | (int)(*(data_buf+7)<<16) | (int)(*(data_buf+8)<<24) ;
    //rho_err = rho_org;
	  rho_org = (char)(*(data_buf+2)<<0); //| (char)(*(data_buf+4)<<8);//| (int)(*(data_buf+7)<<16) | (int)(*(data_buf+8)<<24) ;
	  rho_err = rho_org;
		X=theta_org;
		Y=rho_org;
}










