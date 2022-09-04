/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1������ʽPID������ʼ��
2��λ��ʽPID������ʼ��
3������ʽPID���㺯��
4��λ��ʽPID���㺯��
**************************************************************************/
#include "pid.h"

/**************************************************************************
�������ܣ�����ʽPID������ʼ��
��ڲ���������ʽPID�����ṹ�壬�������������ֲ�����΢�ֲ���
����  ֵ��None
**************************************************************************/
void IncPID_Init(IncPID_Struct *PID, float P, float I, float D)
{
	PID->Proportion = P;//�������� Proportional Const 
	PID->Integral  =  I;//���ֳ���Integral Const 
	PID->Derivative = D;//΢�ֳ��� Derivative Const	
	
	PID->Error = 0;//E(k)	
	PID->PrevError = 0;//E(k-1)
	PID->LastError = 0;//E(k-2)
}

/**************************************************************************
�������ܣ�λ��ʽPID������ʼ��
��ڲ�����λ��ʽPID�ṹ��������������������ֲ�����΢�ֲ���
����  ֵ��None
**************************************************************************/
void PosPID_Init(PosPID_Struct *PID, float P, float I, float D, float IntegralError_Min, float IntegralError_Max)
{
	PID->Proportion = P;//�������� Proportional Const 
	PID->Integral  =  I;//���ֳ���Integral Const 
	PID->Derivative = D;//΢�ֳ��� Derivative Const	
	
	PID->Error = 0;//E(k)	
	PID->PrevError = 0;//E(k-1)
	
	PID->IntegralError = 0;//�ۻ����ֵ
	PID->IntegralError_Min = IntegralError_Min;//�ۻ����ֵ�޷���Сֵ
	PID->IntegralError_Max = IntegralError_Max;//�ۻ����ֵ�޷����ֵ
}

/**************************************************************************
�������ܣ�����ʽPID���㺯��
��ڲ�����PID�ṹ�����������ֵ��Ŀ��ֵ
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
**************************************************************************/
float Incremental_PID(IncPID_Struct *PID, float NextPoint, float SetPoint)
{
  PID->Error = SetPoint - NextPoint;
    
  float Value = PID->Proportion * (PID->Error - PID->PrevError) + PID->Integral * PID->Error+\
  PID->Derivative * (PID->Error-2 * PID->PrevError + PID->LastError);//��������
    
  PID->LastError = PID->PrevError;//��һ�ε���
  PID->PrevError = PID->Error;
  return Value; 
}

/**************************************************************************
�������ܣ�λ��ʽPID���㺯��
��ڲ�����PID�ṹ�����������ֵ��Ŀ��ֵ
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
float Position_PID(PosPID_Struct *PID, float NextPoint, float SetPoint)
{	
  PID->Error = SetPoint - NextPoint;
	
  PID->IntegralError +=  PID->Error;
	if(PID->IntegralError > PID->IntegralError_Max) PID->IntegralError = PID->IntegralError_Max;//�����޷�����ֹ�ۻ�ֵһֱ����
	else if(PID->IntegralError < PID->IntegralError_Min) PID->IntegralError = PID->IntegralError_Min;
	
  float PositionPid = PID->Proportion * PID->Error + PID->Integral * PID->IntegralError + PID->Derivative * (PID->Error - PID->PrevError);
  
  PID->PrevError = PID->Error;
  return PositionPid; 
}
