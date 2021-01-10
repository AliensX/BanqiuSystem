#include "tca8418.h"
#include "sim_iic.h"
#include "headfile.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      TCA8418设备初始化
//  @param      rows            	  行参数
//  @param      cols              	列参数
//  @param      config              模式配置
//  @return     void
//  Sample usage:             		  TCA8418_init(ROW0,COL0,CFG_K_LCK_IEN);    //配置TCA8418
//-------------------------------------------------------------------------------------------------------------------
void TCA8418_init(u8 rows,u16 cols,u8 config)
{
	u8 col;
	//I2C初始化
	IIC_Init();
	//设置矩阵列
	col= (u8)(0xff & cols);
	while(IIC_Set_Reg(KP_GPIO2,col,SlaveAddr));
	col= (u8)(0x03 & (cols>>8));
	IIC_Set_Reg(KP_GPIO3,col,SlaveAddr);
	IIC_Set_Reg(KP_GPIO1,rows,SlaveAddr);
	//配置寄存器初始化
	IIC_Set_Reg(CFG,config,SlaveAddr);
	//设备锁关闭
	IIC_Set_Reg(KEY_LCK_EC,0x00,SlaveAddr);
	//中断INT输入引脚初始化
	GPIO_Select(GPIOF,P7,INPUT,H);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取TCA8418键位
//  @param      mode            	  按键模式选择 (1：按下触发    0：松开触发)
//  @return     void
//  Sample usage:             		  key = TCA8418_GetKey(0);    //获取TCA8418键值(松开触发)
//-------------------------------------------------------------------------------------------------------------------
u8 TCA8418_GetKey(u8 mode)
{
	u8 KEY = 0;
	u8 RturnKey = 0;
	if(!TCA_INT)
	{
		if(((IIC_Read_Reg(KEY_LCK_EC,SlaveAddr)>>4)&0x03)==0)
		{
			KEY = GET_KEYPAD;
			CLC_INTSTAT;
			
			if(KEY!=0)
					KEY = KEY;
			else
					KEY = 0;
			
			if(mode==0)
			{
					switch(KEY)
				{
					case 0:
						RturnKey = 0;
					break;
					case 1:
						RturnKey = 1;
					break;
					case 2:
						RturnKey = 2;
					break;
					case 3:
						RturnKey = 3;
					break;
					case 11:
						RturnKey = 4;
					break;
					case 12:
						RturnKey = 5;
					break;
					case 13:
						RturnKey = 6;
					break;
					case 21:
						RturnKey = 7;
					break;
					case 22:
						RturnKey = 8;
					break;
					case 23:
						RturnKey = 9;
					break;
					case 31:
						RturnKey = 11;
					break;
					case 32:
						RturnKey = 10;
					break;
					case 33:
						RturnKey = 12;
					break;
					default:break;
				}
			}
			else if(mode==1)
			{
				switch(KEY)
				{
					case 0:
						RturnKey = 0;
					break;
					case 129:
						RturnKey = 1;
					break;
					case 130:
						RturnKey = 2;
					break;
					case 131:
						RturnKey = 3;
					break;
					case 139:
						RturnKey = 4;
					break;
					case 140:
						RturnKey = 5;
					break;
					case 141:
						RturnKey = 6;
					break;
					case 149:
						RturnKey = 7;
					break;
					case 150:
						RturnKey = 8;
					break;
					case 151:
						RturnKey = 9;
					break;
					case 159:
						RturnKey = 11;
					break;
					case 160:
						RturnKey = 10;
					break;
					case 161:
						RturnKey = 12;
					break;
					default:break;
				}
			}
			
		}
	}
	return RturnKey;
}









