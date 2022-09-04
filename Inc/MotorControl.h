#ifndef __MOTORCONTROL_H
#define __MOTORCONTROL_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
#define MotorPWM_Max 2000 //PWM���ֵ
#define MotorPWM_Min 0 		//PWM��Сֵ
#define Motor1_PWM 	TIM8->CCR4 //���Ƶ��1 PWM���
#define	Motor2_PWM 	TIM8->CCR1 //���Ƶ��2 PWM���
#define	Motor3_PWM 	TIM8->CCR3 //���Ƶ��3 PWM���
#define	Motor4_PWM 	TIM8->CCR2 //���Ƶ��4 PWM���

void Motor1_GPIO_Init(void);//�������1 IO��ʼ������
void Motor2_GPIO_Init(void);//�������2 IO��ʼ������
void Motor3_GPIO_Init(void);//�������3 IO��ʼ������
void Motor4_GPIO_Init(void);//�������4 IO��ʼ������

void Motor1_Forward(void);//���1����
void Motor1_Reverse(void);//���1��ת
void Motor2_Forward(void);//���2����
void Motor2_Reverse(void);//���2��ת
void Motor3_Forward(void);//���3����
void Motor3_Reverse(void);//���3��ת
void Motor4_Forward(void);//���4����
void Motor4_Reverse(void);//���4��ת

#ifdef __cplusplus
}
#endif

#endif
