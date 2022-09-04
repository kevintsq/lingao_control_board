#include "spi.h"
#include "ShareWare.h"

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

__IO uint8_t *SPIpTxData[100];
__IO uint8_t *SPIpRxData[100];

void SPI1_CSX_GPIO_Init(void)//SPI1片选IO初始化
{
	/* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	
  GPIO_InitStruct.Pin = GPIO_PIN_4;//设定对应引脚IO编号
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//设定对应引脚IO为输出模式
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//设对应引脚IO操作速度
	GPIO_InitStruct.Pull = GPIO_NOPULL;//内部浮空
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);//初始化对应引脚IO  
}

/*-----------------------------------------------------------
函数功能: SPI1初始化函数
输入参数: None
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void MX_SPI1_Init(void)
{
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;//2条线全双工通信
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;//8位数据
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;//时钟极性，时钟空闲时为低电平
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;//时钟相位，在时钟的第一个跳变沿（上升沿或下降沿）进行数据采样
  hspi1.Init.NSS = SPI_NSS_SOFT;//配置spi在master下，NSS作为普通IO，由用户自己写代码控制片选，可以1主多从
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;//波特率预分频器
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;// MSB 先行（高位数据在前）， LSB先行（低位数据在前）
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;//禁用TI模式
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;//禁用CRC校验
  hspi1.Init.CRCPolynomial = 10;//这是 SPI 的 CRC 校验中的多项式，若我们使用 CRC 校验时，就使用这个成员的参数（多项式）来计算 CRC 的值
  HAL_SPI_Init(&hspi1);
	
//	__HAL_SPI_ENABLE_IT(&hspi1, SPI_IT_TXE);
//	__HAL_SPI_ENABLE_IT(&hspi1, SPI_IT_RXNE);
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance==SPI1)
	{
//		IndicatorDeviceControl(&Buzzer, 2, 50);//蜂鸣器控制函数
		if(HAL_SPI_GetState(hspi) == HAL_SPI_STATE_READY)
		{
			
		}
	}
}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	IndicatorDeviceControl(&Buzzer, 2, 50);//蜂鸣器控制函数
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	IndicatorDeviceControl(&Buzzer, 2, 50);//蜂鸣器控制函数
}
