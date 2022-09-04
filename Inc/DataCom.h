#ifndef __DATACOM_H
#define __DATACOM_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
typedef struct
{	
	__IO float Linear_X; //����Ŀ�����ٶ�ֵ m/s
	__IO float Linear_Y; //����Ŀ�����ٶ�ֵ m/s
	__IO float Angular_Z;//����Ŀ����ٶ�ֵ rad/s
	__IO uint16_t HeartbeatTime;//������ʱ��
}DataCom_RX_Struct;//����Э��ṹ�����


void DataCom_RX_Function(DataCom_RX_Struct *DataCom_RX, uint8_t *Buff);//�������ݽӿ�
	
#ifdef __cplusplus
}
#endif

#endif
