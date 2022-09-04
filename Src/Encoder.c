#include "Encoder.h"
#include "ShareWare.h"

__IO uint16_t TIM1_OverflowCount;//��ʱ��1�����������ֵ
__IO uint16_t TIM2_OverflowCount;//��ʱ��2�����������ֵ
__IO uint16_t TIM3_OverflowCount;//��ʱ��3�����������ֵ
__IO uint16_t TIM4_OverflowCount;//��ʱ��4�����������ֵ
__IO uint16_t TIM5_OverflowCount;//��ʱ��5�����������ֵ


int8_t Sgn(int16_t a)//���ź���
{
	if(a>0) return 1;
	else if(a<0) return -1;
	else return 0;
}

/*-----------------------------------------------------------
�������ܣ���ʼ���������ṹ�����
��ڲ������ṹ���������Ӧ�Ķ�ʱ�����
�� �� ֵ��None
˵    ��: 
������TIMx������ָ���ṹ���Ӧ�Ķ�ʱ����ţ���ֵ��ΧΪ1~5����Ӧ��ʱ��TIM1~TIM5
 -----------------------------------------------------------*/
void Encoder_Struct_Init(Encoder_Struct *Encoder)
{
	Encoder->CaptureCount = 0;	//�������������ֵ
	Encoder->Capture_D_Value = 0;//������ǰ��2�β�������Ĳ�ֵ
	Encoder->CaptureCount_Last = 0;//������һ�εı�����������ֵ
}

/*-----------------------------------------------------------
�������ܣ����±�������ֵ
��ڲ������ṹ�������TIM�������ֵ�����Ų���
�� �� ֵ��None
˵    ��: 
���øú�����Encoder->CaptureCount���롰Encoder->Capture_D_Value�����ø���

��������Ĳ����С�Signed������ֵΪ��1����-1��
����ֵΪ1ʱ����Encoder->CaptureCount���롰Encoder->Capture_D_Value���ĸ���ֵ���³���1
����ֵΪ-1ʱ����Encoder->CaptureCount���롰Encoder->Capture_D_Value���ĸ���ֵ���³���-1
 -----------------------------------------------------------*/
void Encoder_UpdataValue(Encoder_Struct *Encoder, int16_t CaptureCount, int8_t Signed)
{
	int16_t CaptureCount_Static = CaptureCount * Signed;//��ȡ�������������ֵ

	if(Sgn(CaptureCount_Static) != Sgn(Encoder->CaptureCount_Last))
	{
		uint16_t i1 = abs(CaptureCount_Static) + abs(Encoder->CaptureCount_Last);
		uint16_t i2 = 65535 - i1;
		if(i1 < i2) 
		{
			if(CaptureCount_Static > Encoder->CaptureCount_Last) Encoder->Capture_D_Value = i1;//��ȡ������ǰ��2�β�������Ĳ�ֵ
			else Encoder->Capture_D_Value = -i1;//��ȡ������ǰ��2�β�������Ĳ�ֵ
		}
		else 
		{
			if(CaptureCount_Static > Encoder->CaptureCount_Last) Encoder->Capture_D_Value = -i2;//��ȡ������ǰ��2�β�������Ĳ�ֵ
			else Encoder->Capture_D_Value = i2;//��ȡ������ǰ��2�β�������Ĳ�ֵ
		}
	}
	else
	{
		Encoder->Capture_D_Value = CaptureCount_Static - Encoder->CaptureCount_Last;//��ȡ������ǰ��2�β�������Ĳ�ֵ
	}

	Encoder->CaptureCount_Last = CaptureCount_Static;
	
	Encoder->CaptureCount += (int32_t)Encoder->Capture_D_Value;
}

/*-----------------------------------------------------------
��������: ��������������жϺ���
�������: ��ʱ�����
�� �� ֵ: None
˵    ��: ���������������������жϺ���
 0xFFFF���䵽0x0000�����
 0x0000���䵽0xFFFF�����
 -----------------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM7) 
	{
		HAL_IncTick();
	}

	if(htim->Instance == TIM1)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM1_OverflowCount--;       //���¼������
		}
		else
		{
			TIM1_OverflowCount++;  		 //���ϼ������
		}
	}
	
	else if(htim->Instance == TIM2)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM2_OverflowCount--;       //���¼������
		}
		else
		{
			TIM2_OverflowCount++;  		 //���ϼ������
		}
	}
	
	else if(htim->Instance == TIM3)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM3_OverflowCount--;       //���¼������
		}
		else
		{
			TIM3_OverflowCount++;  		 //���ϼ������
		}
	}
	
	else if(htim->Instance == TIM4)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM4_OverflowCount--;       //���¼������
		}
		else
		{
			TIM4_OverflowCount++;  		 //���ϼ������
		}
	}

	else if(htim->Instance == TIM5)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM5_OverflowCount--;       //���¼������
		}
		else
		{
			TIM5_OverflowCount++;  		 //���ϼ������
		} 
	}
}
