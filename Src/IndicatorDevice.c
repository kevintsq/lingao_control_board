/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：
1、控制提示设备

**************************************************************************/
#include "IndicatorDevice.h"
				
/*-----------------------------------------------------------
函数功能: 提示设备初始化配置函数
输入参数: None
返 回 值: None
说    明: None
 -----------------------------------------------------------*/				
void IndicatorDevice_Init(IndicatorDevice_Struct *IndicatorDevice, GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN)//
{
	IndicatorDevice->LockedStatus = 0;//上锁状态 1代表上锁 0代表未上锁
	IndicatorDevice->PeriodTime = 0;//闪烁周期
	IndicatorDevice->PeriodTimeBuffer = 0;//缓存亮灯时间
	IndicatorDevice->Times = 0;//闪烁次数
	IndicatorDevice->LastTimes = 0;
	IndicatorDevice->LastPeriodTime = 0;
	IndicatorDevice->GPIOx = GPIOx;
	IndicatorDevice->GPIO_PIN = GPIO_PIN;
	
	/* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStruct;
	if(GPIOx == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOF) __HAL_RCC_GPIOF_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOG) __HAL_RCC_GPIOG_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	
	/*电机驱动芯片1对应GPIO引脚配置*/
  GPIO_InitStruct.Pin = GPIO_PIN;//设定对应引脚IO编号
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//设定对应引脚IO为输出模式
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW ;//设对应引脚IO操作速度
	GPIO_InitStruct.Pull = GPIO_NOPULL;//内部浮空
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);//初始化对应引脚IO  
}

/*-----------------------------------------------------------
函数功能: 提示设备控制函数
输入参数: 闪烁次数，闪烁周期
返 回 值: None
说    明: 
参数“Times”是闪烁次数 
闪烁次数代表连续闪烁的次数，例如该参数为5，代表闪烁5次后停止
该值为0时代表灭，该值为0xFFFF时代表闪烁次数无限

参数“PeriodTime”是闪烁周期
闪烁周期代表亮和灭的时间周期，例如该参数为5，代表亮和灭的时间各为5ms
该值为0时代表灭，该值为0xFFFF时代表长亮
 -----------------------------------------------------------*/
void IndicatorDeviceControl(IndicatorDevice_Struct *IndicatorDevice, uint16_t Times, uint16_t PeriodTime)//提示设备控制函数
{
	if(IndicatorDevice->LastTimes != Times || IndicatorDevice->LastPeriodTime != PeriodTime || (!IndicatorDevice->Times && !IndicatorDevice->PeriodTime))//防止反复调用该函数导致不正常执行
	{
		IndicatorDevice->LastTimes = Times;
		IndicatorDevice->LastPeriodTime = PeriodTime;
		
		IndicatorDevice->LockedStatus=1;//上锁状态为1
		
		if(!Times)//闪烁次数为0
		{
			HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_RESET);//灭
			return;//退出函数
		}
		else if(!PeriodTime)//闪烁周期为0
		{
			HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_RESET);//灭
			return;//退出函数
		}
		else
		{
			if(PeriodTime == 0xFFFF)//长亮
			{
				HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_SET);//亮
				return;//退出函数
			}	
			else if(Times == 0xFFFF)//持续闪烁
			{
				HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_RESET);//灭
				IndicatorDevice->Times =  Times;//赋值0xFFFF
				IndicatorDevice->PeriodTimeBuffer= PeriodTime;//更新缓存闪烁周期
				IndicatorDevice->PeriodTime =0;//闪烁周期清0
			}
			else
			{
				HAL_GPIO_WritePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN, GPIO_PIN_RESET);//灭
				IndicatorDevice->Times =  Times * 2;//闪烁次数*2  PS：一亮一灭为一个周期，因此需要乘2
				IndicatorDevice->PeriodTimeBuffer= PeriodTime;//更新缓存闪烁周期
				IndicatorDevice->PeriodTime =0;//闪烁周期清0
			}
			IndicatorDevice->LockedStatus=0;//上锁状态为0
		}	
	}
}

/*-----------------------------------------------------------
函数功能: 指示设备循环函数
输入参数: None
返 回 值: None
说    明: 该函数是控制指示设备的开、关状态，需要将该函数放到
滴答定时器中断函数中运行
 -----------------------------------------------------------*/
void IndicatorDeviceLoop(IndicatorDevice_Struct *IndicatorDevice)
{
	if(IndicatorDevice->PeriodTime) IndicatorDevice->PeriodTime--;//闪烁周期
	if(!IndicatorDevice->LockedStatus)//没有上锁才执行
	{
		if(IndicatorDevice->Times && !IndicatorDevice->PeriodTime)//闪烁次数不为0，闪烁周期时间为0
		{
			HAL_GPIO_TogglePin(IndicatorDevice->GPIOx, IndicatorDevice->GPIO_PIN);//IO口电平翻转
			if(IndicatorDevice->Times != 0xFFFF) IndicatorDevice->Times--;//如果闪烁次数非无限次则闪烁次数减1
			IndicatorDevice->PeriodTime = IndicatorDevice->PeriodTimeBuffer;//闪烁周期时间重新赋值
		}
	}
}
