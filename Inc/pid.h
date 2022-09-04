#ifndef __PID_H
#define __PID_H
#include "main.h"

typedef struct//����ʽPID�ṹ�����
{
	__IO float Proportion; //�������� Proportional Const
	__IO float Integral; //���ֳ��� Integral Const
	__IO float Derivative; //΢�ֳ��� Derivative Const
	
	__IO float Error;//E(k)	
	__IO float PrevError;//E(k-1)
	__IO float LastError;//E(k-2)
} IncPID_Struct;

typedef struct//λ��ʽPID�ṹ�����
{
	__IO float Proportion; //�������� Proportional Const
	__IO float Integral; //���ֳ��� Integral Const
	__IO float Derivative; //΢�ֳ��� Derivative Const
	
	__IO float Error;//E(k)	
	__IO float PrevError;//E(k-1)
	
	__IO float IntegralError;//�ۻ����ֵ
	__IO float IntegralError_Min;//�ۻ����ֵ�޷���Сֵ
	__IO float IntegralError_Max;//�ۻ����ֵ�޷����ֵ
} PosPID_Struct;

void IncPID_Init(IncPID_Struct *PID, float P, float I, float D);//����ʽPID������ʼ��
void PosPID_Init(PosPID_Struct *PID, float P, float I, float D, float IntegralError_Min, float IntegralError_Max);//λ��ʽPID������ʼ��
float Incremental_PID(IncPID_Struct *PID, float NextPoint, float SetPoint);//����ʽPID���㺯��
float Position_PID(PosPID_Struct *PID, float NextPoint, float SetPoint);//λ��ʽPID���㺯��
#endif
