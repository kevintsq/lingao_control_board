#ifndef __CAN1_H
#define __CAN1_H

#ifdef __cplusplus
 extern "C" {
#endif
	
#include "main.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_RxHeaderTypeDef RxmessageCan1;
extern CAN_TxHeaderTypeDef TxmessageCan1;
extern __IO uint32_t CAN1_TxMailbox;//存储发送消息的Tx邮箱号
extern __IO uint8_t TxmessageCan1_Buf[8];
extern __IO uint8_t RxmessageCan1_Buf[8];


void CAN1_SetTxMsg(void);//CAN1 TX消息设置
void MX_CAN1_Init(void);//CAN1初始化函数

#ifdef __cplusplus
}
#endif

#endif
