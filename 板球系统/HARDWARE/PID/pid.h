#ifndef _PID_H
#define _PID_H
#include "headfile.h"


typedef struct
{
	float KP;
	float KD;
	float KI;
	int Targer;
	int Out;
}PID_SPEED_X;

typedef struct
{
	float KP;
	float KD;
	float KI;
	int Targer;
	int Out;
}PID_SPEED_Y;

typedef struct
{
	float KP;
	float KD;
	float KI;
	int Targer;
	int Out;
}PID_POST_X;

typedef struct
{
	float KP;
	float KD;
	float KI;
	int Targer;
	int Out;
}PID_POST_Y;


extern PID_SPEED_X pid_speed_x;		//速度内环X轴
extern PID_SPEED_Y pid_speed_y;		//速度内环Y轴
extern PID_POST_X  pid_post_x;			//位置外环X轴
extern PID_POST_Y  pid_post_y;			//位置外环Y轴


void PID_Init(void);
void PID_Speed_Control_X(void);
void PID_Speed_Control_Y(void);
void PID_Post_Control_X(void);
void PID_Post_Control_Y(void);



#endif


