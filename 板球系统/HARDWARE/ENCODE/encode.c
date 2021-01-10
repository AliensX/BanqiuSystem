/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,����ΰҵ
 * All rights reserved.
 *
 * �����������ݰ�Ȩ��������ΰҵ���У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣������ΰҵ�İ�Ȩ������
 *
 * @file       		ENCODE
 * @company	   		��������ѧ
 * @author     		����ΰҵ
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-01-31
 ********************************************************************************************************************/
#include "headfile.h"
#include "encode.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߼���ʱ��������ģʽ��ʼ��
//  @param      TIMx          ��ʱ��ѡ��TIMER1��TIMER8��
//  @return     void
//  Sample usage:             Encode_AdvTIMER_Init(TIMER1);    //��TIM1����Ϊ˫���ر�����ģʽ
//-------------------------------------------------------------------------------------------------------------------
void Encode_AdvTIMER_Init(ADV_TIMER TIMx)
{
	switch((u8)TIMx)
	{
		case (u8)TIMER1:
				RCC->APB2ENR |= 1<<0;
				RCC->AHB1ENR |= 1<<4;

				GPIO_Select(GPIOE,P9,MUX,F);			//TIM1������ģʽA���ѡ��PA8��PE9
				GPIO_Select(GPIOE,P11,MUX,F);			//TIM1������ģʽB���ѡ��PA9��PE11
				GPIO_AF_Set(GPIOE,9,1);
				GPIO_AF_Set(GPIOE,11,1);
		
				TIM1->ARR = 0xFFFF;
				TIM1->PSC = 0;
				 
				TIM1->CCMR1 |=	1<<0;
				TIM1->CCMR1 |=	1<<8;  
				 
				TIM1->SMCR |=3<<0;
				TIM1->CR1 |= 1<<0;
				break;
		case (u8)TIMER8:
				RCC->APB2ENR |= 1<<1;
				RCC->AHB1ENR |= 1<<2;

				GPIO_Select(GPIOC,P6,MUX,F);			//TIM8������ģʽA���ѡ��PC6
				GPIO_Select(GPIOC,P7,MUX,F);			//TIM8������ģʽB���ѡ��PC7
				GPIO_AF_Set(GPIOC,6,3);
				GPIO_AF_Set(GPIOC,7,3);
		
			  TIM8->ARR = 0xFFFF;
				TIM8->PSC = 0;
    
				TIM8->CCMR1 |=	1<<0;
				TIM8->CCMR1 |=	1<<8;
     
				TIM8->SMCR |=3<<0;
				TIM8->CR1 |= 1<<0;
				break;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߼���ʱ��������ģʽ��ȡ�ٶ�
//  @param      TIMx          ��ʱ��ѡ��TIMER1��TIMER8��
//  @return     int
//  Sample usage:             speed = Encode_AdvTIMER_SpeedGet(TIMER1);    //��ȡTIM1������ģʽ�µ��ٶ�ֵ
//-------------------------------------------------------------------------------------------------------------------
int Encode_AdvTIMER_SpeedGet(ADV_TIMER TIMx)
{
	int SpeedCnt = 0;
	u8 flag;
	
	switch((u8)TIMx)
	{
		case (u8)TIMER1:
				flag = 1;
				break;
		case (u8)TIMER8:
				flag = 0;
				break;
	}
	
	if(flag)
	{
		SpeedCnt = TIM1->CNT;
		TIM1->CNT = 0x0;
		return SpeedCnt;
	}
	else
	{
		SpeedCnt = TIM8->CNT;
		TIM8->CNT = 0x0;
		return SpeedCnt;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ͨ�ö�ʱ��������ģʽ��ʼ��
//  @param      TIMx          ��ʱ��ѡ��TIMER2~TIMER5��
//  @return     void
//  Sample usage:             Encode_GenTIMER_Init(TIMER3);    //��TIM3����Ϊ˫���ر�����ģʽ
//-------------------------------------------------------------------------------------------------------------------
void Encode_GenTIMER_Init(GENERAL_TIMER TIMx)
{
	switch((u8)TIMx)
	{
		case (u8)TIMER2:
				RCC->APB1ENR|=1<<0;
	
				GPIO_Select(GPIOA,P5,MUX,F);			//TIM2������ģʽA���ѡ��PA0��PA5��PA15
				GPIO_Select(GPIOB,P3,MUX,F);			//TIM2������ģʽB���ѡ��PA1��PB3
				GPIO_AF_Set(GPIOA,5,1);
				GPIO_AF_Set(GPIOB,3,1);

				TIM2->ARR = 0xFFFF;
				TIM2->PSC = 0;

				TIM2->CCMR1 |=	1<<0;
				TIM2->CCMR1 |=	1<<8;    

				TIM2->SMCR |=3<<0;
				TIM2->CR1 |= 1<<0;
				break;
		case (u8)TIMER3:
				RCC->APB1ENR|=1<<1;
	
				GPIO_Select(GPIOA,P6,MUX,F);			//TIM3������ģʽA���ѡ��PA6��PB4��PC6
				GPIO_Select(GPIOA,P7,MUX,F);			//TIM3������ģʽB���ѡ��PA7��PB5��PC7
				GPIO_AF_Set(GPIOA,6,2);
				GPIO_AF_Set(GPIOA,7,2);

				TIM3->ARR = 0xFFFF;
				TIM3->PSC = 0;

				TIM3->CCMR1 |=	1<<0;
				TIM3->CCMR1 |=	1<<8;    

				TIM3->SMCR |=3<<0;
				TIM3->CR1 |= 1<<0;
				break;
		case (u8)TIMER4:
				RCC->APB1ENR|=1<<2;
	
				GPIO_Select(GPIOB,P6,MUX,F);			//TIM4������ģʽA���ѡ��PB6��PD12
				GPIO_Select(GPIOB,P7,MUX,F);			//TIM4������ģʽB���ѡ��PB7��PD13
				GPIO_AF_Set(GPIOB,6,2);
				GPIO_AF_Set(GPIOB,7,2);

				TIM4->ARR = 0xFFFF;
				TIM4->PSC = 0;

				TIM4->CCMR1 |=	1<<0;
				TIM4->CCMR1 |=	1<<8;    

				TIM4->SMCR |=3<<0;
				TIM4->CR1 |= 1<<0;
				break;
		case (u8)TIMER5:
				RCC->APB1ENR|=1<<3;
	
				GPIO_Select(GPIOA,P0,MUX,F);			//TIM5������ģʽA���ѡ��PA0
				GPIO_Select(GPIOA,P1,MUX,F);			//TIM5������ģʽB���ѡ��PA1
				GPIO_AF_Set(GPIOA,0,2);
				GPIO_AF_Set(GPIOA,1,2);

				TIM5->ARR = 0xFFFF;
				TIM5->PSC = 0;

				TIM5->CCMR1 |=	1<<0;
				TIM5->CCMR1 |=	1<<8;    

				TIM5->SMCR |=3<<0;
				TIM5->CR1 |= 1<<0;
				break;
		
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ͨ�ö�ʱ��������ģʽ��ȡ�ٶ�
//  @param      TIMx          ��ʱ��ѡ��TIMER2~TIMER5��
//  @return     int
//  Sample usage:             speed = Encode_GenTIMER_SpeedGet(TIMER3);    //��ȡTIM3������ģʽ�µ��ٶ�ֵ
//-------------------------------------------------------------------------------------------------------------------
int Encode_GenTIMER_SpeedGet(GENERAL_TIMER TIMx)
{
	int cnt=0;
	
	switch((u8)TIMx)
	{
		case (u8)TIMER2:
				cnt=TIM2->CNT;
				TIM2->CNT=0;
				return cnt;
		case (u8)TIMER3:
				cnt=TIM3->CNT;
				TIM3->CNT=0;
				return cnt;
		case (u8)TIMER4:
				cnt=TIM4->CNT;
				TIM4->CNT=0;
				return cnt;
		case (u8)TIMER5:
				cnt=TIM5->CNT;
				TIM5->CNT=0;
				return cnt;
	}
	return 0;
}





