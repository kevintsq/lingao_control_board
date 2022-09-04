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
		//IndicatorDeviceControl(&LED_Red, 2, 100);//��ɫLED���ƺ���
    osDelay(1000);
//		vTaskSuspend(NULL);//���������
  }
}


void task(void)//����ָ�
{
//	BaseType_t YieldRequired;
//	YieldRequired = xTaskResumeFromISR(myTask02Handle);
//	if(YieldRequired == pdTRUE)
//	{
//		portYIELD_FROM_ISR(YieldRequired);//ע��һ�´�ISR���жϺ����вŵ��õģ�Bվ��Ƶ�иú������ڰ����жϺ����е��õ�
//	}			
}

void IndicatorDeviceTask(void const * argument)
{
	taskENTER_CRITICAL();//�����ٽ���
	IndicatorDevice_Init(&Buzzer, GPIOC, GPIO_PIN_13);//��ʾ�豸��ʼ�����ú���
	IndicatorDevice_Init(&LED_Gre, GPIOC, GPIO_PIN_14);//��ʾ�豸��ʼ�����ú���
	IndicatorDevice_Init(&LED_Red, GPIOC, GPIO_PIN_15);//��ʾ�豸��ʼ�����ú���
	taskEXIT_CRITICAL();//�˳��ٽ���
	
	IndicatorDeviceControl(&Buzzer, 2, 50);//���������ƺ���
	IndicatorDeviceControl(&LED_Gre, 2, 50);//��ɫLED���ƺ���
	IndicatorDeviceControl(&LED_Red, 2, 50);//��ɫLED���ƺ���
	
  for(;;)
  {
		osDelay(1);
		IndicatorDeviceLoop(&Buzzer);//ָʾ�豸ѭ������
		IndicatorDeviceLoop(&LED_Gre);//ָʾ�豸ѭ������
		IndicatorDeviceLoop(&LED_Red);//ָʾ�豸ѭ������   
  }
}


void IMUTask(void const * argument)
{
	taskENTER_CRITICAL();//�����ٽ���
	MX_SPI1_Init();//SPI1��ʼ������
	SPI1_CSX_GPIO_Init();//SPI1ƬѡIO��ʼ��
	taskEXIT_CRITICAL();//�˳��ٽ���
	
	while(!ICM42605_Init())//�ȴ���������ʼ���ɹ�
	{
		osDelay(100); 		
		IndicatorDeviceControl(&LED_Red, 1, 100);//��ɫLED���ƺ���
		IndicatorDeviceControl(&Buzzer, 1, 100);//���������ƺ���
	}
	
	for(;;)
	{
		osDelay(1);
		ICM42605_Read_FIFO(&ICM42605);//��ICM42605 FIFOֵ		
	}
}

void KinematicsTask(void const * argument)
{
	taskENTER_CRITICAL();//�����ٽ���
	MX_TIM8_Init();//TIM8-PWM��ʼ������
	MX_TIM2_Init();//TIM2-������ģʽ��ʼ��
	MX_TIM3_Init();//TIM3-������ģʽ��ʼ��
	MX_TIM4_Init();//TIM4-������ģʽ��ʼ��
	MX_TIM5_Init();//TIM5-������ģʽ��ʼ��
	Motor1_GPIO_Init();//�������1 IO��ʼ������
  Motor2_GPIO_Init();//�������2 IO��ʼ������
  Motor3_GPIO_Init();//�������3 IO��ʼ������
  Motor4_GPIO_Init();//�������4 IO��ʼ������
	Encoder_Struct_Init(&Encoder_M1);//��ʼ���������ṹ�����
	Encoder_Struct_Init(&Encoder_M2);//��ʼ���������ṹ�����
	Encoder_Struct_Init(&Encoder_M3);//��ʼ���������ṹ�����
	Encoder_Struct_Init(&Encoder_M4);//��ʼ���������ṹ�����
	LPF_Struct_Init(&LPF_RPM1, 0.03);//��ͨ�˲��ṹ�������ʼ��
	LPF_Struct_Init(&LPF_RPM2, 0.03);//��ͨ�˲��ṹ�������ʼ��
	LPF_Struct_Init(&LPF_RPM3, 0.03);//��ͨ�˲��ṹ�������ʼ��
	LPF_Struct_Init(&LPF_RPM4, 0.03);//��ͨ�˲��ṹ�������ʼ��
	taskEXIT_CRITICAL();//�˳��ٽ���
	
	for(;;)
	{
		osDelay(5);
		Kinematics_4WD_CalculateRPM(&Kinematics_Inverse);//4WD�˶�ѧ��⺯��
		/*-------�ԡ�Ŀ��ת�١�������ֵ-------*/	
		Kinematics_Inverse.M1_RPM = Constrain(Kinematics_Inverse.M1_RPM, -RPM_MAX, RPM_MAX);
		Kinematics_Inverse.M2_RPM = Constrain(Kinematics_Inverse.M2_RPM, -RPM_MAX, RPM_MAX);
		Kinematics_Inverse.M3_RPM = Constrain(Kinematics_Inverse.M3_RPM, -RPM_MAX, RPM_MAX);
		Kinematics_Inverse.M4_RPM = Constrain(Kinematics_Inverse.M4_RPM, -RPM_MAX, RPM_MAX);
				
		LPF_RPM1.SampleValue = Kinematics_Inverse.M1_RPM;//ͨ������ת��ֵ����ͨ�˲����ṹ���еĲɼ�ֵ
		VelControl.M1_SetRPM = LowPassFilter(&LPF_RPM1);//ת��ֵ������ͨ�˲�������ֵ�����ƽ��			
		LPF_RPM2.SampleValue = Kinematics_Inverse.M2_RPM;//ͨ������ת��ֵ����ͨ�˲����ṹ���еĲɼ�ֵ
		VelControl.M2_SetRPM = LowPassFilter(&LPF_RPM2);//ת��ֵ������ͨ�˲�������ֵ�����ƽ��				
		LPF_RPM3.SampleValue = Kinematics_Inverse.M3_RPM;//ͨ������ת��ֵ����ͨ�˲����ṹ���еĲɼ�ֵ
		VelControl.M3_SetRPM = LowPassFilter(&LPF_RPM3);//ת��ֵ������ͨ�˲�������ֵ�����ƽ��							
		LPF_RPM4.SampleValue = Kinematics_Inverse.M4_RPM;//ͨ������ת��ֵ����ͨ�˲����ṹ���еĲɼ�ֵ
		VelControl.M4_SetRPM = LowPassFilter(&LPF_RPM4);//ת��ֵ������ͨ�˲�������ֵ�����ƽ��	
		
		VelocityControl_4WD(&VelControl);//4WD�ٶȱջ����ƺ���
			
		/*----------------------���嵱ǰ���ٶȽ��ٶȲ����˲�----------------------*/
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
			Kinematics_4WD_GetVelocities(&Kinematics_Forward);//4WD�˶�ѧ���⺯��
			i = Kinematics_Forward.M1_RPM = Kinematics_Forward.M2_RPM = Kinematics_Forward.M3_RPM = Kinematics_Forward.M4_RPM = 0;//��0
		}	
	}
}

void MotionControlTask(void const * argument)
{
	taskENTER_CRITICAL();//�����ٽ���
	MX_UART4_Init();//UART4��ʼ������
	taskEXIT_CRITICAL();//�˳��ٽ���
	
	for(;;)
	{
		osDelay(10);
		if(RC.ConnectState)//�ж�ң��������ջ��Ƿ�������ͨ��״̬
		{
			IndicatorDeviceControl(&LED_Gre, 1, 50);//��ɫLED���ƺ���			
			//if(RC.Switch == RC_DOWN) ICM42605.Yaw = 0;			
			Kinematics_Inverse.Linear_X = RC.Left_Y * 0.8f;//���Yҡ�˿��Ƴ���X�����ٶ�
			Kinematics_Inverse.Angular_Z = RC.Right_X * 2.0f;//�Ҳ�Xҡ�˿��Ƴ���Z����ٶ�	
			DataCom_RX.HeartbeatTime = 0;//������ʱ��
		}
		else if(DataCom_RX.HeartbeatTime)//�����������ά������
		{
			Kinematics_Inverse.Linear_X = DataCom_RX.Linear_X;
			Kinematics_Inverse.Angular_Z = DataCom_RX.Angular_Z;
			DataCom_RX.HeartbeatTime--;
		}
		else//������ʱɲ��
		{
			DataCom_RX.Linear_X =  DataCom_RX.Angular_Z = 0;									
			Kinematics_Inverse.Linear_X = 0;//���Ƴ������ٶ� m/s
			Kinematics_Inverse.Angular_Z = 0;//���Ƴ�����ٶ� rad/s			
		}		
	}
}

void SerialInterfaceTask(void const * argument)
{
	taskENTER_CRITICAL();//�����ٽ���	
	MX_USART2_Init();//USART2��ʼ������
	MastMessage_Queue = xQueueCreate(100, sizeof(uint8_t));//����������Ϣ���У����������100��uint8_t��С
	ParseData_Init(&ParseData_Mast, 30);//�������ݲ�����ʼ��
	taskEXIT_CRITICAL();//�˳��ٽ���
	
	for(;;)
	{		
		osDelay(1);	
		if(MastMessage_Queue != NULL)//��Ϣ����MastMessage_Queue�����ɹ�
		{
			while(!ParseData_Mast.Flag)//�жϽ������������Ƿ��Ѵ���
			{
				uint8_t Data;
				if(xQueueReceive(MastMessage_Queue, &Data, 0) == pdTRUE)//����������Ϣ�����гɹ���ȡ��������ִ��
				{
					ParseDataFunction(&ParseData_Mast, Data);//��������
				}
			}
		}
		
		if(HAL_UART_GetState(&huart2) != HAL_UART_STATE_BUSY_TX)//���⴮�ڷ���δ�����ִ�д��ڷ���
		{				
			if(ParseData_Mast.Flag)//��������һ֡���ݣ������
			{
				IndicatorDeviceControl(&LED_Gre, 1, 10);//��ɫLED���ƺ���				
				DataCom_RX_Function(&DataCom_RX, (uint8_t*)ParseData_Mast.Buff);//���ݽ��սӿ�
				ParseData_Mast.Flag = 0;//���ݽ���״̬��־λ��0
			}			
		}
	}
}

void BMSTask(void const * argument)
{
	taskENTER_CRITICAL();//�����ٽ���	
	MX_ADC1_Init();//ADC1��ʼ������
	Battery_Init(&Battery, 0.3f);//���״̬��ʼ������
	taskEXIT_CRITICAL();//�˳��ٽ���
	
	for(;;)
	{
		osDelay(500);//��ʱ��������ŷ������Battery.Voltage����nan
		UpdateBatteryInfor(&Battery, (uint16_t*)ADC1_DMA_Buff);//���µ��״̬��Ϣ		
//		dma_printf("%f", ICM42605.Yaw);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
