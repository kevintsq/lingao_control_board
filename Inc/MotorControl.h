#ifndef __MOTORCONTROL_H
#define __MOTORCONTROL_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
#define MotorPWM_Max 2000 //PWM最大值
#define MotorPWM_Min 0 		//PWM最小值
#define Motor1_PWM 	TIM8->CCR4 //控制电机1 PWM输出
#define	Motor2_PWM 	TIM8->CCR1 //控制电机2 PWM输出
#define	Motor3_PWM 	TIM8->CCR3 //控制电机3 PWM输出
#define	Motor4_PWM 	TIM8->CCR2 //控制电机4 PWM输出

void Motor1_GPIO_Init(void);//电机驱动1 IO初始化函数
void Motor2_GPIO_Init(void);//电机驱动2 IO初始化函数
void Motor3_GPIO_Init(void);//电机驱动3 IO初始化函数
void Motor4_GPIO_Init(void);//电机驱动4 IO初始化函数

void Motor1_Forward(void);//电机1正传
void Motor1_Reverse(void);//电机1反转
void Motor2_Forward(void);//电机2正传
void Motor2_Reverse(void);//电机2反转
void Motor3_Forward(void);//电机3正传
void Motor3_Reverse(void);//电机3反转
void Motor4_Forward(void);//电机4正传
void Motor4_Reverse(void);//电机4反转

#ifdef __cplusplus
}
#endif

#endif
