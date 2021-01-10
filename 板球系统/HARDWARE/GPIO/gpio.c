/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,徐氏伟业
 * All rights reserved.
 *
 * 以下所有内容版权均属徐氏伟业所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留徐氏伟业的版权声明。
 *
 * @file       		GPIO
 * @company	   		华北理工大学
 * @author     		徐氏伟业
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-01-31
 ********************************************************************************************************************/
#include "headfile.h"
#include "gpio.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO复用功能设置
//  @param      GPIOx         选择GPIO（GPIOA~GPIOE）
//  @param      BITx          引脚编号选择，P0~P15（0~15）
//  @param      AFx           复用表选择，AF0~AF15（0~15）
//  @return     void
//  Sample usage:             GPIO_AF_Set(GPIOC,10,6);     //设置PC10引脚对应复用表的AF6
//-------------------------------------------------------------------------------------------------------------------
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx)
{  
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(u32)AFx<<((BITx&0X07)*4);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO初始化
//  @param      GPIOx         选择GPIO（GPIOA~GPIOE）
//  @param      pin           引脚选择（P0~P15）
//  @param      mode          GPIO模式选择：INPUT（输入），OUTPUT（输出），ANALOG（模拟输入）,MUX（复用模式）
//  @param      level         引脚电平/上下拉设置：H：输出高(上拉输入)，L：输出低(下拉输入)，F：浮空
//  @return     void
//  Sample usage:             GPIO_Select(GPIOB,P7,OUTPUT,H);     //设置PB7引脚为通用输出模式
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Select(GPIO_TypeDef* GPIOx , PIN pin , MODE mode , LEVEL level)
{
  switch( (int)GPIOx )
	{
	  case (int)GPIOA:
			RCC->AHB1ENR|=1<<0;
			break;
		case (int)GPIOB:
			RCC->AHB1ENR|=1<<1;
			break;	
		case (int)GPIOC:
			RCC->AHB1ENR|=1<<2;
			break;
		case (int)GPIOD:
			RCC->AHB1ENR|=1<<3;
			break;
		case (int)GPIOE:
			RCC->AHB1ENR|=1<<4;
			break;
		case (int)GPIOF:
			RCC->AHB1ENR|=1<<5;
		  break;
	};
	switch( (u8)mode )
	{
	  case (u8)INPUT:
			GPIOx->MODER&=~(3<<((u8)pin*2));
			break;
		case (u8)OUTPUT:
			GPIOx->MODER&=~(3<<((u8)pin*2));
			GPIOx->MODER|=1<<((u8)pin*2);
		  GPIOx->OTYPER&=~(1<<(u8)pin);
		  GPIOx->OSPEEDR|=3<<((u8)pin*2);
			break;
		case (u8)ANALOG:
			GPIOx->MODER&=~(3<<((u8)pin*2));
			GPIOx->MODER|=3<<((u8)pin*2);
			break;
		case (u8)MUX:
			GPIOx->MODER&=~(3<<((u8)pin*2));
			GPIOx->MODER|=2<<((u8)pin*2);
			break;
	};
	if( (mode==OUTPUT)&&(level==H) )
		GPIOx->ODR|=1<<(u8)pin;
	if( (mode==OUTPUT)&&(level==L) )
		GPIOx->ODR&=~(1<<(u8)pin);
	if( ((mode==INPUT)||(mode==ANALOG))&&(level==H) )
	{
		GPIOx->PUPDR&=~(3<<(u8)pin*2);
		GPIOx->PUPDR|=1<<(u8)pin*2;
	}
	if( ((mode==INPUT)||(mode==ANALOG))&&(level==L) )
	{
		GPIOx->PUPDR&=~(3<<(u8)pin*2);
		GPIOx->PUPDR|=2<<(u8)pin*2;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO输出电平设置
//  @param      GPIOx         选择GPIO（GPIOA~GPIOE）
//  @param      pin           引脚选择（P0~P15）
//  @param      level         引脚电平设置（H：输出高，L：输出低）
//  @return     void
//  Sample usage:             GPIO_SetLevel(GPIOC,P2,L);    //PC2引脚输出低电平
//-------------------------------------------------------------------------------------------------------------------
void GPIO_SetLevel(GPIO_TypeDef* GPIOx , PIN pin , LEVEL level)
{
  switch( (u8)level )
	{
	  case (u8)H:
			GPIOx->ODR|=1<<(u8)pin;
			break;
		case (u8)L:
			GPIOx->ODR&=~(1<<(u8)pin);
			break;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO输入电平获取
//  @param      GPIOx            	  选择GPIO（GPIOA~GPIOE）
//  @param      pin              	  引脚选择（P0~P15）
//  @return     unsigned char
//  Sample usage:             		  Level=GPIO_GetLevel(GPIOA,P12);	  //获取PA12引脚的输入电平
//-------------------------------------------------------------------------------------------------------------------
unsigned char GPIO_GetLevel(GPIO_TypeDef* GPIOx , PIN pin)
{
	if((GPIOx->IDR)&(1<<(u8)pin))
		return 1;
	else return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO输出电平翻转
//  @param      GPIOx            	  选择GPIO（GPIOA~GPIOE）
//  @param      pin              	  引脚选择（P0~P15）
//  @return     void
//  Sample usage:             		  GPIO_Upturn(GPIOC,P0);    //翻转PC0的电平
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Upturn(GPIO_TypeDef* GPIOx , PIN pin)
{
  u8 status;
	if((GPIOx->ODR)&(1<<(u8)pin))
		status=1;
	else status=0;
	if(status)
		GPIO_SetLevel(GPIOx,pin,L);
	else 
		GPIO_SetLevel(GPIOx,pin,H);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO方向设置（调用前提：该GPIO已初始化）
//  @param      GPIOx         选择GPIO（GPIOA~GPIOE）
//  @param      pin           引脚选择（P0~P15）
//  @param      mode          GPIO模式选择：INPUT（输入），OUTPUT（输出），ANALOG（模拟输入）,MUX（复用模式）
//  @param      level         引脚电平/上下拉设置：H：输出高(上拉输入)，L：输出低(下拉输入)，F：浮空
//  @return     void
//  Sample usage:             GPIO_Dir(GPIOD,P2,INPUT,H);     //将PD2更改为上拉输入
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Dir(GPIO_TypeDef* GPIOx , PIN pin , MODE mode , LEVEL level)
{
	switch( (u8)mode )
	{
	  case (u8)INPUT:
			GPIOx->MODER&=~(3<<((u8)pin*2));
			break;
		case (u8)OUTPUT:
			GPIOx->MODER&=~(3<<((u8)pin*2));
			GPIOx->MODER|=1<<((u8)pin*2);
		  GPIOx->OTYPER&=~(1<<(u8)pin);
		  GPIOx->OSPEEDR|=3<<((u8)pin*2);
			break;
		case (u8)ANALOG:
			GPIOx->MODER&=~(3<<((u8)pin*2));
			GPIOx->MODER|=3<<((u8)pin*2);
			break;
		case (u8)MUX:
			GPIOx->MODER&=~(3<<((u8)pin*2));
			GPIOx->MODER|=2<<((u8)pin*2);
			break;
	};
	if( (mode==OUTPUT)&&(level==H) )
		GPIOx->ODR|=1<<(u8)pin;
	if( (mode==OUTPUT)&&(level==L) )
		GPIOx->ODR&=~(1<<(u8)pin);
	if( ((mode==INPUT)||(mode==ANALOG))&&(level==H) )
	{
		GPIOx->PUPDR&=~(3<<(u8)pin*2);
		GPIOx->PUPDR|=1<<(u8)pin*2;
	}
	if( ((mode==INPUT)||(mode==ANALOG))&&(level==L) )
	{
		GPIOx->PUPDR&=~(3<<(u8)pin*2);
		GPIOx->PUPDR|=2<<(u8)pin*2;
	}
}







