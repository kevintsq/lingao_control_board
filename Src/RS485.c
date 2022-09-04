#include "RS485.h"

/*-----------------------------------------------------------
函数功能: RS485芯片RD引脚配置
输入参数: None
返 回 值: None
说    明: RD引脚低电平时 芯片处于接收数据状态		
					RD引脚高电平时 芯片处于发送数据状态
					当不使用485芯片收发数据时，为防止485芯片占用串口，需要将RD引脚设为高电平状态
 -----------------------------------------------------------*/
void RS485_RD_GPIO_Init(RS485_Struct *RS485, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	RS485->Time = 0;
	RS485->GPIOx = GPIOx;
	RS485->GPIO_Pin = GPIO_Pin;
	
	/* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStruct;
	if(GPIOx == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	else if(GPIOx == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	
  GPIO_InitStruct.Pin = GPIO_Pin;//设定对应引脚IO编号
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//设定对应引脚IO为输出模式
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//设对应引脚IO操作速度
	GPIO_InitStruct.Pull = GPIO_NOPULL;//内部浮空
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);//初始化对应引脚IO  
}

/*-----------------------------------------------------------
函数功能: RS485芯片RD引脚电平设置
输入参数: None
返 回 值: None
说    明: RD引脚低电平时 芯片处于接收数据状态		
					RD引脚高电平时 芯片处于发送数据状态
					当不使用485芯片收发数据时，为防止485芯片占用串口，需要将RD引脚设为高电平状态
 -----------------------------------------------------------*/
void RS485_RD(RS485_Struct* RS485, uint8_t PinState)
{
	if(PinState) HAL_GPIO_WritePin(RS485->GPIOx, RS485->GPIO_Pin, GPIO_PIN_SET);
	else 				 HAL_GPIO_WritePin(RS485->GPIOx, RS485->GPIO_Pin, GPIO_PIN_RESET);
}
