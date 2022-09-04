#include "ShareWare.h"

union floatHex_union floatHex;

__IO uint16_t Loop_1msTime=0;//1ms��ѯʱ��
__IO uint16_t Loop_5msTime=0;//5ms��ѯʱ��
__IO uint16_t Loop_10msTime=0;//10ms��ѯʱ��
__IO uint16_t Loop_100msTime=0;//100ms��ѯʱ��
__IO uint16_t Loop_500msTime=0;//500ms��ѯʱ��


RS485_Struct RS485;//����RS485�ṹ�����

IndicatorDevice_Struct Buzzer;//�������������ƽṹ�����
IndicatorDevice_Struct LED_Gre;//������ɫLED���ƽṹ�����
IndicatorDevice_Struct LED_Red;//������ɫLED���ƽṹ�����

Battery_Struct Battery;//���״̬��Ϣ�ṹ�����

RC_Struct RC;//����RCң�����ṹ�����

Encoder_Struct Encoder_M1;//����M1����������ṹ�����
Encoder_Struct Encoder_M2;//����M2����������ṹ�����
Encoder_Struct Encoder_M3;//����M3����������ṹ�����
Encoder_Struct Encoder_M4;//����M4����������ṹ�����

IncPID_Struct PID_M1;//����M1���PID�ṹ�����
IncPID_Struct PID_M2;//����M2���PID�ṹ�����
IncPID_Struct PID_M3;//����M3���PID�ṹ�����
IncPID_Struct PID_M4;//����M4���PID�ṹ�����

VelControl_Struct VelControl;//�������ת�ٿ��ƽṹ�����

Kinematics_Struct Kinematics_Inverse;//���������˶�ѧ���ṹ�����
Kinematics_Struct Kinematics_Forward;//���������˶�ѧ����ṹ�����

ICM42605_Struct ICM42605;//����ICM42605�ṹ�����

LPF_Struct LPF_RPM1;//������ͨ�˲�RPM1�ṹ�����
LPF_Struct LPF_RPM2;//������ͨ�˲�RPM2�ṹ�����
LPF_Struct LPF_RPM3;//������ͨ�˲�RPM3�ṹ�����
LPF_Struct LPF_RPM4;//������ͨ�˲�RPM4�ṹ�����

DataCom_RX_Struct DataCom_RX;//��������Э��ṹ�����
ParseData_Struct ParseData_Mast;//��������Э��ṹ�����

QueueHandle_t MastMessage_Queue;	//������Ϣ���о��
