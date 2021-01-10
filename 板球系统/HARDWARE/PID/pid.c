#include "headfile.h"

PID_SPEED_X pid_speed_x;		//速度内环X轴
PID_SPEED_Y pid_speed_y;		//速度内环Y轴
PID_POST_X  pid_post_x;			//位置外环X轴
PID_POST_Y  pid_post_y;			//位置外环Y轴


//PID参量初始化
void PID_Init(void)
{
	pid_speed_x.KP = 0;
	pid_speed_x.KI = 0;
	pid_speed_x.KD = 0;
	pid_speed_x.Out = 0;
	pid_speed_x.Targer = 0;
	
	pid_speed_y.KP = 0;
	pid_speed_y.KI = 0;
	pid_speed_y.KD = 0;
	pid_speed_y.Out = 0;
	pid_speed_y.Targer = 0;
	
	pid_post_x.KP = 0;
	pid_post_x.KI = 0;
	pid_post_x.KD = 0;
	pid_post_x.Out = 0;
	pid_post_x.Targer = 0;
	
	pid_post_y.KP = 0;
	pid_post_y.KI = 0;
	pid_post_y.KD = 0;
	pid_post_y.Out = 0;
	pid_post_y.Targer = 0;
}


//X分量速度环
void PID_Speed_Control_X(void)
{
	static short speed_error = 0;					//本次误差
	static short speed_lasterror = 0;			//上次误差
	static short speed_differential = 0;		//误差微分值
	
	speed_error = ((short)pid_post_x.Out - Speed_X);
	speed_differential = speed_error - speed_lasterror;
	
	pid_speed_x.Out = (int)(pid_speed_x.KP*(float)speed_error + pid_speed_x.KD*(float)speed_differential);
	
	if(pid_speed_x.Out>=340)		//增量限幅
		pid_speed_x.Out = 340;		
	if(pid_speed_x.Out<=-340)	//增量限幅
		pid_speed_x.Out = -340;
	
	speed_lasterror = speed_error;
}


//Y分量速度环
void PID_Speed_Control_Y(void)
{
	static short speed_error = 0;					//本次误差
	static short speed_lasterror = 0;			//上次误差
	static short speed_differential = 0;		//误差微分值
	
	speed_error = ((short)pid_post_y.Out - Speed_Y);
	speed_differential = speed_error - speed_lasterror;
	
	pid_speed_y.Out = (int)(pid_speed_y.KP*(float)speed_error + pid_speed_y.KD*(float)speed_differential);
	
	if(pid_speed_y.Out>=340)		//增量限幅
		pid_speed_y.Out = 340;		
	if(pid_speed_y.Out<=-340)		//增量限幅
		pid_speed_y.Out = -340;
	
	speed_lasterror = speed_error;
}


//X分量位置环
void PID_Post_Control_X(void)
{
	static short Post_error = 0;					//本次误差
	static short Post_lasterror = 0;			//上次误差
	static short Post_differential = 0;	//误差微分值
	static short Post_integral = 0;			//误差积分值
	
	Post_error = ((short)pid_post_x.Targer - X_Post);
	Post_differential = Post_error - Post_lasterror;
	
	pid_post_x.Out = (int)(pid_post_x.KP*(float)Post_error + pid_post_x.KD*(float)Post_differential+ pid_post_x.KI*(float)Post_integral);
	
	Post_integral += Post_error;
	Post_lasterror = Post_error;
}


//Y分量位置环
void PID_Post_Control_Y(void)
{
	static short Post_error = 0;					//本次误差
	static short Post_lasterror = 0;			//上次误差
	static short Post_differential = 0;	//误差微分值
	static short Post_integral = 0;			//误差积分值
	
	Post_error = ((short)pid_post_y.Targer - Y_Post);
	Post_differential = Post_error - Post_lasterror;
	
	pid_post_y.Out = (int)(pid_post_y.KP*(float)Post_error + pid_post_y.KD*(float)Post_differential + pid_post_y.KI*(float)Post_integral);
	
	Post_integral += Post_error;
	Post_lasterror = Post_error;
}




