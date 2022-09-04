#include "Encoder.h"
#include "ShareWare.h"

__IO uint16_t TIM1_OverflowCount;//定时器1溢出次数计数值
__IO uint16_t TIM2_OverflowCount;//定时器2溢出次数计数值
__IO uint16_t TIM3_OverflowCount;//定时器3溢出次数计数值
__IO uint16_t TIM4_OverflowCount;//定时器4溢出次数计数值
__IO uint16_t TIM5_OverflowCount;//定时器5溢出次数计数值


int8_t Sgn(int16_t a)//符号函数
{
	if(a>0) return 1;
	else if(a<0) return -1;
	else return 0;
}

/*-----------------------------------------------------------
函数功能：初始化编码器结构体参数
入口参数：结构体参数，对应的定时器序号
返 回 值：None
说    明: 
参数“TIMx”用于指定结构体对应的定时器序号，数值范围为1~5，对应定时器TIM1~TIM5
 -----------------------------------------------------------*/
void Encoder_Struct_Init(Encoder_Struct *Encoder)
{
	Encoder->CaptureCount = 0;	//编码器捕获计数值
	Encoder->Capture_D_Value = 0;//编码器前后2次捕获计数的差值
	Encoder->CaptureCount_Last = 0;//缓存上一次的编码器计数器值
}

/*-----------------------------------------------------------
函数功能：更新编码器数值
入口参数：结构体参数，TIM捕获计数值，符号参数
返 回 值：None
说    明: 
调用该函数后“Encoder->CaptureCount”与“Encoder->Capture_D_Value”会获得更新

函数传入的参数中“Signed”的数值为“1”或“-1”
该数值为1时，“Encoder->CaptureCount”与“Encoder->Capture_D_Value”的更新值重新乘以1
该数值为-1时，“Encoder->CaptureCount”与“Encoder->Capture_D_Value”的更新值重新乘以-1
 -----------------------------------------------------------*/
void Encoder_UpdataValue(Encoder_Struct *Encoder, int16_t CaptureCount, int8_t Signed)
{
	int16_t CaptureCount_Static = CaptureCount * Signed;//获取编码器捕获计数值

	if(Sgn(CaptureCount_Static) != Sgn(Encoder->CaptureCount_Last))
	{
		uint16_t i1 = abs(CaptureCount_Static) + abs(Encoder->CaptureCount_Last);
		uint16_t i2 = 65535 - i1;
		if(i1 < i2) 
		{
			if(CaptureCount_Static > Encoder->CaptureCount_Last) Encoder->Capture_D_Value = i1;//获取编码器前后2次捕获计数的差值
			else Encoder->Capture_D_Value = -i1;//获取编码器前后2次捕获计数的差值
		}
		else 
		{
			if(CaptureCount_Static > Encoder->CaptureCount_Last) Encoder->Capture_D_Value = -i2;//获取编码器前后2次捕获计数的差值
			else Encoder->Capture_D_Value = i2;//获取编码器前后2次捕获计数的差值
		}
	}
	else
	{
		Encoder->Capture_D_Value = CaptureCount_Static - Encoder->CaptureCount_Last;//获取编码器前后2次捕获计数的差值
	}

	Encoder->CaptureCount_Last = CaptureCount_Static;
	
	Encoder->CaptureCount += (int32_t)Encoder->Capture_D_Value;
}

/*-----------------------------------------------------------
函数功能: 编码器计数溢出中断函数
输入参数: 定时器句柄
返 回 值: None
说    明: 编码器计数溢出后会进入该中断函数
 0xFFFF跳变到0x0000，溢出
 0x0000跳变到0xFFFF，溢出
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
			TIM1_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM1_OverflowCount++;  		 //向上计数溢出
		}
	}
	
	else if(htim->Instance == TIM2)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM2_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM2_OverflowCount++;  		 //向上计数溢出
		}
	}
	
	else if(htim->Instance == TIM3)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM3_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM3_OverflowCount++;  		 //向上计数溢出
		}
	}
	
	else if(htim->Instance == TIM4)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM4_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM4_OverflowCount++;  		 //向上计数溢出
		}
	}

	else if(htim->Instance == TIM5)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM5_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM5_OverflowCount++;  		 //向上计数溢出
		} 
	}
}
