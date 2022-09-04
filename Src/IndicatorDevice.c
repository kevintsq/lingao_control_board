/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1��������ʾ�豸

**************************************************************************/
#include "IndicatorDevice.h"
				
/*-----------------------------------------------------------
��������: ��ʾ�豸��ʼ�����ú���
�������: None
�� �� ֵ: None
˵    ��: None
 -----------------------------------------------------------*/				
void IndicatorDevice_Init(IndicatorDevice_Struct *IndicatorDevice, GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN)//
{
	IndicatorDevice->LockedStatus = 0;//����״̬ 1�������� 0����δ����
	IndicatorDevice->PeriodTime = 0;//��˸����
	IndicatorDevice->PeriodTimeBuffer = 0;//��������ʱ��
	IndicatorDevice->Times = 0;//��˸����
	IndicatorDevice->LastTimes = 0;
	IndicatorDevice->LastPeriodTime = 0;
	IndicatorDevice->GPIOx = GPIOx;
	IndicatorDevice->GPIO_PIN = GPIO_PIN;
	
	/* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	if(GPIOx == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOF) __HAL_RCC_GPIOF_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOG) __HAL_RCC_GPIOG_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
	/*�������оƬ1��ӦGPIO��������*/
  GPIO_InitStruct.Pin = GPIO_PIN;//�趨��Ӧ����IO���
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW ;//���Ӧ����IO�����ٶ�
	GPIO_InitStruct.Pull = GPIO_NOPULL;//�ڲ�����
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);//��ʼ����Ӧ����IO  
}

/*-----------------------------------------------------------
��������: ��ʾ�豸���ƺ���
�������: ��˸��������˸����
�� �� ֵ: None
˵    ��: 
������Times������˸���� 
��˸��������������˸�Ĵ���������ò���Ϊ5��������˸5�κ�ֹͣ
��ֵΪ0ʱ�����𣬸�ֵΪ0xFFFFʱ������˸��������

������PeriodTime������˸����
��˸���ڴ����������ʱ�����ڣ�����ò���Ϊ5�������������ʱ���Ϊ5ms
��ֵΪ0ʱ�����𣬸�ֵΪ0xFFFFʱ������
 -----------------------------------------------------------*/
void IndicatorDeviceControl(IndicatorDevice_Struct *IndicatorDevice, uint16_t Times, uint16_t PeriodTime)//��ʾ�豸���ƺ���
{
	if(IndicatorDevice->LastTimes != Times || IndicatorDevice->LastPeriodTime != PeriodTime || (!IndicatorDevice->Times && !IndicatorDevice->PeriodTime))//��ֹ�������øú������²�����ִ��
	{
		IndicatorDevice->LastTimes = Times;
		IndicatorDevice->LastPeriodTime = PeriodTime;
		
		IndicatorDevice->LockedStatus=1;//����״̬Ϊ1
		
		if(!Times)//��˸����Ϊ0
		{
			HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_RESET);//��
			return;//�˳�����
		}
		else if(!PeriodTime)//��˸����Ϊ0
		{
			HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_RESET);//��
			return;//�˳�����
		}
		else
		{
			if(PeriodTime == 0xFFFF)//����
			{
				HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_SET);//��
				return;//�˳�����
			}	
			else if(Times == 0xFFFF)//������˸
			{
				HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_RESET);//��
				IndicatorDevice->Times =  Times;//��ֵ0xFFFF
				IndicatorDevice->PeriodTimeBuffer= PeriodTime;//���»�����˸����
				IndicatorDevice->PeriodTime =0;//��˸������0
			}
			else
			{
				HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_RESET);//��
				IndicatorDevice->Times =  Times * 2;//��˸����*2  PS��һ��һ��Ϊһ�����ڣ������Ҫ��2
				IndicatorDevice->PeriodTimeBuffer= PeriodTime;//���»�����˸����
				IndicatorDevice->PeriodTime =0;//��˸������0
			}
			IndicatorDevice->LockedStatus=0;//����״̬Ϊ0
		}	
	}
}

/*-----------------------------------------------------------
��������: ָʾ�豸ѭ������
�������: None
�� �� ֵ: None
˵    ��: �ú����ǿ���ָʾ�豸�Ŀ�����״̬����Ҫ���ú����ŵ�
�δ�ʱ���жϺ���������
 -----------------------------------------------------------*/
void IndicatorDeviceLoop(IndicatorDevice_Struct *IndicatorDevice)
{
	if(IndicatorDevice->PeriodTime) IndicatorDevice->PeriodTime--;//��˸����
	if(!IndicatorDevice->LockedStatus)//û��������ִ��
	{
		if(IndicatorDevice->Times && !IndicatorDevice->PeriodTime)//��˸������Ϊ0����˸����ʱ��Ϊ0
		{
			HAL_GPIO_TogglePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN);//IO�ڵ�ƽ��ת
			if(IndicatorDevice->Times != 0xFFFF) IndicatorDevice->Times--;//�����˸���������޴�����˸������1
			IndicatorDevice->PeriodTime = IndicatorDevice->PeriodTimeBuffer;//��˸����ʱ�����¸�ֵ
		}
	}
}
