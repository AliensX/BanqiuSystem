/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,徐氏伟业
 * All rights reserved.
 *
 * 以下所有内容版权均属徐氏伟业所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留徐氏伟业的版权声明。
 *
 * @file       		MAIN
 * @company	   		华北理工大学
 * @author     		徐氏伟业
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-01-31
 ********************************************************************************************************************/
#include "headfile.h"
# include <string.h>
////////////////////////////////////   FLASH缓存数组   /////////////////////////////////////////////////////
u32 Flash_Buf[32]=
{
	100,
	200,
	300,
	400,
	500
};			
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////   FLASH地址信息   /////////////////////////////////////////////////////
#define CUR_BYTE sizeof(Flash_Buf)						//缓存数组字节数
#define SIZE CUR_BYTE/4+((CUR_BYTE%4)?1:0)		//缓存数组字数
#define FLASH_SAVE_ADDR 0X0800C004						//FLASH存储起始地址
////////////////////////////////////////////////////////////////////////////////////////////////////////////


u8 key = 0;

int main(void)
{
  System_Init();
	Usart_Init(USART6,9600);
	TCA8418_init(ROW0,COL0,CFG_K_LCK_IEN);
	PID_Init();
	TIM4_PWM_Init(39999,41,CH3,Y_Zhong);			//Y
	TIM4_PWM_Init(39999,41,CH4,X_Zhong);			//X
	pid_post_x.Targer = 116;
	pid_post_y.Targer = 114;
	while(1)
	{
		key = TCA8418_GetKey(0);
		if(key!=0)
			LCD_ShowNum(80,110,key,3,16);
		
		LCD_ShowNum(50,50,X,4,16);
		LCD_ShowNum(100,50,Y,4,16);
		
		LCD_ShowNum(50,70,abs(Speed_X),4,16);
		LCD_ShowNum(100,70,abs(Speed_Y),4,16);
		
		LCD_ShowNum(50,90,abs(pid_speed_x.Out),4,16);
	}
}







