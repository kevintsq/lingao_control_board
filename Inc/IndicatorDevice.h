#ifndef __INDICATORDEVICE_H
#define __INDICATORDEVICE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

typedef struct
{
	__IO uint8_t LockedStatus;//����״̬ 1�������� 0����δ����
	__IO uint16_t PeriodTime;//��˸����
	__IO uint16_t PeriodTimeBuffer;//��������ʱ��
	__IO uint16_t Times;//��˸����
	__IO uint16_t LastTimes;
	__IO uint16_t LastPeriodTime;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_PIN;
}IndicatorDevice_Struct;//AGV����ϵͳ�ṹ�����	 

void IndicatorDevice_Init(IndicatorDevice_Struct *IndicatorDevice, GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN);//��ʾ�豸��ʼ�����ú���
void IndicatorDeviceControl(IndicatorDevice_Struct *IndicatorDevice, uint16_t Times, uint16_t PeriodTime);//��ʾ�豸���ƺ���
void IndicatorDeviceLoop(IndicatorDevice_Struct *IndicatorDevice);//ָʾ�豸ѭ������

#ifdef __cplusplus
}
#endif

#endif
