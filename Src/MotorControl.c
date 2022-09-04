/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1���������IO��ʼ��
2���������ת����ƺ���
**************************************************************************/
#include "MotorControl.h"

#define M1_ENB(a)	\
						if (a)	\
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,GPIO_PIN_SET);	\
						else		\
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,GPIO_PIN_RESET)	
#define M2_ENB(a)	\
						if (a)	\
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,GPIO_PIN_SET);	\
						else		\
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,GPIO_PIN_RESET)			
#define M3_ENB(a)	\
						if (a)	\
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,GPIO_PIN_SET);	\
						else		\
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,GPIO_PIN_RESET)						
#define M4_ENB(a)	\
						if (a)	\
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3,GPIO_PIN_SET);\
						else		\
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3,GPIO_PIN_RESET)

void Motor1_GPIO_Init(void)//�������1 IO��ʼ������
{
	   /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
	/*�������оƬ��ӦGPIO��������*/
	GPIO_InitStruct.Pin = GPIO_PIN_1;//�趨��Ӧ����IO��� 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//���Ӧ����IO�����ٶ�
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);//�趨��Ӧ���ŵ�ƽ״̬
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);//��ʼ����Ӧ����IO
}

void Motor2_GPIO_Init(void)//�������2 IO��ʼ������
{
	   /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
	/*�������оƬ��ӦGPIO��������*/
	GPIO_InitStruct.Pin = GPIO_PIN_0;//�趨��Ӧ����IO��� 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//���Ӧ����IO�����ٶ�
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);//�趨��Ӧ���ŵ�ƽ״̬
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);//��ʼ����Ӧ����IO
}

void Motor3_GPIO_Init(void)//�������3 IO��ʼ������
{
	   /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
	/*�������оƬ��ӦGPIO��������*/
	GPIO_InitStruct.Pin = GPIO_PIN_2;//�趨��Ӧ����IO��� 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//���Ӧ����IO�����ٶ�
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);//�趨��Ӧ���ŵ�ƽ״̬
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);//��ʼ����Ӧ����IO
}

void Motor4_GPIO_Init(void)//�������4 IO��ʼ������
{
	   /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
	/*�������оƬ��ӦGPIO��������*/
	GPIO_InitStruct.Pin = GPIO_PIN_3;//�趨��Ӧ����IO��� 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//���Ӧ����IO�����ٶ�
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);//�趨��Ӧ���ŵ�ƽ״̬
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);//��ʼ����Ӧ����IO
}

/*--------------------------------*�������--------------------------------*/
void Motor1_Forward(void)//���1����
{
	M1_ENB(1);
}

void Motor1_Reverse(void)//���1��ת
{
	M1_ENB(0);
}

void Motor2_Forward(void)//���2����
{
	M2_ENB(0);
}

void Motor2_Reverse(void)//���2��ת
{
	M2_ENB(1);
}

void Motor3_Forward(void)//���3����
{
	M3_ENB(1);
}

void Motor3_Reverse(void)//���3��ת
{
	M3_ENB(0);
}

void Motor4_Forward(void)//���4����
{
	M4_ENB(0);
}

void Motor4_Reverse(void)//���4��ת
{
	M4_ENB(1);
}
