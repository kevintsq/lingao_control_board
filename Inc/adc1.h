#ifndef __ADC1_H
#define __ADC1_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define ADC1_DMA_BuffLEN 2//ADC1采集数据DMA缓存长度
extern __IO uint16_t ADC1_DMA_Buff[ADC1_DMA_BuffLEN];//ADC1采集数据DMA缓存
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
void MX_ADC1_Init(void);//ADC1初始化

#ifdef __cplusplus
}
#endif

#endif
