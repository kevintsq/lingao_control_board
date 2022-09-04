#ifndef __BATTERYINFOR_H
#define __BATTERYINFOR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"


typedef struct
{	
	__IO uint16_t ADchx;//电池电压ADC值
	__IO uint16_t ADre; //STM32内部参照电压ADC值
	__IO float a; //低通滤波系数
	__IO float Voltage;//电压值 V
	__IO float Current;//电流值 A
	__IO uint8_t Capacity;//剩余电量 %
}Battery_Struct;//电池状态信息结构体参数

void Battery_Init(Battery_Struct *Battery, float a);//电池状态初始化函数
void UpdateBatteryInfor(Battery_Struct *Battery, uint16_t *ADCx_DMA_Buff);//更新电池状态信息
uint8_t GetdBatteryCapacity(float BatteryVoltag, uint8_t BatterySeriesNumber);//计算电池组剩余电量百分比

#ifdef __cplusplus
}
#endif

#endif
