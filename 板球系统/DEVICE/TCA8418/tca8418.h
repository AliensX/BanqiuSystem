#ifndef __TCA8418_H
#define __TCA8418_H
#include "sys.h"


//***** TCA8418������ַ���� *****//
#define  SlaveAddr	   0x34				//�ӻ���ַ

//***** TCA8418�Ĵ�����ַ���� *****//
#define  CFG   				 0x01				//���üĴ���
#define  INT_STAT      0x02				//�ж�״̬�Ĵ���
#define  KEY_LCK_EC    0x03				//�����������¼��������Ĵ���
#define  KEY_EVENT_A	 0x04				//�����¼��Ĵ���A
#define  KEY_EVENT_B	 0x05				//�����¼��Ĵ���B
#define  KEY_EVENT_C	 0x06				//�����¼��Ĵ���C
#define  KEY_EVENT_D	 0x07				//�����¼��Ĵ���D
#define  KEY_EVENT_E	 0x08				//�����¼��Ĵ���E
#define  KEY_EVENT_F	 0x09				//�����¼��Ĵ���F
#define  KEY_EVENT_G	 0x0A				//�����¼��Ĵ���G
#define  KEY_EVENT_H	 0x0B				//�����¼��Ĵ���H
#define  KEY_EVENT_I	 0x0C				//�����¼��Ĵ���I
#define  KEY_EVENT_J	 0x0D				//�����¼��Ĵ���J
#define  KP_LCK_TIMER  0x0E				//��������1����2��ʱ��
#define  UNLOCK1 			 0x0F				//��������1
#define  UNLOCK2 			 0x10		  	//��������2
#define  GPIO_INT_STAT1 0x11			//GPIO�ж�״̬1�Ĵ���
#define  GPIO_INT_STAT2 0x12			//GPIO�ж�״̬2�Ĵ���
#define  GPIO_INT_STAT3 0x13			//GPIO�ж�״̬3�Ĵ���
#define  GPIO_DAT_STAT1 0x14			//GPIO����״̬1�Ĵ����������������
#define  GPIO_DAT_STAT2 0x15			//GPIO����״̬2�Ĵ����������������
#define  GPIO_DAT_STAT3 0x16			//GPIO����״̬3�Ĵ����������������
#define  GPIO_DAT_OUT1  0x17			//GPIO��������Ĵ���1
#define  GPIO_DAT_OUT2  0x18			//GPIO��������Ĵ���2
#define  GPIO_DAT_OUT3  0x19			//GPIO��������Ĵ���3
#define  GPIO_INT_EN1   0x1A			//GPIO�ж�ʹ�ܼĴ���1
#define  GPIO_INT_EN2   0x1B			//GPIO�ж�ʹ�ܼĴ���2
#define  GPIO_INT_EN3   0x1C			//GPIO�ж�ʹ�ܼĴ���3
#define  KP_GPIO1				0x1D			//���̻�GPIOѡ��Ĵ���1
#define  KP_GPIO2				0x1E			//���̻�GPIOѡ��Ĵ���2
#define  KP_GPIO3				0x1F			//���̻�GPIOѡ��Ĵ���3
#define  GPI_EM1				0x20			//GPI�¼�ģʽ1�Ĵ���
#define  GPI_EM2				0x21			//GPI�¼�ģʽ2�Ĵ���
#define  GPI_EM3				0x22			//GPI�¼�ģʽ3�Ĵ���
#define  GPIO_DIR1 			0x23			//GPIO����1
#define  GPIO_DIR2 			0x24			//GPIO����2
#define  GPIO_DIR3 			0x25			//GPIO����3
#define  GPIO_INT_LVL1  0x26			//GPIO����/��ƽ���Ĵ���1
#define  GPIO_INT_LVL2  0x27			//GPIO����/��ƽ���Ĵ���2
#define  GPIO_INT_LVL3  0x28			//GPIO����/��ƽ���Ĵ���3
#define  DEBOUNCE_DIS1	0x29			//ȥ�������üĴ���1
#define  DEBOUNCE_DIS2	0x2A			//ȥ�������üĴ���2
#define  DEBOUNCE_DIS3	0x2B			//ȥ�������üĴ���3
#define	 GPIO_PULL1			0x2C			//GPIO�������üĴ���1
#define	 GPIO_PULL2			0x2D			//GPIO�������üĴ���2
#define	 GPIO_PULL3			0x2E			//GPIO�������üĴ���3

#define CFG_AI 0x80
#define CFG_GPI_E_CFG 0x40
#define CFG_OVR_FLOW_M 0x20
#define CFG_INT_CFG 0x10
#define CFG_OVR_FLOW_IEN 0x08
#define CFG_K_LCK_IEN 0x04
#define CFG_GPI_IEN 0x02
#define CFG_KE_IEN 0x01

#define INT_STAT_CAD_INT 0x10
#define INT_STAT_OVR_FLOW_INT 0x08
#define INT_STAT_K_LCK_INT 0x04
#define INT_STAT_GPI_INT 0x02
#define INT_STAT_K_INT 0x01


//�������ģʽλ����
#define ROW0 0x01
#define ROW1 0x02
#define ROW2 0x04
#define ROW3 0x08
#define ROW4 0x10
#define ROW5 0x20
#define ROW6 0x40
#define ROW7 0x80


#define COL0 0x0001
#define COL1 0x0002
#define COL2 0x0004
#define COL3 0x0008
#define COL4 0x0010
#define COL5 0x0020
#define COL6 0x0040
#define COL7 0x0080
#define COL8 0x0100
#define COL9 0x0200


#define  TCA_INT  (GPIO_GetLevel(GPIOF,P7))										  	//�ж����������ƽ
#define  CLC_INTSTAT  {IIC_Set_Reg(INT_STAT,0X0F,SlaveAddr);}			//����ж�״̬
#define  GET_KEYPAD		(IIC_Read_Reg(KEY_EVENT_A,SlaveAddr))				//��ȡ��ֵ



void TCA8418_init(u8 rows,u16 cols,u8 config);				//TCA8418��ʼ��
u8 TCA8418_GetKey(u8 mode);														//���ذ���λ��









#endif


