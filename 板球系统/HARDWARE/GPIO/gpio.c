/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,����ΰҵ
 * All rights reserved.
 *
 * �����������ݰ�Ȩ��������ΰҵ���У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣������ΰҵ�İ�Ȩ������
 *
 * @file       		GPIO
 * @company	   		��������ѧ
 * @author     		����ΰҵ
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-01-31
 ********************************************************************************************************************/
#include "headfile.h"
#include "gpio.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO���ù�������
//  @param      GPIOx         ѡ��GPIO��GPIOA~GPIOE��
//  @param      BITx          ���ű��ѡ��P0~P15��0~15��
//  @param      AFx           ���ñ�ѡ��AF0~AF15��0~15��
//  @return     void
//  Sample usage:             GPIO_AF_Set(GPIOC,10,6);     //����PC10���Ŷ�Ӧ���ñ��AF6
//-------------------------------------------------------------------------------------------------------------------
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx)
{  
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(u32)AFx<<((BITx&0X07)*4);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO��ʼ��
//  @param      GPIOx         ѡ��GPIO��GPIOA~GPIOE��
//  @param      pin           ����ѡ��P0~P15��
//  @param      mode          GPIOģʽѡ��INPUT�����룩��OUTPUT���������ANALOG��ģ�����룩,MUX������ģʽ��
//  @param      level         ���ŵ�ƽ/���������ã�H�������(��������)��L�������(��������)��F������
//  @return     void
//  Sample usage:             GPIO_Select(GPIOB,P7,OUTPUT,H);     //����PB7����Ϊͨ�����ģʽ
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
//  @brief      GPIO�����ƽ����
//  @param      GPIOx         ѡ��GPIO��GPIOA~GPIOE��
//  @param      pin           ����ѡ��P0~P15��
//  @param      level         ���ŵ�ƽ���ã�H������ߣ�L������ͣ�
//  @return     void
//  Sample usage:             GPIO_SetLevel(GPIOC,P2,L);    //PC2��������͵�ƽ
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
//  @brief      GPIO�����ƽ��ȡ
//  @param      GPIOx            	  ѡ��GPIO��GPIOA~GPIOE��
//  @param      pin              	  ����ѡ��P0~P15��
//  @return     unsigned char
//  Sample usage:             		  Level=GPIO_GetLevel(GPIOA,P12);	  //��ȡPA12���ŵ������ƽ
//-------------------------------------------------------------------------------------------------------------------
unsigned char GPIO_GetLevel(GPIO_TypeDef* GPIOx , PIN pin)
{
	if((GPIOx->IDR)&(1<<(u8)pin))
		return 1;
	else return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO�����ƽ��ת
//  @param      GPIOx            	  ѡ��GPIO��GPIOA~GPIOE��
//  @param      pin              	  ����ѡ��P0~P15��
//  @return     void
//  Sample usage:             		  GPIO_Upturn(GPIOC,P0);    //��תPC0�ĵ�ƽ
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
//  @brief      GPIO�������ã�����ǰ�᣺��GPIO�ѳ�ʼ����
//  @param      GPIOx         ѡ��GPIO��GPIOA~GPIOE��
//  @param      pin           ����ѡ��P0~P15��
//  @param      mode          GPIOģʽѡ��INPUT�����룩��OUTPUT���������ANALOG��ģ�����룩,MUX������ģʽ��
//  @param      level         ���ŵ�ƽ/���������ã�H�������(��������)��L�������(��������)��F������
//  @return     void
//  Sample usage:             GPIO_Dir(GPIOD,P2,INPUT,H);     //��PD2����Ϊ��������
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







