#ifndef __ENCODER_H
#define __ENCODER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

typedef struct
{	
	__IO int32_t CaptureCount;	//�������������ֵ
	__IO int16_t CaptureCount_Last;//������һ�ε�TIMx->CNT������ֵ
	__IO int16_t Capture_D_Value;//������ǰ��2�β�������Ĳ�ֵ
}Encoder_Struct;//����������ṹ�����

void Encoder_Struct_Init(Encoder_Struct *Encoder);//��ʼ���������ṹ�����
void Encoder_UpdataValue(Encoder_Struct *Encoder, int16_t CaptureCount, int8_t Signed);	

#ifdef __cplusplus
}
#endif

#endif
