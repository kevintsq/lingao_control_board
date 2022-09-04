#ifndef __RC_H
#define __RC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

enum RC_Enum
{
	RC_UP=0,		//拨钮开关拨上
	RC_Middle,	//拨钮开关拨中间
	RC_DOWN			//拨钮开关拨下
};

typedef struct
{		
	__IO float Left_X; //左侧摇杆X值，数值范围 -1.0f ~ 1.0f
	__IO float Left_Y; //左侧摇杆Y值，数值范围 -1.0f ~ 1.0f
	__IO float Right_X;//右侧摇杆X值，数值范围 -1.0f ~ 1.0f
	__IO float Right_Y;//右侧摇杆Y值，数值范围 -1.0f ~ 1.0f
	__IO uint8_t Switch;	 //三档拨钮开关，[RC_UP：拨上]、[RC_Middle：拨中间]、[RC_DOWN：拨下]
	__IO float Knob;	 	 //旋钮0.0f~1.0f
	__IO uint8_t ConnectState;//遥控器与接收器连接状态 0=未连接，1=正常连接
	
	__IO uint16_t CH1;//通道1数值
	__IO uint16_t CH2;//通道2数值
	__IO uint16_t CH3;//通道3数值
	__IO uint16_t CH4;//通道4数值
	__IO uint16_t CH5;//通道5数值
	__IO uint16_t CH6;//通道6数值
}RC_Struct;//RC遥控器结构体参数

/*-----------------------------------------------------------
函数功能: 遥控器更新函数
输入参数: 遥控器结构体参数
返 回 值: None
说    明: 该函数放在串口DMA接收中断函数中进行调用
 -----------------------------------------------------------*/
void RC_Update(RC_Struct *RC, uint8_t *Data);//遥控器更新函数

#ifdef __cplusplus
}
#endif

#endif
