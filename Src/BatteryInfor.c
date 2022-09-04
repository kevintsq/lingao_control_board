/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1�����µ��״̬��Ϣ
2����������ʣ������ٷֱ�
**************************************************************************/
#include "BatteryInfor.h"
#include "ShareWare.h"

#define R1_R2 ((82.0f + 10.0f) / 10.0f)	//ͨ����ѹ��������ѹϵ��
#define	ADC_VREFINT 1.212f				//ADC�ڲ����յ�ѹ

/*-----------------------------------------------------------
��������: ���״̬��ʼ������
�������: ��ز����ṹ��ָ�룬��ͨ�˲�ϵ��
�� �� ֵ: None
˵    ��: None
 -----------------------------------------------------------*/
void Battery_Init(Battery_Struct *Battery, float a)
{	
	Battery->ADchx = 0;//��ѹADCֵ
	Battery->ADre = 0; //STM32�ڲ����յ�ѹADCֵ
	Battery->a = a; //��ͨ�˲�ϵ��
	Battery->Voltage = 0; //��ѹֵ V
	Battery->Current = 0; //����ֵ A
	Battery->Capacity = 0;//ʣ����� %
}

/*-----------------------------------------------------------
��������: ���µ��״̬��Ϣ
�������: ��ز����ṹ��ָ�룬ADC��DMA��������ָ��
�� �� ֵ: None
˵    ��: ���øú������µ�صĵ�ѹ��������Ϣ
 -----------------------------------------------------------*/
void UpdateBatteryInfor(Battery_Struct *Battery, uint16_t *ADCx_DMA_Buff)
{
	Battery->ADchx =  ADCx_DMA_Buff[0];//��ȡ��ص�ѹADCֵ
	Battery->ADre  =  ADCx_DMA_Buff[1];//STM32�ڲ����յ�ѹADCֵ	
	float Voltage = ADC_VREFINT * (float)Battery->ADchx / (float)Battery->ADre * R1_R2;//ͨ�����������ѹ�������ص�ѹֵ��ֵ����ͨ�˲����ṹ���еĲɼ�ֵ
	Battery->Voltage = (Battery->a * Voltage) + (1.0f - Battery->a) * Battery->Voltage;//��ص�ѹֵ������ͨ�˲�������ֵ������ȶ�	
	Battery->Capacity = GetdBatteryCapacity(Battery->Voltage, 4);//��ȡ���ʣ������ٷֱ�
}

/*-----------------------------------------------------------
��������: ��������ʣ������ٷֱ�
�������: ��ǰ����������ѹֵ��﮵�ش�����
�� �� ֵ: ��ǰ�����ʣ������ٷֱ�ֵ
˵    ��: �����ٷֱ���ֵ��Χ0-100���ú�������﮵�ص���������Ч��
 -----------------------------------------------------------*/
uint8_t GetdBatteryCapacity(float BatteryVoltag, uint8_t BatterySeriesNumber)
{
	uint8_t BatteryCapacity;//﮵��������ٷֱ�ֵ
	float SingleBatteryVoltag = (float)BatteryVoltag / BatterySeriesNumber;//����﮵���鵥��﮵�ص�ѹֵ
	if(SingleBatteryVoltag >= 4.06f)      BatteryCapacity=(((SingleBatteryVoltag - 4.06f)/0.14f)*10+90);
	else if(SingleBatteryVoltag >= 3.98f) BatteryCapacity=(((SingleBatteryVoltag - 3.98f)/0.08f)*10+80);
	else if(SingleBatteryVoltag >= 3.92f) BatteryCapacity=(((SingleBatteryVoltag - 3.92f)/0.06f)*10+70);
	else if(SingleBatteryVoltag >= 3.87f) BatteryCapacity=(((SingleBatteryVoltag - 3.87f)/0.05f)*10+60);
	else if(SingleBatteryVoltag >= 3.82f) BatteryCapacity=(((SingleBatteryVoltag - 3.82f)/0.05f)*10+50);
	else if(SingleBatteryVoltag >= 3.79f) BatteryCapacity=(((SingleBatteryVoltag - 3.79f)/0.03f)*10+40);
	else if(SingleBatteryVoltag >= 3.77f) BatteryCapacity=(((SingleBatteryVoltag - 3.77f)/0.02f)*10+30);
	else if(SingleBatteryVoltag >= 3.74f) BatteryCapacity=(((SingleBatteryVoltag - 3.74f)/0.03f)*10+20);
	else if(SingleBatteryVoltag >= 3.68f) BatteryCapacity=(((SingleBatteryVoltag - 3.68f)/0.06f)*10+10);
	else if(SingleBatteryVoltag >= 3.45f) BatteryCapacity=(((SingleBatteryVoltag - 3.45f)/0.23f)*10+5);
	else if(SingleBatteryVoltag >= 3.0f)  BatteryCapacity=(((SingleBatteryVoltag - 3.0f)/0.45f)*10+0);
	else BatteryCapacity = 0;
	if(BatteryCapacity > 100) BatteryCapacity = 100;
	return BatteryCapacity;//��ص���
}
