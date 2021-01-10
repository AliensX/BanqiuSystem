/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,����ΰҵ
 * All rights reserved.
 *
 * �����������ݰ�Ȩ��������ΰҵ���У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣������ΰҵ�İ�Ȩ������
 *
 * @file       		SPI
 * @company	   		��������ѧ
 * @author     		����ΰҵ
 * @Software 			MDK 5.24a
 * @Target core		STM32F407VET6
 * @date       		2019-02-04
 ********************************************************************************************************************/
#include "headfile.h"
#include "hard_spi.h"

//--------------------------------------------------------------------------------------------
//																																													//
//  SPI1�� 				 									SPI2�� 				 									SPI3��		              //
//				NSS�� PA4��PA15									NSS�� PB9�� PB12								NSS�� PA4��PA15		//
//				SCLK��PA5��PB3									SCLK��PB10��PB13								SCLK��PB3��PC10		//
//				MISO��PA6��PB4									MISO��PB14��PC2									MISO��PB4��PC11		//
//				MOSI��PA7��PB5                  MOSI��PB15��PC3									MOSI��PB5��PC12		//
//																																													//
//--------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI�����ʼ��
//  @param      SPIx          ѡ��Ӳ��SPI��SPI1~SPI3��
//  @param      mode          ģʽѡ��������Master�����ӻ���Slave��
//  @param      SpeedLevel    SPI�ٶȵȼ���Speed1~Speed8 �ֱ��Ӧ2��n��������ʱ�ӷ�Ƶ���������hard_spi.h�ļ�
//  @param      ClkTypes      ʱ�����ͣ�ClkTypes1~ClkTypes4���������hard_spi.h�ļ�
//  @return     void
//  Sample usage:             Hardware_SPI_Init(SPI2,Master,Speed1,ClkTypes4);     //����SPI2Ϊ�ٶ�1��ʱ������4������
//-------------------------------------------------------------------------------------------------------------------
void Hardware_SPI_Init(SPI_TypeDef* SPIx,SPI_Mode mode,SPI_SpeedLevel SpeedLevel,SPI_ClkTypes ClkTypes)
{
	SPI_DFF dff=SPI_8_Bit;		//����֡��ʽ������/����ѡ��8λ֡��ʽ
	
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

	SPIx->CR1|=(u8)SpeedLevel<<3;		//ͬ��ʱ�Ӳ���������

	if(mode==Master)
	{
			SPIx->CR1|=1<<2;
			SPIx->CR1|=1<<9;		//SSM=1��ʹ����������������ڲ�NSS�ź���SSIλ����
			SPIx->CR1|=1<<8;		//SSI=1������NSSΪ�ߵ�ƽ������ģʽ��NSSΪ�ߵ�ƽ��ѡ�и�����,�ӻ�ģʽ��NSSΪ�͵�ƽѡ�иôӻ���
	}
	else
	{
			SPIx->CR1&=~(1<<2);
			SPIx->CR1&=~(1<<9); //SSM=0����ֹ��������������ڲ�NSS�ź����ⲿNSS���ſ��ƣ�NSS����Ϊ�͵�ƽ��ѡ�иû���
	}

	SPIx->CR1&=~(1<<7);			//֡���͸�ʽ����0ΪMSB�ȷ��ͣ���1ΪLSB�ȷ���
	SPIx->CR1&=~(1<<10);		//ȫ˫��

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

	SPIx->CR2&=~(1<<4);				//Ĭ��SPIΪĦ��������׼��ʽ����ֹ��������SSPЭ�飩
	SPIx->CR1|=1<<6;					//ʹ��SPI

	SPI_RW_Byte(SPIx,0xFF);		//�����䣨0xFF������Ч��
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI����/����һ���ֽ�
//  @param      SPIx          ѡ��Ӳ��SPI��SPI1~SPI3��
//  @param      Txdata        ����������
//  @return     u8
//  Sample usage:             SPI_RW_Byte(SPI2,0xFF);     //SPI2����һ�ֽ�����0xFF
//-------------------------------------------------------------------------------------------------------------------
u8 SPI_RW_Byte(SPI_TypeDef* SPIx,u8 Txdata)
{
	while(!(SPIx->SR&0x02)){;}			//�ȴ�TXE��־λ��1
			SPIx->DR=Txdata;
	while(!(SPIx->SR&0x01)){;}			//�ȴ�RENE��־λ��1
			return SPIx->DR;
}








