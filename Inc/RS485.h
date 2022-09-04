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
}RS485_Struct;//RS485�ṹ�����	 

void RS485_RD_GPIO_Init(RS485_Struct *RS485, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);//RS485оƬRD��������
void RS485_RD(RS485_Struct* RS485, uint8_t PinState);//RS485оƬRD���ŵ�ƽ����


#ifdef __cplusplus
}
#endif

#endif
