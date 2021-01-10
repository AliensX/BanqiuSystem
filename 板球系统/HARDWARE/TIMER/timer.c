/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,徐氏伟业
 * All rights reserved.
 *
 * 以下所有内容版权均属徐氏伟业所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留徐氏伟业的版权声明。
 *
 * @file       		TIMER
 * @company	   		华北理工大学
 * @author     		徐氏伟业
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-01-31
 ********************************************************************************************************************/
#include "headfile.h"
#include "timer.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TIMER定时器中断初始化
//  @param      arr           预装载值
//  @param      psc           预分频值
//  @param      TIMx          定时器【TIM2、TIM3、TIM4、TIM5、TIM7】
//  @return     void
//  Sample usage:             TIMER_Init(499,8399,TIM7);    //TIM7配置为5ms定时器中断
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
//  @brief      TIMER2 PWM初始化
//  @param      arr           预装载值
//  @param      psc           预分频值
//  @param      ch            PWM输出通道选择 【CH1~CH4】
//  @param      duty          初始占空比（ duty≤(arr+1) ）
//  @return     void
//  Sample usage:             TIM2_PWM_Init(8399,0,CH4,2520);    //TIMER2 PWM通道4输出30%占空比，频率为10KHz的矩形波
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
//  @brief      TIMER3 PWM初始化
//  @param      arr           预装载值
//  @param      psc           预分频值
//  @param      ch            PWM输出通道选择 【CH1~CH4】
//  @param      duty          初始占空比（ duty≤(arr+1) ）
//  @return     void
//  Sample usage:             TIM3_PWM_Init(8399,0,CH4,2520);    //TIMER3 PWM通道4输出30%占空比，频率为10KHz的矩形波
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
//  @brief      TIMER4 PWM初始化
//  @param      arr           预装载值
//  @param      psc           预分频值
//  @param      ch            PWM输出通道选择 【CH1~CH4】
//  @param      duty          初始占空比（ duty≤(arr+1) ）
//  @return     void
//  Sample usage:             TIM4_PWM_Init(8399,0,CH4,2520);    //TIMER4 PWM通道4输出30%占空比，频率为10KHz的矩形波
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
//  @brief      TIMER5 PWM初始化
//  @param      arr           预装载值
//  @param      psc           预分频值
//  @param      ch            PWM输出通道选择 【CH1~CH4】
//  @param      duty          初始占空比（ duty≤(arr+1) ）
//  @return     void
//  Sample usage:             TIM5_PWM_Init(8399,0,CH4,2520);    //TIMER5 PWM通道4输出30%占空比，频率为10KHz的矩形波
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
//  @brief      PWM占空比设定
//  @param      timer         定时器名称       【TIMER2~TIMER5】                    
//  @param      ch            PWM输出通道选择  【CH1~CH4】
//  @param      duty          初始占空比（ duty≤(arr+1) ）
//  @return     void
//  Sample usage:             PWM_SetDuty(TIMER4,CH4,2520);    //TIMER4 PWM通道4输出30%占空比的矩形波
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
//  @brief      通用定时器ETR外部计数初始化
//  @param      TIMx          定时器名称		【TIMER2~TIMER4】                    
//  @return     void
//  Sample usage:             TIMER_CNT_Init(TIMER3);    //TIMER3 ETR外部计数初始化
//-------------------------------------------------------------------------------------------------------------------
void TIMER_CNT_Init(GENERAL_TIMER TIMx)
{
	switch((u8)TIMx)
	{
		case (u8)TIMER2:
				RCC->APB1ENR|=1<<0;
				GPIO_Select(GPIOA,P5,MUX,F);			//TIM2_ETR引脚可选：PA0、PA5、PA15
				GPIO_AF_Set(GPIOA,5,1);
		
				TIM2->ARR=0xFFFF;
				TIM2->PSC=0;
	
				TIM2->SMCR|=1<<14;
				
				TIM2->CNT=0;
				
				TIM2->CR1|=1<<0;
		case (u8)TIMER3:
				RCC->APB1ENR|=1<<1;
				GPIO_Select(GPIOD,P2,MUX,F);			//TIM3_ETR引脚可选：PD2
				GPIO_AF_Set(GPIOD,2,2);
		
				TIM3->ARR=0xFFFF;
				TIM3->PSC=0;
				
				TIM3->SMCR|=1<<14;
				
				TIM3->CNT=0;
				
				TIM3->CR1|=1<<0;
		case (u8)TIMER4:
				RCC->APB1ENR|=1<<2;
				GPIO_Select(GPIOE,P0,MUX,F);			//TIM4_ETR引脚可选：PE0
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
//  @brief      获取通用定时器ETR外部计数值
//  @param      TIMx          定时器名称		【TIMER2~TIMER4】                    
//  @return     u16
//  Sample usage:             speed = GenTIMER_SpeedGet(TIMER3);    //获取TIM3的速度值
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
//  @brief      高级定时器ETR外部计数初始化
//  @param      TIMx          定时器名称		【TIMER1、TIMER8】                    
//  @return     void
//  Sample usage:             AdvTIMER_CNT_Init(TIMER8);    //TIMER8 ETR外部计数初始化
//-------------------------------------------------------------------------------------------------------------------
void AdvTIMER_CNT_Init(ADV_TIMER TIMx)
{
	switch((u8)TIMx)
	{
		case (u8)TIMER1:
				RCC->APB2ENR |= 1<<0;
	
				GPIO_Select(GPIOE,P7,MUX,F);			//TIM1_ETR引脚可选：PA12、PE7
				GPIO_AF_Set(GPIOE,7,1);
				
				TIM1->ARR=0xFFFF;
				TIM1->PSC=0;
				
		TIM1->SMCR|=1<<14;
				
				TIM1->CNT=0;
							
				TIM1->CR1|=1<<0;
				break;
		case (u8)TIMER8:
				RCC->APB2ENR |= 1<<1;
	
				GPIO_Select(GPIOA,P0,MUX,F);			//TIM8_ETR引脚可选：PA0
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
//  @brief      获取高级定时器ETR外部计数值
//  @param      TIMx          定时器名称		【TIMER1、TIMER8】                    
//  @return     u16
//  Sample usage:             speed = GenTIMER_SpeedGet(TIMER8);    //获取TIM8的速度值
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














