#ifndef __TCA8418_H
#define __TCA8418_H
#include "sys.h"


//***** TCA8418器件地址定义 *****//
#define  SlaveAddr	   0x34				//从机地址

//***** TCA8418寄存器地址定义 *****//
#define  CFG   				 0x01				//配置寄存器
#define  INT_STAT      0x02				//中断状态寄存器
#define  KEY_LCK_EC    0x03				//按键锁定和事件计数器寄存器
#define  KEY_EVENT_A	 0x04				//按键事件寄存器A
#define  KEY_EVENT_B	 0x05				//按键事件寄存器B
#define  KEY_EVENT_C	 0x06				//按键事件寄存器C
#define  KEY_EVENT_D	 0x07				//按键事件寄存器D
#define  KEY_EVENT_E	 0x08				//按键事件寄存器E
#define  KEY_EVENT_F	 0x09				//按键事件寄存器F
#define  KEY_EVENT_G	 0x0A				//按键事件寄存器G
#define  KEY_EVENT_H	 0x0B				//按键事件寄存器H
#define  KEY_EVENT_I	 0x0C				//按键事件寄存器I
#define  KEY_EVENT_J	 0x0D				//按键事件寄存器J
#define  KP_LCK_TIMER  0x0E				//键盘锁定1锁定2计时器
#define  UNLOCK1 			 0x0F				//解锁按键1
#define  UNLOCK2 			 0x10		  	//解锁按键2
#define  GPIO_INT_STAT1 0x11			//GPIO中断状态1寄存器
#define  GPIO_INT_STAT2 0x12			//GPIO中断状态2寄存器
#define  GPIO_INT_STAT3 0x13			//GPIO中断状态3寄存器
#define  GPIO_DAT_STAT1 0x14			//GPIO数据状态1寄存器（读两次清除）
#define  GPIO_DAT_STAT2 0x15			//GPIO数据状态2寄存器（读两次清除）
#define  GPIO_DAT_STAT3 0x16			//GPIO数据状态3寄存器（读两次清除）
#define  GPIO_DAT_OUT1  0x17			//GPIO数据输出寄存器1
#define  GPIO_DAT_OUT2  0x18			//GPIO数据输出寄存器2
#define  GPIO_DAT_OUT3  0x19			//GPIO数据输出寄存器3
#define  GPIO_INT_EN1   0x1A			//GPIO中断使能寄存器1
#define  GPIO_INT_EN2   0x1B			//GPIO中断使能寄存器2
#define  GPIO_INT_EN3   0x1C			//GPIO中断使能寄存器3
#define  KP_GPIO1				0x1D			//键盘或GPIO选择寄存器1
#define  KP_GPIO2				0x1E			//键盘或GPIO选择寄存器2
#define  KP_GPIO3				0x1F			//键盘或GPIO选择寄存器3
#define  GPI_EM1				0x20			//GPI事件模式1寄存器
#define  GPI_EM2				0x21			//GPI事件模式2寄存器
#define  GPI_EM3				0x22			//GPI事件模式3寄存器
#define  GPIO_DIR1 			0x23			//GPIO方向1
#define  GPIO_DIR2 			0x24			//GPIO方向2
#define  GPIO_DIR3 			0x25			//GPIO方向3
#define  GPIO_INT_LVL1  0x26			//GPIO边沿/电平检测寄存器1
#define  GPIO_INT_LVL2  0x27			//GPIO边沿/电平检测寄存器2
#define  GPIO_INT_LVL3  0x28			//GPIO边沿/电平检测寄存器3
#define  DEBOUNCE_DIS1	0x29			//去抖动禁用寄存器1
#define  DEBOUNCE_DIS2	0x2A			//去抖动禁用寄存器2
#define  DEBOUNCE_DIS3	0x2B			//去抖动禁用寄存器3
#define	 GPIO_PULL1			0x2C			//GPIO上拉禁用寄存器1
#define	 GPIO_PULL2			0x2D			//GPIO上拉禁用寄存器2
#define	 GPIO_PULL3			0x2E			//GPIO上拉禁用寄存器3

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


//矩阵键盘模式位配置
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


#define  TCA_INT  (GPIO_GetLevel(GPIOF,P7))										  	//中断引脚输入电平
#define  CLC_INTSTAT  {IIC_Set_Reg(INT_STAT,0X0F,SlaveAddr);}			//清除中断状态
#define  GET_KEYPAD		(IIC_Read_Reg(KEY_EVENT_A,SlaveAddr))				//获取键值



void TCA8418_init(u8 rows,u16 cols,u8 config);				//TCA8418初始化
u8 TCA8418_GetKey(u8 mode);														//返回按键位置









#endif


