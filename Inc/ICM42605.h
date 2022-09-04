#ifndef __ICM42605_H
#define __ICM42605_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

typedef struct
{		
	__IO float Acc_X;//���ٶ�ֵ g
	__IO float Acc_Y;//���ٶ�ֵ g
	__IO float Acc_Z;//���ٶ�ֵ g
	__IO float Gyro_X;//���ٶ�ֵ rad/s
	__IO float Gyro_Y;//���ٶ�ֵ rad/s
	__IO float Gyro_Z;//���ٶ�ֵ rad/s
	__IO float Pitch;//������ rad
	__IO float Yaw;//ƫ���� rad
	__IO float Roll;//������ rad
	__IO float Temperature;//�¶�ֵ ��
	__IO uint16_t NowTimeStamp;//��ǰ����ʱ��� us
	__IO uint16_t LastTimeStamp;//��һ�β���ʱ��� us
	__IO uint16_t TimeStamp;//�������� us
	__IO uint16_t FIFOCount;//��ǰFIFO������ֽ���
	__IO uint8_t Buf[20];
}ICM42605_Struct;//ICM42605�ṹ�����


uint8_t ICM42605_Init(void);
void ICM42605_Read_FIFO(ICM42605_Struct* ICM42605);

#ifdef __cplusplus
}
#endif

#endif
