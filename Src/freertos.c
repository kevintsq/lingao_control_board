/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "ShareWare.h"

osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId IndicatorDeviceHandle;
osThreadId IMUHandle;
osThreadId KinematicsHandle;
osThreadId MotionControlHandle;
osThreadId BMSHandle;
osThreadId SerialInterfaceHandle;



void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void IndicatorDeviceTask(void const * argument);
void IMUTask(void const * argument);
void KinematicsTask(void const * argument);
void MotionControlTask(void const * argument);
void BMSTask(void const * argument);
void SerialInterfaceTask(void const * argument);

void MX_FREERTOS_Init(void);

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) 
{

//  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
//  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

//  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 20);
//  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);
	
	osThreadDef(IndicatorDevice, IndicatorDeviceTask, osPriorityNormal, 0, 50);
  IndicatorDeviceHandle = osThreadCreate(osThread(IndicatorDevice), NULL);
	
	osThreadDef(IMU, IMUTask, osPriorityAboveNormal, 0, 120);
  IMUHandle = osThreadCreate(osThread(IMU), NULL);
	
	osThreadDef(Kinematics, KinematicsTask, osPriorityNormal, 0, 100);
  KinematicsHandle = osThreadCreate(osThread(Kinematics), NULL);
	
	osThreadDef(MotionControl, MotionControlTask, osPriorityNormal, 0, 100);
  MotionControlHandle = osThreadCreate(osThread(MotionControl), NULL);
	
	osThreadDef(SerialInterface, SerialInterfaceTask, osPriorityNormal, 0, 500);
  SerialInterfaceHandle = osThreadCreate(osThread(SerialInterface), NULL);
	
	osThreadDef(BMS, BMSTask, osPriorityNormal, 0, 100);
  BMSHandle = osThreadCreate(osThread(BMS), NULL);
}


void StartDefaultTask(void const * argument)
{
  for(;;)
  {

    osDelay(50);
  }
}


void StartTask02(void const * argument)
{
  for(;;)
  {
		//IndicatorDeviceControl(&LED_Red, 2, 100);//绿色LED控制函数
    osDelay(1000);
//		vTaskSuspend(NULL);//挂起该任务
  }
}


void task(void)//任务恢复
{
//	BaseType_t YieldRequired;
//	YieldRequired = xTaskResumeFromISR(myTask02Handle);
//	if(YieldRequired == pdTRUE)
//	{
//		portYIELD_FROM_ISR(YieldRequired);//注意一下带ISR是中断函数中才调用的，B站视频中该函数是在按键中断函数中调用的
//	}			
}

void IndicatorDeviceTask(void const * argument)
{
	taskENTER_CRITICAL();//进入临界区
	IndicatorDevice_Init(&Buzzer, GPIOC, GPIO_PIN_13);//提示设备初始化配置函数
	IndicatorDevice_Init(&LED_Gre, GPIOC, GPIO_PIN_14);//提示设备初始化配置函数
	IndicatorDevice_Init(&LED_Red, GPIOC, GPIO_PIN_15);//提示设备初始化配置函数
	taskEXIT_CRITICAL();//退出临界区
	
	IndicatorDeviceControl(&Buzzer, 2, 50);//蜂鸣器控制函数
	IndicatorDeviceControl(&LED_Gre, 2, 50);//绿色LED控制函数
	IndicatorDeviceControl(&LED_Red, 2, 50);//绿色LED控制函数
	
  for(;;)
  {
		osDelay(1);
		IndicatorDeviceLoop(&Buzzer);//指示设备循环函数
		IndicatorDeviceLoop(&LED_Gre);//指示设备循环函数
		IndicatorDeviceLoop(&LED_Red);//指示设备循环函数   
  }
}


void IMUTask(void const * argument)
{
	taskENTER_CRITICAL();//进入临界区
	MX_SPI1_Init();//SPI1初始化函数
	SPI1_CSX_GPIO_Init();//SPI1片选IO初始化
	taskEXIT_CRITICAL();//退出临界区
	
	while(!ICM42605_Init())//等待传感器初始化成功
	{
		osDelay(100); 		
		IndicatorDeviceControl(&LED_Red, 1, 100);//红色LED控制函数
		IndicatorDeviceControl(&Buzzer, 1, 100);//蜂鸣器控制函数
	}
	
	for(;;)
	{
		osDelay(1);
		ICM42605_Read_FIFO(&ICM42605);//读ICM42605 FIFO值		
	}
}

void KinematicsTask(void const * argument)
{
	taskENTER_CRITICAL();//进入临界区
	MX_TIM8_Init();//TIM8-PWM初始化函数
	MX_TIM2_Init();//TIM2-编码器模式初始化
	MX_TIM3_Init();//TIM3-编码器模式初始化
	MX_TIM4_Init();//TIM4-编码器模式初始化
	MX_TIM5_Init();//TIM5-编码器模式初始化
	Motor1_GPIO_Init();//电机驱动1 IO初始化函数
  Motor2_GPIO_Init();//电机驱动2 IO初始化函数
  Motor3_GPIO_Init();//电机驱动3 IO初始化函数
  Motor4_GPIO_Init();//电机驱动4 IO初始化函数
	Encoder_Struct_Init(&Encoder_M1);//初始化编码器结构体参数
	Encoder_Struct_Init(&Encoder_M2);//初始化编码器结构体参数
	Encoder_Struct_Init(&Encoder_M3);//初始化编码器结构体参数
	Encoder_Struct_Init(&Encoder_M4);//初始化编码器结构体参数
	LPF_Struct_Init(&LPF_RPM1, 0.03);//低通滤波结构体参数初始化
	LPF_Struct_Init(&LPF_RPM2, 0.03);//低通滤波结构体参数初始化
	LPF_Struct_Init(&LPF_RPM3, 0.03);//低通滤波结构体参数初始化
	LPF_Struct_Init(&LPF_RPM4, 0.03);//低通滤波结构体参数初始化
	taskEXIT_CRITICAL();//退出临界区
	
	for(;;)
	{
		osDelay(5);
		Kinematics_4WD_CalculateRPM(&Kinematics_Inverse);//4WD运动学逆解函数
		/*-------对“目标转速“进行限值-------*/	
		Kinematics_Inverse.M1_RPM = Constrain(Kinematics_Inverse.M1_RPM, -RPM_MAX, RPM_MAX);
		Kinematics_Inverse.M2_RPM = Constrain(Kinematics_Inverse.M2_RPM, -RPM_MAX, RPM_MAX);
		Kinematics_Inverse.M3_RPM = Constrain(Kinematics_Inverse.M3_RPM, -RPM_MAX, RPM_MAX);
		Kinematics_Inverse.M4_RPM = Constrain(Kinematics_Inverse.M4_RPM, -RPM_MAX, RPM_MAX);
				
		LPF_RPM1.SampleValue = Kinematics_Inverse.M1_RPM;//通过采样转速值给低通滤波器结构体中的采集值
		VelControl.M1_SetRPM = LowPassFilter(&LPF_RPM1);//转速值经过低通滤波器后数值会更加平滑			
		LPF_RPM2.SampleValue = Kinematics_Inverse.M2_RPM;//通过采样转速值给低通滤波器结构体中的采集值
		VelControl.M2_SetRPM = LowPassFilter(&LPF_RPM2);//转速值经过低通滤波器后数值会更加平滑				
		LPF_RPM3.SampleValue = Kinematics_Inverse.M3_RPM;//通过采样转速值给低通滤波器结构体中的采集值
		VelControl.M3_SetRPM = LowPassFilter(&LPF_RPM3);//转速值经过低通滤波器后数值会更加平滑							
		LPF_RPM4.SampleValue = Kinematics_Inverse.M4_RPM;//通过采样转速值给低通滤波器结构体中的采集值
		VelControl.M4_SetRPM = LowPassFilter(&LPF_RPM4);//转速值经过低通滤波器后数值会更加平滑	
		
		VelocityControl_4WD(&VelControl);//4WD速度闭环控制函数
			
		/*----------------------车体当前线速度角速度采样滤波----------------------*/
		static uint8_t i = 0;
		i++;
		Kinematics_Forward.M1_RPM += VelControl.M1_RPM;
		Kinematics_Forward.M2_RPM += VelControl.M2_RPM;
		Kinematics_Forward.M3_RPM += VelControl.M3_RPM;
		Kinematics_Forward.M4_RPM += VelControl.M4_RPM;
		
		if(i > 1) 
		{
			Kinematics_Forward.M1_RPM = (float)Kinematics_Forward.M1_RPM / i;
			Kinematics_Forward.M2_RPM = (float)Kinematics_Forward.M2_RPM / i;
			Kinematics_Forward.M3_RPM = (float)Kinematics_Forward.M3_RPM / i;
			Kinematics_Forward.M4_RPM = (float)Kinematics_Forward.M4_RPM / i;
			Kinematics_4WD_GetVelocities(&Kinematics_Forward);//4WD运动学正解函数
			i = Kinematics_Forward.M1_RPM = Kinematics_Forward.M2_RPM = Kinematics_Forward.M3_RPM = Kinematics_Forward.M4_RPM = 0;//清0
		}	
	}
}

void MotionControlTask(void const * argument)
{
	taskENTER_CRITICAL();//进入临界区
	MX_UART4_Init();//UART4初始化函数
	taskEXIT_CRITICAL();//退出临界区
	
	for(;;)
	{
		osDelay(10);
		if(RC.ConnectState)//判断遥控器与接收机是否处于正常通信状态
		{
			IndicatorDeviceControl(&LED_Gre, 1, 50);//绿色LED控制函数			
			//if(RC.Switch == RC_DOWN) ICM42605.Yaw = 0;			
			Kinematics_Inverse.Linear_X = RC.Left_Y * 0.8f;//左侧Y摇杆控制车体X轴线速度
			Kinematics_Inverse.Angular_Z = RC.Right_X * 2.0f;//右侧X摇杆控制车体Z轴角速度	
			DataCom_RX.HeartbeatTime = 0;//心跳包时间
		}
		else if(DataCom_RX.HeartbeatTime)//如果心跳周期维持正常
		{
			Kinematics_Inverse.Linear_X = DataCom_RX.Linear_X;
			Kinematics_Inverse.Angular_Z = DataCom_RX.Angular_Z;
			DataCom_RX.HeartbeatTime--;
		}
		else//心跳超时刹车
		{
			DataCom_RX.Linear_X =  DataCom_RX.Angular_Z = 0;									
			Kinematics_Inverse.Linear_X = 0;//控制车体线速度 m/s
			Kinematics_Inverse.Angular_Z = 0;//控制车体角速度 rad/s			
		}		
	}
}

void SerialInterfaceTask(void const * argument)
{
	taskENTER_CRITICAL();//进入临界区	
	MX_USART2_Init();//USART2初始化函数
	MastMessage_Queue = xQueueCreate(100, sizeof(uint8_t));//创建主机消息队列，队列项长度是100个uint8_t大小
	ParseData_Init(&ParseData_Mast, 30);//解析数据参数初始化
	taskEXIT_CRITICAL();//退出临界区
	
	for(;;)
	{		
		osDelay(1);	
		if(MastMessage_Queue != NULL)//消息队列MastMessage_Queue创建成功
		{
			while(!ParseData_Mast.Flag)//判断解析出的数据是否已处理
			{
				uint8_t Data;
				if(xQueueReceive(MastMessage_Queue, &Data, 0) == pdTRUE)//若从主机消息队列中成功获取到数据则执行
				{
					ParseDataFunction(&ParseData_Mast, Data);//解析数据
				}
			}
		}
		
		if(HAL_UART_GetState(&huart2) != HAL_UART_STATE_BUSY_TX)//避免串口发送未完成又执行串口发送
		{				
			if(ParseData_Mast.Flag)//若解析出一帧数据，则进入
			{
				IndicatorDeviceControl(&LED_Gre, 1, 10);//绿色LED控制函数				
				DataCom_RX_Function(&DataCom_RX, (uint8_t*)ParseData_Mast.Buff);//数据接收接口
				ParseData_Mast.Flag = 0;//数据解析状态标志位清0
			}			
		}
	}
}

void BMSTask(void const * argument)
{
	taskENTER_CRITICAL();//进入临界区	
	MX_ADC1_Init();//ADC1初始化函数
	Battery_Init(&Battery, 0.3f);//电池状态初始化函数
	taskEXIT_CRITICAL();//退出临界区
	
	for(;;)
	{
		osDelay(500);//延时函数必须放方面否则Battery.Voltage等于nan
		UpdateBatteryInfor(&Battery, (uint16_t*)ADC1_DMA_Buff);//更新电池状态信息		
//		dma_printf("%f", ICM42605.Yaw);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
