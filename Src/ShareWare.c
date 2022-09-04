#include "ShareWare.h"

union floatHex_union floatHex;

__IO uint16_t Loop_1msTime=0;//1ms轮询时间
__IO uint16_t Loop_5msTime=0;//5ms轮询时间
__IO uint16_t Loop_10msTime=0;//10ms轮询时间
__IO uint16_t Loop_100msTime=0;//100ms轮询时间
__IO uint16_t Loop_500msTime=0;//500ms轮询时间


RS485_Struct RS485;//创建RS485结构体参数

IndicatorDevice_Struct Buzzer;//创建蜂鸣器控制结构体参数
IndicatorDevice_Struct LED_Gre;//创建绿色LED控制结构体参数
IndicatorDevice_Struct LED_Red;//创建红色LED控制结构体参数

Battery_Struct Battery;//电池状态信息结构体参数

RC_Struct RC;//创建RC遥控器结构体参数

Encoder_Struct Encoder_M1;//创建M1电机编码器结构体参数
Encoder_Struct Encoder_M2;//创建M2电机编码器结构体参数
Encoder_Struct Encoder_M3;//创建M3电机编码器结构体参数
Encoder_Struct Encoder_M4;//创建M4电机编码器结构体参数

IncPID_Struct PID_M1;//创建M1电机PID结构体参数
IncPID_Struct PID_M2;//创建M2电机PID结构体参数
IncPID_Struct PID_M3;//创建M3电机PID结构体参数
IncPID_Struct PID_M4;//创建M4电机PID结构体参数

VelControl_Struct VelControl;//创建电机转速控制结构体参数

Kinematics_Struct Kinematics_Inverse;//创建车体运动学逆解结构体参数
Kinematics_Struct Kinematics_Forward;//创建车体运动学正解结构体参数

ICM42605_Struct ICM42605;//创建ICM42605结构体参数

LPF_Struct LPF_RPM1;//创建低通滤波RPM1结构体参数
LPF_Struct LPF_RPM2;//创建低通滤波RPM2结构体参数
LPF_Struct LPF_RPM3;//创建低通滤波RPM3结构体参数
LPF_Struct LPF_RPM4;//创建低通滤波RPM4结构体参数

DataCom_RX_Struct DataCom_RX;//创建数据协议结构体参数
ParseData_Struct ParseData_Mast;//创建解析协议结构体参数

QueueHandle_t MastMessage_Queue;	//主机消息队列句柄
