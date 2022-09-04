#ifndef __LOWPASSFILTER_H
#define __LOWPASSFILTER_H

#ifdef __cplusplus
 extern "C" {
#endif
	
#include "main.h"

typedef struct
{
	volatile float a;// �˲�ϵ�� ȡֵ��Χ0~1
	volatile float OutValue;//�˲�������ֵ
	volatile float SampleValue;//����ֵ 
}LPF_Struct;

void LPF_Struct_Init(LPF_Struct *LPF, float a);//��ͨ�˲�������ʼ��
float LowPassFilter(LPF_Struct *LPF);//��ͨ�˲����㺯��

#ifdef __cplusplus
}
#endif

#endif
