#include "RS485.h"

/*-----------------------------------------------------------
��������: RS485оƬRD��������
�������: None
�� �� ֵ: None
˵    ��: RD���ŵ͵�ƽʱ оƬ���ڽ�������״̬		
					RD���Ÿߵ�ƽʱ оƬ���ڷ�������״̬
					����ʹ��485оƬ�շ�����ʱ��Ϊ��ֹ485оƬռ�ô��ڣ���Ҫ��RD������Ϊ�ߵ�ƽ״̬
 -----------------------------------------------------------*/
void RS485_RD_GPIO_Init(RS485_Struct *RS485, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	RS485->Time = 0;
	RS485->GPIOx = GPIOx;
	RS485->GPIO_Pin = GPIO_Pin;
	
	/* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	if(GPIOx == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	else if(GPIOx == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
  GPIO_InitStruct.Pin = GPIO_Pin;//�趨��Ӧ����IO���
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//���Ӧ����IO�����ٶ�
	GPIO_InitStruct.Pull = GPIO_NOPULL;//�ڲ�����
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);//��ʼ����Ӧ����IO  
}

/*-----------------------------------------------------------
��������: RS485оƬRD���ŵ�ƽ����
�������: None
�� �� ֵ: None
˵    ��: RD���ŵ͵�ƽʱ оƬ���ڽ�������״̬		
					RD���Ÿߵ�ƽʱ оƬ���ڷ�������״̬
					����ʹ��485оƬ�շ�����ʱ��Ϊ��ֹ485оƬռ�ô��ڣ���Ҫ��RD������Ϊ�ߵ�ƽ״̬
 -----------------------------------------------------------*/
void RS485_RD(RS485_Struct* RS485, uint8_t PinState)
{
	if(PinState) HAL_GPIO_WritePin(RS485->GPIOx, RS485->GPIO_Pin, GPIO_PIN_SET);
	else 				 HAL_GPIO_WritePin(RS485->GPIOx, RS485->GPIO_Pin, GPIO_PIN_RESET);
}
