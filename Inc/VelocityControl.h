#ifndef __VELOCITYCONTROL_H
#define __VELOCITYCONTROL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define VelocityControl_T 5//�ٶȱջ��������� ms
#define RPM_MAX         300.0f //������ת�� rpm
#define COUNTS_PER_REV   144000//��������תһȦ����������ֵ89600  144000

typedef struct
{
	__IO float M1_RPM;	 //M1�����ǰת�� rpm
	__IO float M2_RPM;	 //M2�����ǰת�� rpm
	__IO float M3_RPM;	 //M3�����ǰת�� rpm
	__IO float M4_RPM;	 //M4�����ǰת�� rpm
	__IO float M1_SetRPM;//M1���Ŀ��ת�� rpm
	__IO float M2_SetRPM;//M2���Ŀ��ת�� rpm
	__IO float M3_SetRPM;//M3���Ŀ��ת�� rpm
	__IO float M4_SetRPM;//M4���Ŀ��ת�� rpm
}VelControl_Struct; //���ת�ٿ��ƽṹ�����

void VelocityControl_4WD(VelControl_Struct *VelControl);//4WD�ٶȱջ����ƺ���

#ifdef __cplusplus
}
#endif

#endif
