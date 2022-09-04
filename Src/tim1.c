#include "tim1.h"

TIM_HandleTypeDef htim1;

/*-----------------------------------------------------------
��������: TIM1-PWM��ʼ������
�������: None
�� �� ֵ: None
˵    ��: TIM1����ΪPWM���ģʽ PWMƵ��Ϊ50HZ
 -----------------------------------------------------------*/
void MX_TIM1_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 167;//ʱ��Ԥ��Ƶ
	htim1.Init.Period = 19999;//����
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;//���ϼ���ģʽ 
  htim1.Init.RepetitionCounter = 0;//���ظ�����
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//�����Զ���װֵ
  HAL_TIM_PWM_Init(&htim1);


  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);


  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);//����TIM1-CH1ͨ��
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);//����TIM1-CH2ͨ��
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);//����TIM1-CH3ͨ��
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);//����TIM1-CH4ͨ��


  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig);

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//TIM1-CH1ͨ����ʼ���PWM
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//TIM1-CH2ͨ����ʼ���PWM
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);//TIM1-CH3ͨ����ʼ���PWM
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);//TIM1-CH4ͨ����ʼ���PWM
}
