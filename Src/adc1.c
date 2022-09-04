#include "adc1.h"
#include "ShareWare.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

__IO uint16_t ADC1_DMA_Buff[ADC1_DMA_BuffLEN];//ADC1�ɼ�����DMA����
/*-----------------------------------------------------------
��������: ADC1��ʼ������
�������: None
�� �� ֵ: None
˵    ��: ����ADC1-IN4��ADC1-IN17�������ɼ��ⲿ��ѹ���ڲ����յ�ѹADCֵ
 -----------------------------------------------------------*/
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;
	
	hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;//ʱ�ӷ�Ƶ
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;//��������
  hadc1.Init.ScanConvMode = ENABLE;//���ͨ���ɼ�
  hadc1.Init.ContinuousConvMode = ENABLE;//�����ɼ�
  hadc1.Init.DiscontinuousConvMode = DISABLE;//���ü��ģʽ
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;//�ⲿ����ģʽNone
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;//���������ʽ
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;//�������Ҷ���
  hadc1.Init.NbrOfConversion = 2;//2������
  hadc1.Init.DMAContinuousRequests = ENABLE;//DMA�����ɼ�
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	HAL_ADC_Init(&hadc1);
	
	sConfig.Channel = ADC_CHANNEL_8;//ͨ��8
  sConfig.Rank = 1;//����˳�����
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;//����ʱ��
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  sConfig.Channel = ADC_CHANNEL_VREFINT;//ͨ��17,�ڲ����յ�ѹ
  sConfig.Rank = 2;//����˳�����
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

		/* ����ADת����ʹ��DMA������ж� */
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1_DMA_Buff, ADC1_DMA_BuffLEN);  
	
	HAL_ADC_Start(&hadc1);//ADC��ʼ�ɼ�ADCֵ
}
