#ifndef _HARD_SPI_H
#define _HARD_SPI_H
#include "stm32f4xx.h"

typedef enum
{
	Speed1=0,		//速度等级1：fPCLK/2			SPI1的fPCLK=84M，SPI2与SPI3的fPCLK=42M
	Speed2,		  //速度等级2：fPCLK/4			SPI1的fPCLK=84M，SPI2与SPI3的fPCLK=42M
	Speed3,		  //速度等级3：fPCLK/8			SPI1的fPCLK=84M，SPI2与SPI3的fPCLK=42M
	Speed4,		  //速度等级4：fPCLK/16			SPI1的fPCLK=84M，SPI2与SPI3的fPCLK=42M
	Speed5,		  //速度等级5：fPCLK/32			SPI1的fPCLK=84M，SPI2与SPI3的fPCLK=42M
	Speed6,		  //速度等级6：fPCLK/64			SPI1的fPCLK=84M，SPI2与SPI3的fPCLK=42M
	Speed7,		  //速度等级7：fPCLK/128		SPI1的fPCLK=84M，SPI2与SPI3的fPCLK=42M
	Speed8		  //速度等级8：fPCLK/256		SPI1的fPCLK=84M，SPI2与SPI3的fPCLK=42M
}SPI_SpeedLevel;

typedef enum
{
	Slave=0,				//配置该单片机为从机
	Master=1				//配置该单片机为主机
}SPI_Mode;

typedef enum
{
	SPI_8_Bit=0,		//数据帧格式：发送/接收选择8位帧格式
	SPI_16_Bit			//数据帧格式：发送/接收选择16位帧格式
}SPI_DFF;

typedef enum
{
	ClkTypes1=0,		//时钟类型：CPHA=0,CPOL=0（在第一个时钟边沿开始采样数据；SCLK空闲时为低电平）
	ClkTypes2,			//时钟类型：CPHA=1,CPOL=0（在第二个时钟边沿开始采样数据；SCLK空闲时为低电平）
	ClkTypes3,			//时钟类型：CPHA=0,CPOL=1（在第一个时钟边沿开始采样数据；SCLK空闲时为高电平）
	ClkTypes4				//时钟类型：CPHA=1,CPOL=1（在第二个时钟边沿开始采样数据；SCLK空闲时为高电平）
}SPI_ClkTypes;



void Hardware_SPI_Init(SPI_TypeDef* SPIx,SPI_Mode mode,SPI_SpeedLevel SpeedLevel,SPI_ClkTypes ClkTypes);
u8 SPI_RW_Byte(SPI_TypeDef* SPIx,u8 Txdata);





#endif


