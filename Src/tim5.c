#include "tim5.h"
TIM_HandleTypeDef htim5;

/*-----------------------------------------------------------
��������: TIM5-������ģʽ��ʼ��
�������: None
�� �� ֵ: None
˵    ��: TIM5����Ϊ������ģʽ
 -----------------------------------------------------------*/
void MX_TIM5_Init(void)
{
  TIM_Encoder_InitTypeDef sConfig;

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;//��ʱ��Ԥ��Ƶ
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;//���ϼ���ģʽ
  htim5.Init.Period = 0xFFFF;//��ʱ������
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ

  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;//������ģʽ3 ˫���ؼ���
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;//����
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;//��ӳ��
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;//����Ƶ
  sConfig.IC1Filter = 0xF;//�˲���
	
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;//����
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;//��ӳ��
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;//����Ƶ
  sConfig.IC2Filter = 0xF;//�˲���
	__HAL_TIM_SET_COUNTER(&htim5,0);//����TIM5->CNTֵΪ0
  HAL_TIM_Encoder_Init(&htim5, &sConfig);
	
	__HAL_TIM_CLEAR_IT(&htim5, TIM_IT_UPDATE);  // ��������жϱ�־λ
//  __HAL_TIM_ENABLE_IT(&htim5,TIM_IT_UPDATE);  // ʹ�ܸ����ж�
	
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_1|TIM_CHANNEL_2);//������ʱ���ı�����ģʽ
}
