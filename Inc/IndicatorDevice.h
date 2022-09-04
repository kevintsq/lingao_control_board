#ifndef __INDICATORDEVICE_H
#define __INDICATORDEVICE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

typedef struct
{
	__IO uint8_t LockedStatus;//上锁状态 1代表上锁 0代表未上锁
	__IO uint16_t PeriodTime;//闪烁周期
	__IO uint16_t PeriodTimeBuffer;//缓存亮灯时间
	__IO uint16_t Times;//闪烁次数
	__IO uint16_t LastTimes;
	__IO uint16_t LastPeriodTime;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_PIN;
}IndicatorDevice_Struct;//AGV调度系统结构体参数	 

void IndicatorDevice_Init(IndicatorDevice_Struct *IndicatorDevice, GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN);//提示设备初始化配置函数
void IndicatorDeviceControl(IndicatorDevice_Struct *IndicatorDevice, uint16_t Times, uint16_t PeriodTime);//提示设备控制函数
void IndicatorDeviceLoop(IndicatorDevice_Struct *IndicatorDevice);//指示设备循环函数

#ifdef __cplusplus
}
#endif

#endif
