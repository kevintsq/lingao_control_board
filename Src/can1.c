#include "can1.h"
#include "ShareWare.h"

CAN_HandleTypeDef hcan1;
CAN_RxHeaderTypeDef RxmessageCan1;
CAN_TxHeaderTypeDef TxmessageCan1;
__IO uint32_t CAN1_TxMailbox;//存储发送消息的Tx邮箱号
__IO uint8_t TxmessageCan1_Buf[8];
__IO uint8_t RxmessageCan1_Buf[8];


/*-----------------------------------------------------------
函数功能: CAN1 TX消息设置
输入参数: None
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void CAN1_SetTxMsg(void)
{						 
  TxmessageCan1.StdId=0x601;					   //使用的标准标识符ID
  TxmessageCan1.IDE=CAN_ID_STD;					 //标准模式
  TxmessageCan1.RTR=CAN_RTR_DATA;				 //发送的是数据
  TxmessageCan1.DLC=8;							     //数据长度为8字节
}

/*-----------------------------------------------------------
函数功能: CAN1初始化函数
输入参数: None
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void MX_CAN1_Init(void)
{
	CAN_FilterTypeDef  sFilterConfig;
	
	hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;					// BTR-BRP 波特率分频器 3：1000Kbps，6：500Kbps
  hcan1.Init.Mode = CAN_MODE_NORMAL;// 正常工作模式
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;// BTR-SJW 重新同步跳跃宽度 1个时间单元
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;// BTR-TS1 时间段1 占用了7个时间单元
  hcan1.Init.TimeSeg2 = CAN_BS2_6TQ;// BTR-TS2 时间段2 占用了6个时间单元
  hcan1.Init.TimeTriggeredMode = DISABLE;// MCR-TTCM  关闭时间触发通信模式使能
  hcan1.Init.AutoBusOff = ENABLE;// MCR-ABOM  自动离线管理 
  hcan1.Init.AutoWakeUp = ENABLE;// MCR-AWUM  使用自动唤醒模式
  hcan1.Init.AutoRetransmission = DISABLE;// MCR-NART  禁止报文自动重传	  DISABLE-自动重传
  hcan1.Init.ReceiveFifoLocked = DISABLE;// MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文 
  hcan1.Init.TransmitFifoPriority = ENABLE;// MCR-TXFP  发送FIFO优先级 ENABLE-以存入发送邮箱的顺序进行发送，DISABLE-以报文ID的优先级发送
  HAL_CAN_Init(&hcan1);
	
	/*CAN过滤器初始化*/
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;  //工作在标识符屏蔽位模式
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; //过滤器位宽为单个32位。
  /* 使能报文标示符过滤器按照标示符的内容进行比对过滤，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
  
//  sFilterConfig.FilterIdHigh         = (((uint32_t)0x1314<<3)&0xFFFF0000)>>16;				//要过滤的ID高位 
//  sFilterConfig.FilterIdLow          = (((uint32_t)0x1314<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF; //要过滤的ID低位 
//  sFilterConfig.FilterMaskIdHigh     = 0xFFFF;			//过滤器高16位每位必须匹配
//  sFilterConfig.FilterMaskIdLow      = 0xFFFF;			//过滤器低16位每位必须匹配
	
	sFilterConfig.FilterIdHigh         = 0x0000;				//要过滤的ID高位 
  sFilterConfig.FilterIdLow          = 0x0000; 				//要过滤的ID低位 
  sFilterConfig.FilterMaskIdHigh     = 0x0000;			//过滤器高16位每位必须匹配
  sFilterConfig.FilterMaskIdLow      = 0x0000;			//过滤器低16位每位必须匹配
	
  sFilterConfig.FilterFIFOAssignment = 0;           //过滤器被关联到FIFO 0

  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterActivation = ENABLE;          //使能过滤器
	sFilterConfig.SlaveStartFilterBank = 1;
  HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
	
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);//FIFI0 消息挂起中断
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);//FIFI1 消息挂起中断
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY);//传输邮箱空中断
}


/*-----------------------------------------------------------
函数功能: CAN接收完成中断回调服务函数
输入参数: CAN句柄类型指针
返 回 值: None
说    明: None
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
//	LED_Green_Control(1,50);//绿色LED控制函数
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{
//	LED_Green_Control(2,100);
}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{
//	LED_Green_Control(2,100);
}
