#ifndef __RS485_H
#define __RS485_H

#ifdef __cplusplus
 extern "C" {
#endif
	
#include "main.h"

typedef struct
{
	__IO uint16_t Time;//
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}RS485_Struct;//RS485结构体参数	 

void RS485_RD_GPIO_Init(RS485_Struct *RS485, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);//RS485芯片RD引脚配置
void RS485_RD(RS485_Struct* RS485, uint8_t PinState);//RS485芯片RD引脚电平设置


#ifdef __cplusplus
}
#endif

#endif
