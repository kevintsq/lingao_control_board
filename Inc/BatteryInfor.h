#ifndef __BATTERYINFOR_H
#define __BATTERYINFOR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"


typedef struct
{	
	__IO uint16_t ADchx;//��ص�ѹADCֵ
	__IO uint16_t ADre; //STM32�ڲ����յ�ѹADCֵ
	__IO float a; //��ͨ�˲�ϵ��
	__IO float Voltage;//��ѹֵ V
	__IO float Current;//����ֵ A
	__IO uint8_t Capacity;//ʣ����� %
}Battery_Struct;//���״̬��Ϣ�ṹ�����

void Battery_Init(Battery_Struct *Battery, float a);//���״̬��ʼ������
void UpdateBatteryInfor(Battery_Struct *Battery, uint16_t *ADCx_DMA_Buff);//���µ��״̬��Ϣ
uint8_t GetdBatteryCapacity(float BatteryVoltag, uint8_t BatterySeriesNumber);//��������ʣ������ٷֱ�

#ifdef __cplusplus
}
#endif

#endif
