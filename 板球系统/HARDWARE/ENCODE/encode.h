#ifndef _ENCODE_H
#define _ENCODE_H

#include "headfile.h"
#include "timer.h"


void Encode_AdvTIMER_Init(ADV_TIMER TIMx);
int Encode_AdvTIMER_SpeedGet(ADV_TIMER TIMx);
void Encode_GenTIMER_Init(GENERAL_TIMER TIMx);
int Encode_GenTIMER_SpeedGet(GENERAL_TIMER TIMx);




#endif



