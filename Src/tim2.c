#include "tim2.h"
TIM_HandleTypeDef htim2;

/*-----------------------------------------------------------
函数功能: TIM2-编码器模式初始化
输入参数: None
返 回 值: None
说    明: TIM2配置为编码器模式,IO 部分映射
 -----------------------------------------------------------*/
void MX_TIM2_Init(void)//TIM2-编码器模式初始化
{
  TIM_Encoder_InitTypeDef sConfig;
	
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;//定时器预分频
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;//向上计数模式
  htim2.Init.Period = 0xFFFF;//定时器周期
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//时钟分频

  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;//编码器模式3 双边沿计数
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;//极性
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;//不映射
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;//不分频
  sConfig.IC1Filter = 0xF;//滤波器
	
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;//极性
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;//不映射
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;//不分频
  sConfig.IC2Filter = 0xF;//滤波器
	__HAL_TIM_SET_COUNTER(&htim2,0);//设置TIM2->CNT值为0
  HAL_TIM_Encoder_Init(&htim2, &sConfig);
	
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);  // 清除更新中断标志位
//  __HAL_TIM_ENABLE_IT(&htim2,TIM_IT_UPDATE);  // 使能更新中断
	
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1|TIM_CHANNEL_2);//开启定时器的编码器模式
}

