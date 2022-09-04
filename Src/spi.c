#include "spi.h"
#include "ShareWare.h"

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

__IO uint8_t *SPIpTxData[100];
__IO uint8_t *SPIpRxData[100];

void SPI1_CSX_GPIO_Init(void)//SPI1ƬѡIO��ʼ��
{
	/* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
  GPIO_InitStruct.Pin = GPIO_PIN_4;//�趨��Ӧ����IO���
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//���Ӧ����IO�����ٶ�
	GPIO_InitStruct.Pull = GPIO_NOPULL;//�ڲ�����
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);//��ʼ����Ӧ����IO  
}

/*-----------------------------------------------------------
��������: SPI1��ʼ������
�������: None
�� �� ֵ: None
˵    ��: None
 -----------------------------------------------------------*/
void MX_SPI1_Init(void)
{
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;//2����ȫ˫��ͨ��
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;//8λ����
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;//ʱ�Ӽ��ԣ�ʱ�ӿ���ʱΪ�͵�ƽ
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;//ʱ����λ����ʱ�ӵĵ�һ�������أ������ػ��½��أ��������ݲ���
  hspi1.Init.NSS = SPI_NSS_SOFT;//����spi��master�£�NSS��Ϊ��ͨIO�����û��Լ�д�������Ƭѡ������1�����
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;//������Ԥ��Ƶ��
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;// MSB ���У���λ������ǰ���� LSB���У���λ������ǰ��
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;//����TIģʽ
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;//����CRCУ��
  hspi1.Init.CRCPolynomial = 10;//���� SPI �� CRC У���еĶ���ʽ��������ʹ�� CRC У��ʱ����ʹ�������Ա�Ĳ���������ʽ�������� CRC ��ֵ
  HAL_SPI_Init(&hspi1);
	
//	__HAL_SPI_ENABLE_IT(&hspi1, SPI_IT_TXE);
//	__HAL_SPI_ENABLE_IT(&hspi1, SPI_IT_RXNE);
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance==SPI1)
	{
//		IndicatorDeviceControl(&Buzzer, 2, 50);//���������ƺ���
		if(HAL_SPI_GetState(hspi) == HAL_SPI_STATE_READY)
		{
			
		}
	}
}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	IndicatorDeviceControl(&Buzzer, 2, 50);//���������ƺ���
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	IndicatorDeviceControl(&Buzzer, 2, 50);//���������ƺ���
}
