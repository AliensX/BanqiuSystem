#ifndef GPIO_H
#define GPIO_H
#include "headfile.h"

#define setbit(x,y)  x|=(1<<y)   //ָ��ĳһλ����1
#define clrbit(x,y)  x&=~(1<<y)  //ָ��ĳһλ����0


typedef enum
{
			INPUT=0,  //����ģʽ
			OUTPUT,   //ͨ�����ģʽ
			ANALOG,   //ģ������ģʽ
			MUX       //����ģʽ
}MODE; //IO��ģʽ����

typedef enum
{
			P0=0,
			P1,
			P2,
			P3,
			P4,
			P5,
			P6,
			P7,
			P8,
			P9,
			P10,
			P11,
			P12,
			P13,
			P14,
			P15
}PIN;  //IO������

typedef enum
{
			L=0,
			H=1,
			F=2
}LEVEL;  //�����ƽ

/* GPIOģʽѡ���� */
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx);
void GPIO_Select(GPIO_TypeDef* GPIOx , PIN pin , MODE mode , LEVEL level);
void GPIO_SetLevel(GPIO_TypeDef* GPIOx , PIN pin , LEVEL level);
unsigned char GPIO_GetLevel(GPIO_TypeDef* GPIOx , PIN pin);
void GPIO_Upturn(GPIO_TypeDef* GPIOx , PIN pin);
void GPIO_Dir(GPIO_TypeDef* GPIOx , PIN pin , MODE mode , LEVEL level);



#endif
