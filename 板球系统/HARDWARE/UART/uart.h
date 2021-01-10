#ifndef _UART_H
#define _UART_H

#include "headfile.h"


#define  USART_RXIT_EN  1			//是否开启串口接收中断(RXNE):1开启，0关闭
#define  PCLK1  42000000			//APB1总线时钟（42MHz）
#define  PCLK2  84000000			//APB2总线时钟（84MHz）

#define TITLE1 0xAA        //解析OpenMV包
#define TITLE2 0xAE

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern int theta_err,rho_err;

void Usart_Init(USART_TypeDef* USARTx,u32 bound);
void Usart_Send(USART_TypeDef* USARTx,u8 data);
void Optical_Flow_Receive_Prepare(u8 data);
void Data_Processing(u8 *data_buf,u8 num);


#endif


