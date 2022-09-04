#ifndef __LOWPASSFILTER_H
#define __LOWPASSFILTER_H

#ifdef __cplusplus
 extern "C" {
#endif
	
#include "main.h"

typedef struct
{
	volatile float a;// 滤波系数 取值范围0~1
	volatile float OutValue;//滤波后的输出值
	volatile float SampleValue;//采样值 
}LPF_Struct;

void LPF_Struct_Init(LPF_Struct *LPF, float a);//低通滤波参数初始化
float LowPassFilter(LPF_Struct *LPF);//低通滤波计算函数

#ifdef __cplusplus
}
#endif

#endif
