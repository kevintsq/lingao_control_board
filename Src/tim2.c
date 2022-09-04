#include "tim2.h"
TIM_HandleTypeDef htim2;

/*-----------------------------------------------------------
��������: TIM2-������ģʽ��ʼ��
�������: None
�� �� ֵ: None
˵    ��: TIM2����Ϊ������ģʽ,IO ����ӳ��
 -----------------------------------------------------------*/
void MX_TIM2_Init(void)//TIM2-������ģʽ��ʼ��
{
  TIM_Encoder_InitTypeDef sConfig;
	
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;//��ʱ��Ԥ��Ƶ
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;//���ϼ���ģʽ
  htim2.Init.Period = 0xFFFF;//��ʱ������
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ

  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;//������ģʽ3 ˫���ؼ���
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;//����
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;//��ӳ��
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;//����Ƶ
  sConfig.IC1Filter = 0xF;//�˲���
	
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;//����
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;//��ӳ��
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;//����Ƶ
  sConfig.IC2Filter = 0xF;//�˲���
	__HAL_TIM_SET_COUNTER(&htim2,0);//����TIM2->CNTֵΪ0
  HAL_TIM_Encoder_Init(&htim2, &sConfig);
	
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);  // ��������жϱ�־λ
//  __HAL_TIM_ENABLE_IT(&htim2,TIM_IT_UPDATE);  // ʹ�ܸ����ж�
	
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1|TIM_CHANNEL_2);//������ʱ���ı�����ģʽ
}

