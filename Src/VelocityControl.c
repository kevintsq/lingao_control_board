/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：1、4WD速度闭环控制函数
**************************************************************************/
#include "VelocityControl.h"
#include "ShareWare.h"

#define PID_H (float)(COUNTS_PER_REV/(float)(60000/(float)VelocityControl_T))//PID参数转化

/**************************************************************************
函数功能：4WD速度闭环控制函数
入口参数：4WD电机转速结构体参数
返回  值：None
注    意：该函数需要周期性执行，控制4WD电机速度闭环
调用该函数后，4WD电机的当前转速值得到更新，4WD电机转速趋向目标转速
**************************************************************************/
void VelocityControl_4WD(VelControl_Struct *VelControl)
{
	static float PWM_M1=0;
	static float PWM_M2=0;
	static float PWM_M3=0;
	static float PWM_M4=0;

	Encoder_UpdataValue(&Encoder_M1, TIM3->CNT, -1);//更新M1编码器数值
	Encoder_UpdataValue(&Encoder_M2, TIM2->CNT, -1);//更新M2编码器数值
	Encoder_UpdataValue(&Encoder_M3, TIM4->CNT, 1);//更新M3编码器数值
	Encoder_UpdataValue(&Encoder_M4, TIM5->CNT, -1);//更新M4编码器数值
	
	/*-----------------------------电机当前转速值更新-----------------------------*/
	VelControl->M1_RPM = Encoder_M1.Capture_D_Value * 60000 / (float)VelocityControl_T / (float)COUNTS_PER_REV;//更新M1电机当前转速
	VelControl->M2_RPM = Encoder_M2.Capture_D_Value * 60000 / (float)VelocityControl_T / (float)COUNTS_PER_REV;//更新M2电机当前转速
	VelControl->M3_RPM = Encoder_M3.Capture_D_Value * 60000 / (float)VelocityControl_T / (float)COUNTS_PER_REV;//更新M3电机当前转速
	VelControl->M4_RPM = Encoder_M4.Capture_D_Value * 60000 / (float)VelocityControl_T / (float)COUNTS_PER_REV;//更新M4电机当前转速

	/*-------对“目标转速“进行限值-------*/	
	VelControl->M1_SetRPM = Constrain(VelControl->M1_SetRPM, -RPM_MAX, RPM_MAX);
	VelControl->M2_SetRPM = Constrain(VelControl->M2_SetRPM, -RPM_MAX, RPM_MAX);
	VelControl->M3_SetRPM = Constrain(VelControl->M3_SetRPM, -RPM_MAX, RPM_MAX);
	VelControl->M4_SetRPM = Constrain(VelControl->M4_SetRPM, -RPM_MAX, RPM_MAX);
	
	if( (fabs(VelControl->M1_SetRPM) < 0.005f) && (fabs(VelControl->M2_SetRPM) < 0.005f) && (fabs(VelControl->M3_SetRPM) < 0.005f) && (fabs(VelControl->M4_SetRPM) < 0.005f) )
	{
		PWM_M1 = PWM_M2 = PWM_M3 = PWM_M4 = 0;
		Motor1_PWM = Motor2_PWM = Motor3_PWM = Motor4_PWM = MotorPWM_Max;
		return;
	}
	
	/*------------------------PID运算------------------------*/
	if(fabs((VelControl->M1_SetRPM * PID_H)) > 20)
	{		
		PID_M1.Proportion = -0.587;
		PID_M1.Integral = -0.141337;
		PID_M1.Derivative = -1.0688;
	}
	else
	{
		PID_M1.Proportion = -3.66852;
		PID_M1.Integral = -3.68106;
		PID_M1.Derivative = -3.16713;
	}
	
	if(fabs((VelControl->M2_SetRPM * PID_H)) > 20)
	{
		PID_M2.Proportion = -0.587;
		PID_M2.Integral = -0.141337;
		PID_M2.Derivative = -1.0688;
	}
	else
	{
		PID_M2.Proportion = -3.66852;
		PID_M2.Integral = -3.68106;
		PID_M2.Derivative = -3.16713;
	}
	
	if(fabs((VelControl->M3_SetRPM * PID_H)) > 20)
	{
		PID_M3.Proportion = -0.587;
		PID_M3.Integral = -0.141337;
		PID_M3.Derivative = -1.0688;
	}
	else
	{
		PID_M3.Proportion = -3.66852;
		PID_M3.Integral = -3.68106;
		PID_M3.Derivative = -3.16713;
	}
	
	if(fabs((VelControl->M4_SetRPM * PID_H)) > 20)
	{
		PID_M4.Proportion = -0.587;
		PID_M4.Integral = -0.141337;
		PID_M4.Derivative = -1.0688;
	}
	else
	{
		PID_M4.Proportion = -3.66852;
		PID_M4.Integral = -3.68106;
		PID_M4.Derivative = -3.16713;
	}
	
	
	PWM_M1 += Incremental_PID(&PID_M1, Encoder_M1.Capture_D_Value, VelControl->M1_SetRPM * PID_H); //通过增量式PID计算获取M1电机PWM输出	
	PWM_M2 += Incremental_PID(&PID_M2, Encoder_M2.Capture_D_Value, VelControl->M2_SetRPM * PID_H); //通过增量式PID计算获取M2电机PWM输出
	PWM_M3 += Incremental_PID(&PID_M3, Encoder_M3.Capture_D_Value, VelControl->M3_SetRPM * PID_H); //通过增量式PID计算获取M3电机PWM输出
	PWM_M4 += Incremental_PID(&PID_M4, Encoder_M4.Capture_D_Value, VelControl->M4_SetRPM * PID_H); //通过增量式PID计算获取M4电机PWM输出
	
	/*------------------------PWM限值------------------------*/
	PWM_M1 = Constrain(PWM_M1, -MotorPWM_Max, MotorPWM_Max);
	PWM_M2 = Constrain(PWM_M2, -MotorPWM_Max, MotorPWM_Max);
	PWM_M3 = Constrain(PWM_M3, -MotorPWM_Max, MotorPWM_Max);
	PWM_M4 = Constrain(PWM_M4, -MotorPWM_Max, MotorPWM_Max);

	/*---------------------控制电机转动----------------------*/	
	if(PWM_M1 > 0.0f) 
	{
		Motor1_PWM = MotorPWM_Max-PWM_M1;//控制电机1 PWM输出
		Motor1_Reverse();//电机1反转	
	}
	else
	{
		Motor1_PWM = MotorPWM_Max+PWM_M1;//控制电机1 PWM输出
		Motor1_Forward();//电机1正传				
	}

	if(PWM_M2 > 0.0f) 
	{
		Motor2_PWM = MotorPWM_Max-PWM_M2;//控制电机2 PWM输出
		Motor2_Reverse();//电机2反转		
	}
	else
	{
		Motor2_PWM = MotorPWM_Max+PWM_M2;//控制电机2 PWM输出
		Motor2_Forward();//电机2正传	
	}
	
	if(PWM_M3 > 0.0f) 
	{
		Motor3_PWM = MotorPWM_Max-PWM_M3;//控制电机3 PWM输出
		Motor3_Reverse();//电机3反转			
	}
	else
	{
		Motor3_PWM = MotorPWM_Max+PWM_M3;//控制电机3 PWM输出
		Motor3_Forward();//电机3正传	
	}
	
	if(PWM_M4 > 0.0f) 
	{
		Motor4_PWM = MotorPWM_Max-PWM_M4;//控制电机4 PWM输出
		Motor4_Reverse();//电机4反转	
	}
	else
	{
		Motor4_PWM = MotorPWM_Max+PWM_M4;//控制电机4 PWM输出
		Motor4_Forward();//电机4正传			
	}
}
