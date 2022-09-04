#include "tim4.h"
TIM_HandleTypeDef htim4;

/*-----------------------------------------------------------
��������: TIM4-������ģʽ��ʼ��
�������: None
�� �� ֵ: None
˵    ��: TIM4����Ϊ������ģʽ
 -----------------------------------------------------------*/
void MX_TIM4_Init(void)
{
  TIM_Encoder_InitTypeDef sConfig;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;//��ʱ��Ԥ��Ƶ
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;//���ϼ���ģʽ
  htim4.Init.Period = 0xFFFF;//��ʱ������
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ

  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;//������ģʽ3 ˫���ؼ���
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;//����
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;//��ӳ��
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;//����Ƶ
  sConfig.IC1Filter = 0xF;//�˲���
	
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;//����
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;//��ӳ��
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;//����Ƶ
  sConfig.IC2Filter = 0xF;//�˲���
	__HAL_TIM_SET_COUNTER(&htim4,0);//����TIM4->CNTֵΪ0
  HAL_TIM_Encoder_Init(&htim4, &sConfig);
	
	__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);  // ��������жϱ�־λ
//  __HAL_TIM_ENABLE_IT(&htim4,TIM_IT_UPDATE);  // ʹ�ܸ����ж�
	
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1|TIM_CHANNEL_2);//������ʱ���ı�����ģʽ
}
