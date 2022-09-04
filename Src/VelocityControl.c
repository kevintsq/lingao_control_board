/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�1��4WD�ٶȱջ����ƺ���
**************************************************************************/
#include "VelocityControl.h"
#include "ShareWare.h"

#define PID_H (float)(COUNTS_PER_REV/(float)(60000/(float)VelocityControl_T))//PID����ת��

/**************************************************************************
�������ܣ�4WD�ٶȱջ����ƺ���
��ڲ�����4WD���ת�ٽṹ�����
����  ֵ��None
ע    �⣺�ú�����Ҫ������ִ�У�����4WD����ٶȱջ�
���øú�����4WD����ĵ�ǰת��ֵ�õ����£�4WD���ת������Ŀ��ת��
**************************************************************************/
void VelocityControl_4WD(VelControl_Struct *VelControl)
{
	static float PWM_M1=0;
	static float PWM_M2=0;
	static float PWM_M3=0;
	static float PWM_M4=0;

	Encoder_UpdataValue(&Encoder_M1, TIM3->CNT, -1);//����M1��������ֵ
	Encoder_UpdataValue(&Encoder_M2, TIM2->CNT, -1);//����M2��������ֵ
	Encoder_UpdataValue(&Encoder_M3, TIM4->CNT, 1);//����M3��������ֵ
	Encoder_UpdataValue(&Encoder_M4, TIM5->CNT, -1);//����M4��������ֵ
	
	/*-----------------------------�����ǰת��ֵ����-----------------------------*/
	VelControl->M1_RPM = Encoder_M1.Capture_D_Value * 60000 / (float)VelocityControl_T / (float)COUNTS_PER_REV;//����M1�����ǰת��
	VelControl->M2_RPM = Encoder_M2.Capture_D_Value * 60000 / (float)VelocityControl_T / (float)COUNTS_PER_REV;//����M2�����ǰת��
	VelControl->M3_RPM = Encoder_M3.Capture_D_Value * 60000 / (float)VelocityControl_T / (float)COUNTS_PER_REV;//����M3�����ǰת��
	VelControl->M4_RPM = Encoder_M4.Capture_D_Value * 60000 / (float)VelocityControl_T / (float)COUNTS_PER_REV;//����M4�����ǰת��

	/*-------�ԡ�Ŀ��ת�١�������ֵ-------*/	
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
	
	/*------------------------PID����------------------------*/
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
	
	
	PWM_M1 += Incremental_PID(&PID_M1, Encoder_M1.Capture_D_Value, VelControl->M1_SetRPM * PID_H); //ͨ������ʽPID�����ȡM1���PWM���	
	PWM_M2 += Incremental_PID(&PID_M2, Encoder_M2.Capture_D_Value, VelControl->M2_SetRPM * PID_H); //ͨ������ʽPID�����ȡM2���PWM���
	PWM_M3 += Incremental_PID(&PID_M3, Encoder_M3.Capture_D_Value, VelControl->M3_SetRPM * PID_H); //ͨ������ʽPID�����ȡM3���PWM���
	PWM_M4 += Incremental_PID(&PID_M4, Encoder_M4.Capture_D_Value, VelControl->M4_SetRPM * PID_H); //ͨ������ʽPID�����ȡM4���PWM���
	
	/*------------------------PWM��ֵ------------------------*/
	PWM_M1 = Constrain(PWM_M1, -MotorPWM_Max, MotorPWM_Max);
	PWM_M2 = Constrain(PWM_M2, -MotorPWM_Max, MotorPWM_Max);
	PWM_M3 = Constrain(PWM_M3, -MotorPWM_Max, MotorPWM_Max);
	PWM_M4 = Constrain(PWM_M4, -MotorPWM_Max, MotorPWM_Max);

	/*---------------------���Ƶ��ת��----------------------*/	
	if(PWM_M1 > 0.0f) 
	{
		Motor1_PWM = MotorPWM_Max-PWM_M1;//���Ƶ��1 PWM���
		Motor1_Reverse();//���1��ת	
	}
	else
	{
		Motor1_PWM = MotorPWM_Max+PWM_M1;//���Ƶ��1 PWM���
		Motor1_Forward();//���1����				
	}

	if(PWM_M2 > 0.0f) 
	{
		Motor2_PWM = MotorPWM_Max-PWM_M2;//���Ƶ��2 PWM���
		Motor2_Reverse();//���2��ת		
	}
	else
	{
		Motor2_PWM = MotorPWM_Max+PWM_M2;//���Ƶ��2 PWM���
		Motor2_Forward();//���2����	
	}
	
	if(PWM_M3 > 0.0f) 
	{
		Motor3_PWM = MotorPWM_Max-PWM_M3;//���Ƶ��3 PWM���
		Motor3_Reverse();//���3��ת			
	}
	else
	{
		Motor3_PWM = MotorPWM_Max+PWM_M3;//���Ƶ��3 PWM���
		Motor3_Forward();//���3����	
	}
	
	if(PWM_M4 > 0.0f) 
	{
		Motor4_PWM = MotorPWM_Max-PWM_M4;//���Ƶ��4 PWM���
		Motor4_Reverse();//���4��ת	
	}
	else
	{
		Motor4_PWM = MotorPWM_Max+PWM_M4;//���Ƶ��4 PWM���
		Motor4_Forward();//���4����			
	}
}
