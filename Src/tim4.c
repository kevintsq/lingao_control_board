#include "tim4.h"
TIM_HandleTypeDef htim4;

/*-----------------------------------------------------------
函数功能: TIM4-编码器模式初始化
输入参数: None
返 回 值: None
说    明: TIM4配置为编码器模式
 -----------------------------------------------------------*/
void MX_TIM4_Init(void)
{
  TIM_Encoder_InitTypeDef sConfig;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;//定时器预分频
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;//向上计数模式
  htim4.Init.Period = 0xFFFF;//定时器周期
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//时钟分频

  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;//编码器模式3 双边沿计数
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;//极性
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;//不映射
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;//不分频
  sConfig.IC1Filter = 0xF;//滤波器
	
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;//极性
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;//不映射
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;//不分频
  sConfig.IC2Filter = 0xF;//滤波器
	__HAL_TIM_SET_COUNTER(&htim4,0);//设置TIM4->CNT值为0
  HAL_TIM_Encoder_Init(&htim4, &sConfig);
	
	__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);  // 清除更新中断标志位
//  __HAL_TIM_ENABLE_IT(&htim4,TIM_IT_UPDATE);  // 使能更新中断
	
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1|TIM_CHANNEL_2);//开启定时器的编码器模式
}
