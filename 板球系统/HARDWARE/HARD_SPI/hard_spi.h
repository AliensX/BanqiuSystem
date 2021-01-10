#ifndef _HARD_SPI_H
#define _HARD_SPI_H
#include "stm32f4xx.h"

typedef enum
{
	Speed1=0,		//�ٶȵȼ�1��fPCLK/2			SPI1��fPCLK=84M��SPI2��SPI3��fPCLK=42M
	Speed2,		  //�ٶȵȼ�2��fPCLK/4			SPI1��fPCLK=84M��SPI2��SPI3��fPCLK=42M
	Speed3,		  //�ٶȵȼ�3��fPCLK/8			SPI1��fPCLK=84M��SPI2��SPI3��fPCLK=42M
	Speed4,		  //�ٶȵȼ�4��fPCLK/16			SPI1��fPCLK=84M��SPI2��SPI3��fPCLK=42M
	Speed5,		  //�ٶȵȼ�5��fPCLK/32			SPI1��fPCLK=84M��SPI2��SPI3��fPCLK=42M
	Speed6,		  //�ٶȵȼ�6��fPCLK/64			SPI1��fPCLK=84M��SPI2��SPI3��fPCLK=42M
	Speed7,		  //�ٶȵȼ�7��fPCLK/128		SPI1��fPCLK=84M��SPI2��SPI3��fPCLK=42M
	Speed8		  //�ٶȵȼ�8��fPCLK/256		SPI1��fPCLK=84M��SPI2��SPI3��fPCLK=42M
}SPI_SpeedLevel;

typedef enum
{
	Slave=0,				//���øõ�Ƭ��Ϊ�ӻ�
	Master=1				//���øõ�Ƭ��Ϊ����
}SPI_Mode;

typedef enum
{
	SPI_8_Bit=0,		//����֡��ʽ������/����ѡ��8λ֡��ʽ
	SPI_16_Bit			//����֡��ʽ������/����ѡ��16λ֡��ʽ
}SPI_DFF;

typedef enum
{
	ClkTypes1=0,		//ʱ�����ͣ�CPHA=0,CPOL=0���ڵ�һ��ʱ�ӱ��ؿ�ʼ�������ݣ�SCLK����ʱΪ�͵�ƽ��
	ClkTypes2,			//ʱ�����ͣ�CPHA=1,CPOL=0���ڵڶ���ʱ�ӱ��ؿ�ʼ�������ݣ�SCLK����ʱΪ�͵�ƽ��
	ClkTypes3,			//ʱ�����ͣ�CPHA=0,CPOL=1���ڵ�һ��ʱ�ӱ��ؿ�ʼ�������ݣ�SCLK����ʱΪ�ߵ�ƽ��
	ClkTypes4				//ʱ�����ͣ�CPHA=1,CPOL=1���ڵڶ���ʱ�ӱ��ؿ�ʼ�������ݣ�SCLK����ʱΪ�ߵ�ƽ��
}SPI_ClkTypes;



void Hardware_SPI_Init(SPI_TypeDef* SPIx,SPI_Mode mode,SPI_SpeedLevel SpeedLevel,SPI_ClkTypes ClkTypes);
u8 SPI_RW_Byte(SPI_TypeDef* SPIx,u8 Txdata);





#endif


