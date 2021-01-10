#include "headfile.h"


//演示模式1
void mode_show1(void)
{
	flag_mode1 = 1;
}


//演示模式2
void mode_show2(void)
{
	flag_mode1 = 0;
	
	pid_post_x.Targer = 116;
	pid_post_y.Targer = 114;
}


//演示模式3
u16 Post_X[15] = {52,52,205,205,116,72,252,239,238,215,174};
u16 Post_Y[15] = {197,44,210,36,114,121,120,68,87,103,114};
void mode_show3(void)
{
	static u8 state = 1;		//状态
	
	flag_mode1 = 0;
	
	//FSM
	switch(state)
	{
		case 1:
			pid_post_x.Targer = Post_X[0];
			pid_post_y.Targer = Post_Y[0];
			if( (X_Post>=Post_X[0]-35 && X_Post<=Post_X[0]+35) && (Y_Post>=Post_Y[0]-35 && Y_Post<=Post_Y[0]+35) )
				state = 2;
			else
				state = 1;	
		break;
			
		case 2:
			pid_post_x.Targer = Post_X[1];
			pid_post_y.Targer = Post_Y[1];
			if( (X_Post>=Post_X[1]-35 && X_Post<=Post_X[1]+35) && (Y_Post>=Post_Y[0]-35 && Y_Post<=Post_Y[0]+35) )
				state = 3;
			else
				state = 2;
		break;
			
		case 3:
			pid_post_x.Targer = Post_X[2];
			pid_post_y.Targer = Post_Y[2];
			if( (X_Post>=Post_X[2]-35 && X_Post<=Post_X[2]+35) && (Y_Post>=Post_Y[2]-35 && Y_Post<=Post_Y[2]+35) )
				state = 4;
			else
				state = 3;
		break;
			
		case 4:
			pid_post_x.Targer = Post_X[3];
			pid_post_y.Targer = Post_Y[3];
			if( (X_Post>=Post_X[3]-35 && X_Post<=Post_X[3]+35) && (Y_Post>=Post_Y[3]-35 && Y_Post<=Post_Y[3]+35) )
				state = 5;
			else
				state = 4;
		break;
			
		case 5:
			pid_post_x.Targer = Post_X[4];
			pid_post_y.Targer = Post_Y[4];
			if( (X_Post>=Post_X[4]-35 && X_Post<=Post_X[4]+35) && (Y_Post>=Post_Y[4]-35 && Y_Post<=Post_Y[4]+35) )
				state = 1;
			else
				state = 5;
		break;	
		
	}
}





