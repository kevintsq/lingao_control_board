#ifndef __VELOCITYCONTROL_H
#define __VELOCITYCONTROL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define VelocityControl_T 5//速度闭环控制周期 ms
#define RPM_MAX         300.0f //电机最大转速 rpm
#define COUNTS_PER_REV   144000//电机输出轴转一圈编码器计数值89600  144000

typedef struct
{
	__IO float M1_RPM;	 //M1电机当前转速 rpm
	__IO float M2_RPM;	 //M2电机当前转速 rpm
	__IO float M3_RPM;	 //M3电机当前转速 rpm
	__IO float M4_RPM;	 //M4电机当前转速 rpm
	__IO float M1_SetRPM;//M1电机目标转速 rpm
	__IO float M2_SetRPM;//M2电机目标转速 rpm
	__IO float M3_SetRPM;//M3电机目标转速 rpm
	__IO float M4_SetRPM;//M4电机目标转速 rpm
}VelControl_Struct; //电机转速控制结构体参数

void VelocityControl_4WD(VelControl_Struct *VelControl);//4WD速度闭环控制函数

#ifdef __cplusplus
}
#endif

#endif
