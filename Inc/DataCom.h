#ifndef __DATACOM_H
#define __DATACOM_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
typedef struct
{	
	__IO float Linear_X; //车体目标线速度值 m/s
	__IO float Linear_Y; //车体目标线速度值 m/s
	__IO float Angular_Z;//车体目标角速度值 rad/s
	__IO uint16_t HeartbeatTime;//心跳包时间
}DataCom_RX_Struct;//数据协议结构体参数


void DataCom_RX_Function(DataCom_RX_Struct *DataCom_RX, uint8_t *Buff);//接收数据接口
	
#ifdef __cplusplus
}
#endif

#endif
