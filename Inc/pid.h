#ifndef __PID_H
#define __PID_H
#include "main.h"

typedef struct//增量式PID结构体参数
{
	__IO float Proportion; //比例常数 Proportional Const
	__IO float Integral; //积分常数 Integral Const
	__IO float Derivative; //微分常数 Derivative Const
	
	__IO float Error;//E(k)	
	__IO float PrevError;//E(k-1)
	__IO float LastError;//E(k-2)
} IncPID_Struct;

typedef struct//位置式PID结构体参数
{
	__IO float Proportion; //比例常数 Proportional Const
	__IO float Integral; //积分常数 Integral Const
	__IO float Derivative; //微分常数 Derivative Const
	
	__IO float Error;//E(k)	
	__IO float PrevError;//E(k-1)
	
	__IO float IntegralError;//累积误差值
	__IO float IntegralError_Min;//累积误差值限幅最小值
	__IO float IntegralError_Max;//累积误差值限幅最大值
} PosPID_Struct;

void IncPID_Init(IncPID_Struct *PID, float P, float I, float D);//增量式PID参数初始化
void PosPID_Init(PosPID_Struct *PID, float P, float I, float D, float IntegralError_Min, float IntegralError_Max);//位置式PID参数初始化
float Incremental_PID(IncPID_Struct *PID, float NextPoint, float SetPoint);//增量式PID计算函数
float Position_PID(PosPID_Struct *PID, float NextPoint, float SetPoint);//位置式PID计算函数
#endif
