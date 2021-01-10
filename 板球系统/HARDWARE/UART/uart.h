#ifndef _UART_H
#define _UART_H

#include "headfile.h"


#define  USART_RXIT_EN  1			//�Ƿ������ڽ����ж�(RXNE):1������0�ر�
#define  PCLK1  42000000			//APB1����ʱ�ӣ�42MHz��
#define  PCLK2  84000000			//APB2����ʱ�ӣ�84MHz��

#define TITLE1 0xAA        //����OpenMV��
#define TITLE2 0xAE

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern int theta_err,rho_err;

void Usart_Init(USART_TypeDef* USARTx,u32 bound);
void Usart_Send(USART_TypeDef* USARTx,u8 data);
void Optical_Flow_Receive_Prepare(u8 data);
void Data_Processing(u8 *data_buf,u8 num);


#endif


