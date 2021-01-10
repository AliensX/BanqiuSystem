#ifndef _TIMER_H
#define _TIMER_H

#include "headfile.h"

typedef enum
{
			TIMER2=0,
			TIMER3,
			TIMER4,
			TIMER5
}GENERAL_TIMER;  //ͨ�ö�ʱ��

typedef enum
{
			TIMER1=0,
			TIMER8
}ADV_TIMER;  //�߼���ʱ��

typedef enum
{
			CH1,
			CH2,
			CH3,
			CH4
}GENERAL_TIMER_CH;       //ͨ�ö�ʱ��ͨ��



void TIM2_PWM_Init(u16 arr , u16 psc , GENERAL_TIMER_CH ch , u16 duty);
void TIM3_PWM_Init(u16 arr , u16 psc , GENERAL_TIMER_CH ch , u16 duty);
void TIM4_PWM_Init(u16 arr , u16 psc , GENERAL_TIMER_CH ch , u16 duty);
void TIM5_PWM_Init(u16 arr , u16 psc , GENERAL_TIMER_CH ch , u16 duty);
void PWM_SetDuty(GENERAL_TIMER timer , GENERAL_TIMER_CH ch , u16 duty);

void TIMER_Init(u16 arr , u16 psc , TIM_TypeDef* TIMx);

void TIMER_CNT_Init(GENERAL_TIMER TIMx);
u16 GenTIMER_SpeedGet(GENERAL_TIMER TIMx);
void AdvTIMER_CNT_Init(ADV_TIMER TIMx);
u16 AdvTIMER_SpeedGet(ADV_TIMER TIMx);



#endif

