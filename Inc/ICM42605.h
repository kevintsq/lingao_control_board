#ifndef __ICM42605_H
#define __ICM42605_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

typedef struct
{		
	__IO float Acc_X;//加速度值 g
	__IO float Acc_Y;//加速度值 g
	__IO float Acc_Z;//加速度值 g
	__IO float Gyro_X;//角速度值 rad/s
	__IO float Gyro_Y;//角速度值 rad/s
	__IO float Gyro_Z;//角速度值 rad/s
	__IO float Pitch;//俯仰角 rad
	__IO float Yaw;//偏航角 rad
	__IO float Roll;//翻滚角 rad
	__IO float Temperature;//温度值 ℃
	__IO uint16_t NowTimeStamp;//当前采样时间戳 us
	__IO uint16_t LastTimeStamp;//上一次采样时间戳 us
	__IO uint16_t TimeStamp;//采样周期 us
	__IO uint16_t FIFOCount;//当前FIFO缓存的字节数
	__IO uint8_t Buf[20];
}ICM42605_Struct;//ICM42605结构体参数


uint8_t ICM42605_Init(void);
void ICM42605_Read_FIFO(ICM42605_Struct* ICM42605);

#ifdef __cplusplus
}
#endif

#endif
