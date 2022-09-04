/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：
1、增量式PID参数初始化
2、位置式PID参数初始化
3、增量式PID计算函数
4、位置式PID计算函数
**************************************************************************/
#include "pid.h"

/**************************************************************************
函数功能：增量式PID参数初始化
入口参数：增量式PID参数结构体，比例参数，积分参数，微分参数
返回  值：None
**************************************************************************/
void IncPID_Init(IncPID_Struct *PID, float P, float I, float D)
{
	PID->Proportion = P;//比例常数 Proportional Const 
	PID->Integral  =  I;//积分常数Integral Const 
	PID->Derivative = D;//微分常数 Derivative Const	
	
	PID->Error = 0;//E(k)	
	PID->PrevError = 0;//E(k-1)
	PID->LastError = 0;//E(k-2)
}

/**************************************************************************
函数功能：位置式PID参数初始化
入口参数：位置式PID结构体参数，比例参数，积分参数，微分参数
返回  值：None
**************************************************************************/
void PosPID_Init(PosPID_Struct *PID, float P, float I, float D, float IntegralError_Min, float IntegralError_Max)
{
	PID->Proportion = P;//比例常数 Proportional Const 
	PID->Integral  =  I;//积分常数Integral Const 
	PID->Derivative = D;//微分常数 Derivative Const	
	
	PID->Error = 0;//E(k)	
	PID->PrevError = 0;//E(k-1)
	
	PID->IntegralError = 0;//累积误差值
	PID->IntegralError_Min = IntegralError_Min;//累积误差值限幅最小值
	PID->IntegralError_Max = IntegralError_Max;//累积误差值限幅最大值
}

/**************************************************************************
函数功能：增量式PID计算函数
入口参数：PID结构体参数，测量值，目标值
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
**************************************************************************/
float Incremental_PID(IncPID_Struct *PID, float NextPoint, float SetPoint)
{
  PID->Error = SetPoint - NextPoint;
    
  float Value = PID->Proportion * (PID->Error - PID->PrevError) + PID->Integral * PID->Error+\
  PID->Derivative * (PID->Error-2 * PID->PrevError + PID->LastError);//增量计算
    
  PID->LastError = PID->PrevError;//下一次迭代
  PID->PrevError = PID->Error;
  return Value; 
}

/**************************************************************************
函数功能：位置式PID计算函数
入口参数：PID结构体参数，测量值，目标值
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
float Position_PID(PosPID_Struct *PID, float NextPoint, float SetPoint)
{	
  PID->Error = SetPoint - NextPoint;
	
  PID->IntegralError +=  PID->Error;
	if(PID->IntegralError > PID->IntegralError_Max) PID->IntegralError = PID->IntegralError_Max;//积分限幅，防止累积值一直增大
	else if(PID->IntegralError < PID->IntegralError_Min) PID->IntegralError = PID->IntegralError_Min;
	
  float PositionPid = PID->Proportion * PID->Error + PID->Integral * PID->IntegralError + PID->Derivative * (PID->Error - PID->PrevError);
  
  PID->PrevError = PID->Error;
  return PositionPid; 
}
