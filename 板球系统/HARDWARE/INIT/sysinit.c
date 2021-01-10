/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,徐氏伟业
 * All rights reserved.
 *
 * 以下所有内容版权均属徐氏伟业所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留徐氏伟业的版权声明。
 *
 * @file       		SYSINIT
 * @company	   		华北理工大学
 * @author     		徐氏伟业
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-01-31
 ********************************************************************************************************************/
#include "headfile.h"
#include "sysinit.h"


void System_Init()
{
	delay_init(168);    					//延时函数初始化：168MHz
	LCD_Init();										//LCD初始化
	LCD_Clear(WHITE);							//LCD清除为白色
  Usart_Init(USART1,115200); 	  //串口1初始化
	TIMER_Init(19999,8399,TIM2);	//开启TIM7定时器中断：周期2s
//	KEY_Init();				  //四按键初始化
}


