#include "tim8.h"

TIM_HandleTypeDef htim8;

/*-----------------------------------------------------------
��������: TIM8-PWM��ʼ������
�������: None
�� �� ֵ: None
˵    ��: TIM8����ΪPWM���ģʽ PWMƵ��Ϊ21KHZ
 -----------------------------------------------------------*/
void MX_TIM8_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 3;//ʱ��Ԥ��Ƶ
	htim8.Init.Period = 1999;//����
	htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;//���ϼ���ģʽ 
  htim8.Init.RepetitionCounter = 0;//���ظ�����
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//�����Զ���װֵ
  HAL_TIM_PWM_Init(&htim8);


  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig);


  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 2000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1);//����TIM8-CH1ͨ��
	HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2);//����TIM8-CH2ͨ��
	HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3);//����TIM8-CH3ͨ��
	HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4);//����TIM8-CH4ͨ��


  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig);

	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);//TIM8-CH1ͨ����ʼ���PWM
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);//TIM8-CH2ͨ����ʼ���PWM
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);//TIM8-CH3ͨ����ʼ���PWM
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);//TIM8-CH4ͨ����ʼ���PWM
}
