/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,����ΰҵ
 * All rights reserved.
 *
 * �����������ݰ�Ȩ��������ΰҵ���У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣������ΰҵ�İ�Ȩ������
 *
 * @file       		TIMER
 * @company	   		��������ѧ
 * @author     		����ΰҵ
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-01-31
 ********************************************************************************************************************/
#include "headfile.h"
#include "timer.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TIMER��ʱ���жϳ�ʼ��
//  @param      arr           Ԥװ��ֵ
//  @param      psc           Ԥ��Ƶֵ
//  @param      TIMx          ��ʱ����TIM2��TIM3��TIM4��TIM5��TIM7��
//  @return     void
//  Sample usage:             TIMER_Init(499,8399,TIM7);    //TIM7����Ϊ5ms��ʱ���ж�
//-------------------------------------------------------------------------------------------------------------------
void TIMER_Init(u16 arr , u16 psc , TIM_TypeDef* TIMx)
{
	switch((u32)TIMx)
	{
	  case (u32)TIM7:
			RCC->APB1ENR|=1<<5;
		  MY_NVIC_Init(1,3,TIM7_IRQn,2);	
			break;
		case (u32)TIM2:
			RCC->APB1ENR|=1<<0;
		  MY_NVIC_Init(0,1,TIM2_IRQn,2);	
			break;
		case (u32)TIM3:
			RCC->APB1ENR|=1<<1;
		  MY_NVIC_Init(1,3,TIM3_IRQn,2);
			break;
		case (u32)TIM4:
			RCC->APB1ENR|=1<<2;
	  	MY_NVIC_Init(1,3,TIM4_IRQn,2);
			break;
		case (u32)TIM5:
			RCC->APB1ENR|=1<<3;
		  MY_NVIC_Init(1,3,TIM5_IRQn,2);
			break;
	};	
	TIMx->ARR=arr;
	TIMx->PSC=psc; 
	TIMx->DIER|=1<<0;
	TIMx->CR1|=1<<0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TIMER2 PWM��ʼ��
//  @param      arr           Ԥװ��ֵ
//  @param      psc           Ԥ��Ƶֵ
//  @param      ch            PWM���ͨ��ѡ�� ��CH1~CH4��
//  @param      duty          ��ʼռ�ձȣ� duty��(arr+1) ��
//  @return     void
//  Sample usage:             TIM2_PWM_Init(8399,0,CH4,2520);    //TIMER2 PWMͨ��4���30%ռ�ձȣ�Ƶ��Ϊ10KHz�ľ��β�
//-------------------------------------------------------------------------------------------------------------------
void TIM2_PWM_Init(u16 arr , u16 psc , GENERAL_TIMER_CH ch , u16 duty)
{
  RCC->APB1ENR|=1<<0;
	
	TIM2->ARR=arr;
	TIM2->PSC=psc;
	
	if(ch==CH1)
	{
	  GPIO_Select(GPIOA,P0,MUX,H);
		GPIO_AF_Set(GPIOA,0,1);
		TIM2->CCMR1|=1<<3;
		TIM2->CCMR1|=6<<4;
		TIM2->CCER|=1<<0;
		TIM2->CCER&=~(1<<1);
	}
	
	if(ch==CH2)
	{
	  GPIO_Select(GPIOA,P1,MUX,H);
		GPIO_AF_Set(GPIOA,1,1);
		TIM2->CCMR1|=1<<11;
		TIM2->CCMR1|=6<<12;
		TIM2->CCER|=1<<4;
		TIM2->CCER&=~(1<<5);
	}
	
	if(ch==CH3)
	{
		GPIO_Select(GPIOB,P10,MUX,H);
		GPIO_AF_Set(GPIOB,10,1);
		TIM2->CCMR2|=6<<4;    //CH3
		TIM2->CCMR2|=1<<3;
		TIM2->CCER|=1<<8;     //CH3
		TIM2->CCER&=~(1<<9);
	}

	if(ch==CH4)
	{
		GPIO_Select(GPIOB,P11,MUX,H);
		GPIO_AF_Set(GPIOB,11,1);
		TIM2->CCMR2|=6<<12;   //CH4
		TIM2->CCMR2|=1<<11;
		TIM2->CCER|=1<<12;    //CH4
		TIM2->CCER&=~(1<<13);
	}
	
	TIM2->CR1|=1<<7;
	TIM2->CR1|=1<<0;
	
	switch((u8)ch)
	{
		case (u8)CH1:
			TIM2->CCR1=duty;
			break;
		case (u8)CH2:
			TIM2->CCR2=duty;
			break;
	  case (u8)CH3:
			TIM2->CCR3=duty;
			break;
		case (u8)CH4:
			TIM2->CCR4=duty;
			break;
	};
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TIMER3 PWM��ʼ��
//  @param      arr           Ԥװ��ֵ
//  @param      psc           Ԥ��Ƶֵ
//  @param      ch            PWM���ͨ��ѡ�� ��CH1~CH4��
//  @param      duty          ��ʼռ�ձȣ� duty��(arr+1) ��
//  @return     void
//  Sample usage:             TIM3_PWM_Init(8399,0,CH4,2520);    //TIMER3 PWMͨ��4���30%ռ�ձȣ�Ƶ��Ϊ10KHz�ľ��β�
//-------------------------------------------------------------------------------------------------------------------
void TIM3_PWM_Init(u16 arr , u16 psc , GENERAL_TIMER_CH ch , u16 duty)
{
  RCC->APB1ENR|=1<<1;
	
	TIM3->ARR=arr;
	TIM3->PSC=psc;
	
	if(ch==CH1)
	{
	  GPIO_Select(GPIOA,P6,MUX,H);
		GPIO_AF_Set(GPIOA,6,2);
		TIM3->CCMR1|=1<<3;
		TIM3->CCMR1|=6<<4;
		TIM3->CCER|=1<<0;
		TIM3->CCER&=~(1<<1);
	}
	
	if(ch==CH2)
	{
	  GPIO_Select(GPIOA,P7,MUX,H);
		GPIO_AF_Set(GPIOA,7,2);
		TIM3->CCMR1|=1<<11;
		TIM3->CCMR1|=6<<12;
		TIM3->CCER|=1<<4;
		TIM3->CCER&=~(1<<5);
	}
	
	if(ch==CH3)
	{
		GPIO_Select(GPIOB,P0,MUX,H);
		GPIO_AF_Set(GPIOB,0,2);
		TIM3->CCMR2|=6<<4;    
		TIM3->CCMR2|=1<<3;
		TIM3->CCER|=1<<8;  
		TIM3->CCER&=~(1<<9);
	}

	if(ch==CH4)
	{
		GPIO_Select(GPIOB,P1,MUX,H);
		GPIO_AF_Set(GPIOB,1,2);
		TIM3->CCMR2|=6<<12; 
		TIM3->CCMR2|=1<<11;
		TIM3->CCER|=1<<12;  
		TIM3->CCER&=~(1<<13);
	}
	
	TIM3->CR1|=1<<7;
	TIM3->CR1|=1<<0;
	
	switch((u8)ch)
	{
		case (u8)CH1:
			TIM3->CCR1=duty;
			break;
		case (u8)CH2:
			TIM3->CCR2=duty;
			break;
	  case (u8)CH3:
			TIM3->CCR3=duty;
			break;
		case (u8)CH4:
			TIM3->CCR4=duty;
			break;
	};
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TIMER4 PWM��ʼ��
//  @param      arr           Ԥװ��ֵ
//  @param      psc           Ԥ��Ƶֵ
//  @param      ch            PWM���ͨ��ѡ�� ��CH1~CH4��
//  @param      duty          ��ʼռ�ձȣ� duty��(arr+1) ��
//  @return     void
//  Sample usage:             TIM4_PWM_Init(8399,0,CH4,2520);    //TIMER4 PWMͨ��4���30%ռ�ձȣ�Ƶ��Ϊ10KHz�ľ��β�
//-------------------------------------------------------------------------------------------------------------------
void TIM4_PWM_Init(u16 arr , u16 psc , GENERAL_TIMER_CH ch , u16 duty)
{
  RCC->APB1ENR|=1<<2;
	
	TIM4->ARR=arr;
	TIM4->PSC=psc;
	
	if(ch==CH1)
	{
	  GPIO_Select(GPIOB,P6,MUX,H);
		GPIO_AF_Set(GPIOB,6,2);
		TIM4->CCMR1|=1<<3;
		TIM4->CCMR1|=6<<4;
		TIM4->CCER|=1<<0;
		TIM4->CCER&=~(1<<1);
	}
	
	if(ch==CH2)
	{
	  GPIO_Select(GPIOB,P7,MUX,H);
		GPIO_AF_Set(GPIOB,7,2);
		TIM4->CCMR1|=1<<11;
		TIM4->CCMR1|=6<<12;
		TIM4->CCER|=1<<4;
		TIM4->CCER&=~(1<<5);
	}
	
	if(ch==CH3)
	{
		GPIO_Select(GPIOB,P8,MUX,H);
		GPIO_AF_Set(GPIOB,8,2);
		TIM4->CCMR2|=6<<4;    
		TIM4->CCMR2|=1<<3;
		TIM4->CCER|=1<<8;  
		TIM4->CCER&=~(1<<9);
	}

	if(ch==CH4)
	{
		GPIO_Select(GPIOB,P9,MUX,H);
		GPIO_AF_Set(GPIOB,9,2);
		TIM4->CCMR2|=6<<12; 
		TIM4->CCMR2|=1<<11;
		TIM4->CCER|=1<<12;  
		TIM4->CCER&=~(1<<13);
	}
	
	TIM4->CR1|=1<<7;
	TIM4->CR1|=1<<0;
	
	switch((u8)ch)
	{
		case (u8)CH1:
			TIM4->CCR1=duty;
			break;
		case (u8)CH2:
			TIM4->CCR2=duty;
			break;
	  case (u8)CH3:
			TIM4->CCR3=duty;
			break;
		case (u8)CH4:
			TIM4->CCR4=duty;
			break;
	};
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TIMER5 PWM��ʼ��
//  @param      arr           Ԥװ��ֵ
//  @param      psc           Ԥ��Ƶֵ
//  @param      ch            PWM���ͨ��ѡ�� ��CH1~CH4��
//  @param      duty          ��ʼռ�ձȣ� duty��(arr+1) ��
//  @return     void
//  Sample usage:             TIM5_PWM_Init(8399,0,CH4,2520);    //TIMER5 PWMͨ��4���30%ռ�ձȣ�Ƶ��Ϊ10KHz�ľ��β�
//-------------------------------------------------------------------------------------------------------------------
void TIM5_PWM_Init(u16 arr , u16 psc , GENERAL_TIMER_CH ch , u16 duty)
{
  RCC->APB1ENR|=1<<3;
	
	TIM5->ARR=arr;
	TIM5->PSC=psc;
	
	if(ch==CH1)
	{
	  GPIO_Select(GPIOA,P0,MUX,H);
		GPIO_AF_Set(GPIOA,0,2);
		TIM5->CCMR1|=1<<3;
		TIM5->CCMR1|=6<<4;
		TIM5->CCER|=1<<0;
		TIM5->CCER&=~(1<<1);
	}
	
	if(ch==CH2)
	{
	  GPIO_Select(GPIOA,P1,MUX,H);
		GPIO_AF_Set(GPIOA,1,2);
		TIM5->CCMR1|=1<<11;
		TIM5->CCMR1|=6<<12;
		TIM5->CCER|=1<<4;
		TIM5->CCER&=~(1<<5);
	}
	
	if(ch==CH3)
	{
		GPIO_Select(GPIOA,P2,MUX,H);
		GPIO_AF_Set(GPIOA,2,2);
		TIM5->CCMR2|=6<<4;    
		TIM5->CCMR2|=1<<3;
		TIM5->CCER|=1<<8;
		TIM5->CCER&=~(1<<9);
	}

	if(ch==CH4)
	{
		GPIO_Select(GPIOA,P3,MUX,H);
		GPIO_AF_Set(GPIOA,3,2);
		TIM5->CCMR2|=6<<12; 
		TIM5->CCMR2|=1<<11;
		TIM5->CCER|=1<<12;  
		TIM5->CCER&=~(1<<13);
	}
	
	TIM5->CR1|=1<<7;
	TIM5->CR1|=1<<0;
	
	switch((u8)ch)
	{
		case (u8)CH1:
			TIM5->CCR1=duty;
			break;
		case (u8)CH2:
			TIM5->CCR2=duty;
			break;
	  case (u8)CH3:
			TIM5->CCR3=duty;
			break;
		case (u8)CH4:
			TIM5->CCR4=duty;
			break;
	};
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWMռ�ձ��趨
//  @param      timer         ��ʱ������       ��TIMER2~TIMER5��                    
//  @param      ch            PWM���ͨ��ѡ��  ��CH1~CH4��
//  @param      duty          ��ʼռ�ձȣ� duty��(arr+1) ��
//  @return     void
//  Sample usage:             PWM_SetDuty(TIMER4,CH4,2520);    //TIMER4 PWMͨ��4���30%ռ�ձȵľ��β�
//-------------------------------------------------------------------------------------------------------------------
void PWM_SetDuty(GENERAL_TIMER timer , GENERAL_TIMER_CH ch , u16 duty)
{
  if(timer==TIMER2)
	{
	  switch((u8)ch)
		{
		  case (u8)CH1:
				TIM2->CCR1=duty;
				break;
			case (u8)CH2:
				TIM2->CCR2=duty;
				break;
			case (u8)CH3:
				TIM2->CCR3=duty;
				break;
			case (u8)CH4:
				TIM2->CCR4=duty;
				break;
		};
	}
	  if(timer==TIMER3)
	{
	  switch((u8)ch)
		{
		  case (u8)CH1:
				TIM3->CCR1=duty;
				break;
			case (u8)CH2:
				TIM3->CCR2=duty;
				break;
			case (u8)CH3:
				TIM3->CCR3=duty;
				break;
			case (u8)CH4:
				TIM3->CCR4=duty;
				break;
		};
	}
	  if(timer==TIMER4)
	{
	  switch((u8)ch)
		{
		  case (u8)CH1:
				TIM4->CCR1=duty;
				break;
			case (u8)CH2:
				TIM4->CCR2=duty;
				break;
			case (u8)CH3:
				TIM4->CCR3=duty;
				break;
			case (u8)CH4:
				TIM4->CCR4=duty;
				break;
		};
	}
	  if(timer==TIMER5)
	{
	  switch((u8)ch)
		{
		  case (u8)CH1:
				TIM5->CCR1=duty;
				break;
			case (u8)CH2:
				TIM5->CCR2=duty;
				break;
			case (u8)CH3:
				TIM5->CCR3=duty;
				break;
			case (u8)CH4:
				TIM5->CCR4=duty;
				break;
		};
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ͨ�ö�ʱ��ETR�ⲿ������ʼ��
//  @param      TIMx          ��ʱ������		��TIMER2~TIMER4��                    
//  @return     void
//  Sample usage:             TIMER_CNT_Init(TIMER3);    //TIMER3 ETR�ⲿ������ʼ��
//-------------------------------------------------------------------------------------------------------------------
void TIMER_CNT_Init(GENERAL_TIMER TIMx)
{
	switch((u8)TIMx)
	{
		case (u8)TIMER2:
				RCC->APB1ENR|=1<<0;
				GPIO_Select(GPIOA,P5,MUX,F);			//TIM2_ETR���ſ�ѡ��PA0��PA5��PA15
				GPIO_AF_Set(GPIOA,5,1);
		
				TIM2->ARR=0xFFFF;
				TIM2->PSC=0;
	
				TIM2->SMCR|=1<<14;
				
				TIM2->CNT=0;
				
				TIM2->CR1|=1<<0;
		case (u8)TIMER3:
				RCC->APB1ENR|=1<<1;
				GPIO_Select(GPIOD,P2,MUX,F);			//TIM3_ETR���ſ�ѡ��PD2
				GPIO_AF_Set(GPIOD,2,2);
		
				TIM3->ARR=0xFFFF;
				TIM3->PSC=0;
				
				TIM3->SMCR|=1<<14;
				
				TIM3->CNT=0;
				
				TIM3->CR1|=1<<0;
		case (u8)TIMER4:
				RCC->APB1ENR|=1<<2;
				GPIO_Select(GPIOE,P0,MUX,F);			//TIM4_ETR���ſ�ѡ��PE0
				GPIO_AF_Set(GPIOE,0,2);
		
				TIM4->ARR=0xFFFF;
				TIM4->PSC=0;
				
				TIM4->SMCR|=1<<14;
				
				TIM4->CNT=0;
				
				TIM4->CR1|=1<<0;
		default:
				break;
	}	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡͨ�ö�ʱ��ETR�ⲿ����ֵ
//  @param      TIMx          ��ʱ������		��TIMER2~TIMER4��                    
//  @return     u16
//  Sample usage:             speed = GenTIMER_SpeedGet(TIMER3);    //��ȡTIM3���ٶ�ֵ
//-------------------------------------------------------------------------------------------------------------------
u16 GenTIMER_SpeedGet(GENERAL_TIMER TIMx)
{
	u16 cnt=0;
	
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
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߼���ʱ��ETR�ⲿ������ʼ��
//  @param      TIMx          ��ʱ������		��TIMER1��TIMER8��                    
//  @return     void
//  Sample usage:             AdvTIMER_CNT_Init(TIMER8);    //TIMER8 ETR�ⲿ������ʼ��
//-------------------------------------------------------------------------------------------------------------------
void AdvTIMER_CNT_Init(ADV_TIMER TIMx)
{
	switch((u8)TIMx)
	{
		case (u8)TIMER1:
				RCC->APB2ENR |= 1<<0;
	
				GPIO_Select(GPIOE,P7,MUX,F);			//TIM1_ETR���ſ�ѡ��PA12��PE7
				GPIO_AF_Set(GPIOE,7,1);
				
				TIM1->ARR=0xFFFF;
				TIM1->PSC=0;
				
		TIM1->SMCR|=1<<14;
				
				TIM1->CNT=0;
							
				TIM1->CR1|=1<<0;
				break;
		case (u8)TIMER8:
				RCC->APB2ENR |= 1<<1;
	
				GPIO_Select(GPIOA,P0,MUX,F);			//TIM8_ETR���ſ�ѡ��PA0
				GPIO_AF_Set(GPIOA,0,3);
				
				TIM8->ARR=0xFFFF;
				TIM8->PSC=0;
				
				TIM8->SMCR|=1<<14;
				
				TIM8->CNT=0;
							
				TIM8->CR1|=1<<0;
				break;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ�߼���ʱ��ETR�ⲿ����ֵ
//  @param      TIMx          ��ʱ������		��TIMER1��TIMER8��                    
//  @return     u16
//  Sample usage:             speed = GenTIMER_SpeedGet(TIMER8);    //��ȡTIM8���ٶ�ֵ
//-------------------------------------------------------------------------------------------------------------------
u16 AdvTIMER_SpeedGet(ADV_TIMER TIMx)
{
	u16 cnt=0;
	
	switch((u8)TIMx)
	{
		case (u8)TIMER1:
				cnt=TIM1->CNT;
				TIM1->CNT=0;
				return cnt;
		case (u8)TIMER8:
				cnt=TIM8->CNT;
				TIM8->CNT=0;
				return cnt;
	}
	return 0;
}














