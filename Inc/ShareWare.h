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

#define Constrain(AMT, MIN, MAX) ((AMT) < (MIN)? (MIN):( (AMT) > (MAX)?(MAX):(AMT) ))//Լ������

#define PI 3.1415926f

union floatHex_union
{
	uint8_t Hex[4];
	float floatValue;
};

extern __IO uint16_t Loop_1msTime;//1ms��ѯʱ��
extern __IO uint16_t Loop_5msTime;//5ms��ѯʱ��
extern __IO uint16_t Loop_10msTime;//10ms��ѯʱ��
extern __IO uint16_t Loop_100msTime;//100ms��ѯʱ��
extern __IO uint16_t Loop_500msTime;//500ms��ѯʱ��

extern union floatHex_union floatHex;

extern RS485_Struct RS485;//����RS485�ṹ�����

extern IndicatorDevice_Struct Buzzer;//�������������ƽṹ�����
extern IndicatorDevice_Struct LED_Gre;//������ɫLED���ƽṹ�����
extern IndicatorDevice_Struct LED_Red;//������ɫLED���ƽṹ�����

extern Battery_Struct Battery;//���״̬��Ϣ�ṹ�����

extern RC_Struct RC;//����RCң�����ṹ�����

extern Encoder_Struct Encoder_M1;//����M1����������ṹ�����
extern Encoder_Struct Encoder_M2;//����M2����������ṹ�����
extern Encoder_Struct Encoder_M3;//����M3����������ṹ�����
extern Encoder_Struct Encoder_M4;//����M4����������ṹ�����

extern IncPID_Struct PID_M1;//����M1���PID�ṹ�����
extern IncPID_Struct PID_M2;//����M2���PID�ṹ�����
extern IncPID_Struct PID_M3;//����M3���PID�ṹ�����
extern IncPID_Struct PID_M4;//����M4���PID�ṹ�����

extern VelControl_Struct VelControl;//�������ת�ٿ��ƽṹ�����

extern Kinematics_Struct Kinematics_Inverse;//���������˶�ѧ���ṹ�����
extern Kinematics_Struct Kinematics_Forward;//���������˶�ѧ����ṹ�����

extern ICM42605_Struct ICM42605;//����ICM42605�ṹ�����

extern LPF_Struct LPF_RPM1;//������ͨ�˲�RPM1�ṹ�����
extern LPF_Struct LPF_RPM2;//������ͨ�˲�RPM2�ṹ�����
extern LPF_Struct LPF_RPM3;//������ͨ�˲�RPM3�ṹ�����
extern LPF_Struct LPF_RPM4;//������ͨ�˲�RPM4�ṹ�����

extern DataCom_RX_Struct DataCom_RX;//��������Э��ṹ�����
extern ParseData_Struct ParseData_Mast;//��������Э��ṹ�����

extern QueueHandle_t MastMessage_Queue;	//������Ϣ���о��

#ifdef __cplusplus
}
#endif

#endif
