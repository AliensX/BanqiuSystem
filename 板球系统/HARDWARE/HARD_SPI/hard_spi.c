/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,徐氏伟业
 * All rights reserved.
 *
 * 以下所有内容版权均属徐氏伟业所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留徐氏伟业的版权声明。
 *
 * @file       		SPI
 * @company	   		华北理工大学
 * @author     		徐氏伟业
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-02-04
 ********************************************************************************************************************/
#include "headfile.h"
#include "hard_spi.h"

//--------------------------------------------------------------------------------------------
//																																													//
//  SPI1： 				 									SPI2： 				 									SPI3：		              //
//				NSS： PA4、PA15									NSS： PB9、 PB12								NSS： PA4、PA15		//
//				SCLK：PA5、PB3									SCLK：PB10、PB13								SCLK：PB3、PC10		//
//				MISO：PA6、PB4									MISO：PB14、PC2									MISO：PB4、PC11		//
//				MOSI：PA7、PB5                  MOSI：PB15、PC3									MOSI：PB5、PC12		//
//																																													//
//--------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI外设初始化
//  @param      SPIx          选择硬件SPI（SPI1~SPI3）
//  @param      mode          模式选择：主机（Master）、从机（Slave）
//  @param      SpeedLevel    SPI速度等级：Speed1~Speed8 分别对应2的n次幂输入时钟分频，含义详见hard_spi.h文件
//  @param      ClkTypes      时钟类型：ClkTypes1~ClkTypes4，含义详见hard_spi.h文件
//  @return     void
//  Sample usage:             Hardware_SPI_Init(SPI2,Master,Speed1,ClkTypes4);     //配置SPI2为速度1、时钟类型4的主机
//-------------------------------------------------------------------------------------------------------------------
void Hardware_SPI_Init(SPI_TypeDef* SPIx,SPI_Mode mode,SPI_SpeedLevel SpeedLevel,SPI_ClkTypes ClkTypes)
{
	SPI_DFF dff=SPI_8_Bit;		//数据帧格式：发送/接收选择8位帧格式
	
	switch((u32)SPIx)
	{
		case (u32)SPI1:
				RCC->APB2ENR|=1<<12;
				GPIO_Select(GPIOA,P5,MUX,F);			//SCLK
				GPIO_Select(GPIOA,P6,MUX,F);			//MISO
				GPIO_Select(GPIOA,P7,MUX,F);			//MOSI
				GPIO_AF_Set(GPIOA,5,5);
				GPIO_AF_Set(GPIOA,6,5);
				GPIO_AF_Set(GPIOA,7,5);
				break;
		case (u32)SPI2:
				RCC->APB1ENR|=1<<14;
				GPIO_Select(GPIOB,P13,MUX,F);			//SCLK
				GPIO_Select(GPIOB,P14,MUX,F);			//MISO
				GPIO_Select(GPIOB,P15,MUX,F);			//MOSI
				GPIO_AF_Set(GPIOB,13,5);
				GPIO_AF_Set(GPIOB,14,5);
				GPIO_AF_Set(GPIOB,15,5);
				break;
		case (u32)SPI3:
				RCC->APB1ENR|=1<<15;
				GPIO_Select(GPIOC,P10,MUX,F);			//SCLK
				GPIO_Select(GPIOC,P11,MUX,F);			//MISO
				GPIO_Select(GPIOC,P12,MUX,F);			//MOSI
				GPIO_AF_Set(GPIOC,10,6);
				GPIO_AF_Set(GPIOC,11,6);
				GPIO_AF_Set(GPIOC,12,6);
				break;
		default:break;
	}

	SPIx->CR1|=(u8)SpeedLevel<<3;		//同步时钟波特率设置

	if(mode==Master)
	{
			SPIx->CR1|=1<<2;
			SPIx->CR1|=1<<9;		//SSM=1，使能软件从器件管理，内部NSS信号由SSI位控制
			SPIx->CR1|=1<<8;		//SSI=1，设置NSS为高电平（主机模式下NSS为高电平则选中该主机,从机模式下NSS为低电平选中该从机）
	}
	else
	{
			SPIx->CR1&=~(1<<2);
			SPIx->CR1&=~(1<<9); //SSM=0，禁止软件从器件管理，内部NSS信号由外部NSS引脚控制（NSS引脚为低电平则选中该机）
	}

	SPIx->CR1&=~(1<<7);			//帧发送格式：置0为MSB先发送，置1为LSB先发送
	SPIx->CR1&=~(1<<10);		//全双工

	if(dff==SPI_16_Bit)
			SPIx->CR1|=1<<11;
	else
			SPIx->CR1&=~(1<<11);

	switch((u8)ClkTypes)
	{
		case (u8)ClkTypes1:
				SPIx->CR1&=~(1<<0);			//CPHA=0
				SPIx->CR1&=~(1<<1);			//CPOL=0
				break;
		case (u8)ClkTypes2:
				SPIx->CR1|=1<<0;				//CPHA=1
				SPIx->CR1&=~(1<<1);			//CPOL=0
				break;
		case (u8)ClkTypes3:
				SPIx->CR1&=~(1<<0);			//CPHA=0
				SPIx->CR1|=1<<1;				//CPOL=1
				break;
		case (u8)ClkTypes4:
				SPIx->CR1|=1<<0;				//CPHA=1
				SPIx->CR1|=1<<1;				//CPOL=1
				break;
		default:break;
	}

	SPIx->CR2&=~(1<<4);				//默认SPI为摩托罗拉标准格式（禁止德州仪器SSP协议）
	SPIx->CR1|=1<<6;					//使能SPI

	SPI_RW_Byte(SPIx,0xFF);		//发起传输（0xFF数据无效）
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI发送/接收一个字节
//  @param      SPIx          选择硬件SPI（SPI1~SPI3）
//  @param      Txdata        待发送数据
//  @return     u8
//  Sample usage:             SPI_RW_Byte(SPI2,0xFF);     //SPI2发送一字节数据0xFF
//-------------------------------------------------------------------------------------------------------------------
u8 SPI_RW_Byte(SPI_TypeDef* SPIx,u8 Txdata)
{
	while(!(SPIx->SR&0x02)){;}			//等待TXE标志位置1
			SPIx->DR=Txdata;
	while(!(SPIx->SR&0x01)){;}			//等待RENE标志位置1
			return SPIx->DR;
}








