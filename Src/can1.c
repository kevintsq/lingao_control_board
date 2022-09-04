#include "can1.h"
#include "ShareWare.h"

CAN_HandleTypeDef hcan1;
CAN_RxHeaderTypeDef RxmessageCan1;
CAN_TxHeaderTypeDef TxmessageCan1;
__IO uint32_t CAN1_TxMailbox;//�洢������Ϣ��Tx�����
__IO uint8_t TxmessageCan1_Buf[8];
__IO uint8_t RxmessageCan1_Buf[8];


/*-----------------------------------------------------------
��������: CAN1 TX��Ϣ����
�������: None
�� �� ֵ: None
˵    ��: None
 -----------------------------------------------------------*/
void CAN1_SetTxMsg(void)
{						 
  TxmessageCan1.StdId=0x601;					   //ʹ�õı�׼��ʶ��ID
  TxmessageCan1.IDE=CAN_ID_STD;					 //��׼ģʽ
  TxmessageCan1.RTR=CAN_RTR_DATA;				 //���͵�������
  TxmessageCan1.DLC=8;							     //���ݳ���Ϊ8�ֽ�
}

/*-----------------------------------------------------------
��������: CAN1��ʼ������
�������: None
�� �� ֵ: None
˵    ��: None
 -----------------------------------------------------------*/
void MX_CAN1_Init(void)
{
	CAN_FilterTypeDef  sFilterConfig;
	
	hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;					// BTR-BRP �����ʷ�Ƶ�� 3��1000Kbps��6��500Kbps
  hcan1.Init.Mode = CAN_MODE_NORMAL;// ��������ģʽ
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;// BTR-SJW ����ͬ����Ծ��� 1��ʱ�䵥Ԫ
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;// BTR-TS1 ʱ���1 ռ����7��ʱ�䵥Ԫ
  hcan1.Init.TimeSeg2 = CAN_BS2_6TQ;// BTR-TS2 ʱ���2 ռ����6��ʱ�䵥Ԫ
  hcan1.Init.TimeTriggeredMode = DISABLE;// MCR-TTCM  �ر�ʱ�䴥��ͨ��ģʽʹ��
  hcan1.Init.AutoBusOff = ENABLE;// MCR-ABOM  �Զ����߹��� 
  hcan1.Init.AutoWakeUp = ENABLE;// MCR-AWUM  ʹ���Զ�����ģʽ
  hcan1.Init.AutoRetransmission = DISABLE;// MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
  hcan1.Init.ReceiveFifoLocked = DISABLE;// MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б��� 
  hcan1.Init.TransmitFifoPriority = ENABLE;// MCR-TXFP  ����FIFO���ȼ� ENABLE-�Դ��뷢�������˳����з��ͣ�DISABLE-�Ա���ID�����ȼ�����
  HAL_CAN_Init(&hcan1);
	
	/*CAN��������ʼ��*/
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;  //�����ڱ�ʶ������λģʽ
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; //������λ��Ϊ����32λ��
  /* ʹ�ܱ��ı�ʾ�����������ձ�ʾ�������ݽ��бȶԹ��ˣ���չID�������µľ����������ǵĻ��������FIFO0�� */
  
//  sFilterConfig.FilterIdHigh         = (((uint32_t)0x1314<<3)&0xFFFF0000)>>16;				//Ҫ���˵�ID��λ 
//  sFilterConfig.FilterIdLow          = (((uint32_t)0x1314<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF; //Ҫ���˵�ID��λ 
//  sFilterConfig.FilterMaskIdHigh     = 0xFFFF;			//��������16λÿλ����ƥ��
//  sFilterConfig.FilterMaskIdLow      = 0xFFFF;			//��������16λÿλ����ƥ��
	
	sFilterConfig.FilterIdHigh         = 0x0000;				//Ҫ���˵�ID��λ 
  sFilterConfig.FilterIdLow          = 0x0000; 				//Ҫ���˵�ID��λ 
  sFilterConfig.FilterMaskIdHigh     = 0x0000;			//��������16λÿλ����ƥ��
  sFilterConfig.FilterMaskIdLow      = 0x0000;			//��������16λÿλ����ƥ��
	
  sFilterConfig.FilterFIFOAssignment = 0;           //��������������FIFO 0

  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterActivation = ENABLE;          //ʹ�ܹ�����
	sFilterConfig.SlaveStartFilterBank = 1;
  HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
	
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);//FIFI0 ��Ϣ�����ж�
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);//FIFI1 ��Ϣ�����ж�
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY);//����������ж�
}


/*-----------------------------------------------------------
��������: CAN��������жϻص�������
�������: CAN�������ָ��
�� �� ֵ: None
˵    ��: None
 -----------------------------------------------------------*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == CAN1)
	{
		if(HAL_CAN_GetState(hcan) != RESET)
		{
			HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxmessageCan1, (uint8_t*)RxmessageCan1_Buf);
			
			
			HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
		}
	}
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == CAN1)
	{
		if(HAL_CAN_GetState(hcan) != RESET)
		{			
			
		}		
	}
}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
//	LED_Green_Control(1,50);//��ɫLED���ƺ���
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{
//	LED_Green_Control(2,100);
}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{
//	LED_Green_Control(2,100);
}
