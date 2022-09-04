#ifndef __SHAREWARE_H
#define __SHAREWARE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "FreeRTOS.h"
#include "queue.h"

#include "uart.h"
#include "RS485.h"
#include "can1.h"
#include "adc1.h"
#include "tim8.h"
#include "tim1.h"
#include "tim2.h"
#include "tim3.h"
#include "tim4.h"
#include "tim5.h"
#include "spi.h"
#include "RC.h"
#include "pid.h"
#include "Encoder.h"
#include "MotorControl.h"
#include "BatteryInfor.h"
#include "LowPassFilter.h"
#include "IndicatorDevice.h"
#include "VelocityControl.h"
#include "ICM42605.h"
#include "Kinematics_4WD.h"
#include "DataCom.h"
#include "DataProtocol.h"

#define Constrain(AMT, MIN, MAX) ((AMT) < (MIN)? (MIN):( (AMT) > (MAX)?(MAX):(AMT) ))//约束函数

#define PI 3.1415926f

union floatHex_union
{
	uint8_t Hex[4];
	float floatValue;
};

extern __IO uint16_t Loop_1msTime;//1ms轮询时间
extern __IO uint16_t Loop_5msTime;//5ms轮询时间
extern __IO uint16_t Loop_10msTime;//10ms轮询时间
extern __IO uint16_t Loop_100msTime;//100ms轮询时间
extern __IO uint16_t Loop_500msTime;//500ms轮询时间

extern union floatHex_union floatHex;

extern RS485_Struct RS485;//创建RS485结构体参数

extern IndicatorDevice_Struct Buzzer;//创建蜂鸣器控制结构体参数
extern IndicatorDevice_Struct LED_Gre;//创建绿色LED控制结构体参数
extern IndicatorDevice_Struct LED_Red;//创建红色LED控制结构体参数

extern Battery_Struct Battery;//电池状态信息结构体参数

extern RC_Struct RC;//创建RC遥控器结构体参数

extern Encoder_Struct Encoder_M1;//创建M1电机编码器结构体参数
extern Encoder_Struct Encoder_M2;//创建M2电机编码器结构体参数
extern Encoder_Struct Encoder_M3;//创建M3电机编码器结构体参数
extern Encoder_Struct Encoder_M4;//创建M4电机编码器结构体参数

extern IncPID_Struct PID_M1;//创建M1电机PID结构体参数
extern IncPID_Struct PID_M2;//创建M2电机PID结构体参数
extern IncPID_Struct PID_M3;//创建M3电机PID结构体参数
extern IncPID_Struct PID_M4;//创建M4电机PID结构体参数

extern VelControl_Struct VelControl;//创建电机转速控制结构体参数

extern Kinematics_Struct Kinematics_Inverse;//创建车体运动学逆解结构体参数
extern Kinematics_Struct Kinematics_Forward;//创建车体运动学正解结构体参数

extern ICM42605_Struct ICM42605;//创建ICM42605结构体参数

extern LPF_Struct LPF_RPM1;//创建低通滤波RPM1结构体参数
extern LPF_Struct LPF_RPM2;//创建低通滤波RPM2结构体参数
extern LPF_Struct LPF_RPM3;//创建低通滤波RPM3结构体参数
extern LPF_Struct LPF_RPM4;//创建低通滤波RPM4结构体参数

extern DataCom_RX_Struct DataCom_RX;//创建数据协议结构体参数
extern ParseData_Struct ParseData_Mast;//创建解析协议结构体参数

extern QueueHandle_t MastMessage_Queue;	//主机消息队列句柄

#ifdef __cplusplus
}
#endif

#endif
