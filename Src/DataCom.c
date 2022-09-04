/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1�������뷴������Ŀ���ٶ�
2����������ʵʱ�ٶ�
3��������Դ������Ϣ
4����������IMU��Ϣ
5�������豸����Ϣ
**************************************************************************/
#include "DataCom.h"
#include "ShareWare.h"

/*-----------------------------------------------------------
��������: ���ݽ��սӿ�
�������: ���������ַ
�� �� ֵ: None
˵    ��: ��������������֡����ú���ʵ����ֵ����
 -----------------------------------------------------------*/
void DataCom_RX_Function(DataCom_RX_Struct *DataCom_RX, uint8_t *Buff)
{
	DataCom_RX->HeartbeatTime = 100;//������ʱ��
	switch(Buff[3])
	{
		case 1://�����뷴������Ŀ���ٶ�
		{
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[4+i];
			DataCom_RX->Linear_X = floatHex.floatValue;//����X��Ŀ�����ٶ�ֵ m/s
			
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[8+i];
			DataCom_RX->Linear_Y = floatHex.floatValue;//����Y��Ŀ�����ٶ�ֵ m/s
			
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[12+i];
			DataCom_RX->Angular_Z = floatHex.floatValue;//����Z��Ŀ����ٶ�ֵ rad/s
			
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 1;
			Usart2_TX_Buf[3] = 1;
			
			uint16_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[4] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		case 2://��������ʵʱ�ٶ�
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 13;
			Usart2_TX_Buf[3] = 2;
			
			floatHex.floatValue = Kinematics_Forward.Linear_X;//���嵱ǰX�����ٶ� m/s
			Usart2_TX_Buf[4] = floatHex.Hex[3];
			Usart2_TX_Buf[5] = floatHex.Hex[2];
			Usart2_TX_Buf[6] = floatHex.Hex[1];
			Usart2_TX_Buf[7] = floatHex.Hex[0];
			
			floatHex.floatValue = Kinematics_Forward.Linear_Y;//���嵱ǰY�����ٶ� m/s
			Usart2_TX_Buf[8] = floatHex.Hex[3];
			Usart2_TX_Buf[9] = floatHex.Hex[2];
			Usart2_TX_Buf[10] = floatHex.Hex[1];
			Usart2_TX_Buf[11] = floatHex.Hex[0];
			
			floatHex.floatValue = Kinematics_Forward.Angular_Z;//���嵱ǰZ����ٶ� rad/s
			Usart2_TX_Buf[12] = floatHex.Hex[3];
			Usart2_TX_Buf[13] = floatHex.Hex[2];
			Usart2_TX_Buf[14] = floatHex.Hex[1];
			Usart2_TX_Buf[15] = floatHex.Hex[0];
			
			uint16_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[16] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		case 3://������Դ������Ϣ
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 8;
			Usart2_TX_Buf[3] = 3;
			int16_t Voltage = (int16_t)(Battery.Voltage * 100);//��ص�ѹֵ 10mv
			Usart2_TX_Buf[4]= Voltage >> 8;//��ص�ѹֵ 10mv
			Usart2_TX_Buf[5]= Voltage;			
			Usart2_TX_Buf[6]= 0;//��ص���ֵ 10mA
			Usart2_TX_Buf[7]= 0;			
			Usart2_TX_Buf[8]= 0;
			Usart2_TX_Buf[9]= 0;
			Usart2_TX_Buf[10]= Battery.Capacity;//��ص���ֵ %
			
			uint16_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[11] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		case 4://��������IMU��Ϣ
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 37;
			Usart2_TX_Buf[3] = 4;
			
			floatHex.floatValue = ICM42605.Pitch;//������ rad
			Usart2_TX_Buf[4] = floatHex.Hex[3];
			Usart2_TX_Buf[5] = floatHex.Hex[2];
			Usart2_TX_Buf[6] = floatHex.Hex[1];
			Usart2_TX_Buf[7] = floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Yaw;//ƫ���� rad
			Usart2_TX_Buf[8] = floatHex.Hex[3];
			Usart2_TX_Buf[9] = floatHex.Hex[2];
			Usart2_TX_Buf[10] = floatHex.Hex[1];
			Usart2_TX_Buf[11] = floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Roll;//������ rad
			Usart2_TX_Buf[12]= floatHex.Hex[3];
			Usart2_TX_Buf[13]= floatHex.Hex[2];
			Usart2_TX_Buf[14]= floatHex.Hex[1];
			Usart2_TX_Buf[15]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Acc_X;//���ٶȼ�X��
			Usart2_TX_Buf[16]= floatHex.Hex[3];
			Usart2_TX_Buf[17]= floatHex.Hex[2];
			Usart2_TX_Buf[18]= floatHex.Hex[1];
			Usart2_TX_Buf[19]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Acc_Y;//���ٶȼ�Y��
			Usart2_TX_Buf[20]= floatHex.Hex[3];
			Usart2_TX_Buf[21]= floatHex.Hex[2];
			Usart2_TX_Buf[22]= floatHex.Hex[1];
			Usart2_TX_Buf[23]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Acc_Z;//���ٶȼ�Z��
			Usart2_TX_Buf[24]= floatHex.Hex[3];
			Usart2_TX_Buf[25]= floatHex.Hex[2];
			Usart2_TX_Buf[26]= floatHex.Hex[1];
			Usart2_TX_Buf[27]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Gyro_X;//������X��
			Usart2_TX_Buf[28]= floatHex.Hex[3];
			Usart2_TX_Buf[29]= floatHex.Hex[2];
			Usart2_TX_Buf[30]= floatHex.Hex[1];
			Usart2_TX_Buf[31]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Gyro_Y;//������Y��
			Usart2_TX_Buf[32]= floatHex.Hex[3];
			Usart2_TX_Buf[33]= floatHex.Hex[2];
			Usart2_TX_Buf[34]= floatHex.Hex[1];
			Usart2_TX_Buf[35]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Gyro_Z;//������Z��
			Usart2_TX_Buf[36]= floatHex.Hex[3];
			Usart2_TX_Buf[37]= floatHex.Hex[2];
			Usart2_TX_Buf[38]= floatHex.Hex[1];
			Usart2_TX_Buf[39]= floatHex.Hex[0];
			
			uint16_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[40] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		case 255://�����豸����Ϣ
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 6;
			Usart2_TX_Buf[3] = 0xFF;
			
			Usart2_TX_Buf[4] = 22;//Э��汾
			Usart2_TX_Buf[5] = HAL_GetUIDw0() >> 24;//�豸��
			Usart2_TX_Buf[6] = HAL_GetUIDw0() >> 16;
			Usart2_TX_Buf[7] = HAL_GetUIDw0() >> 8;			
			Usart2_TX_Buf[8] = HAL_GetUIDw0();
			
			uint16_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[9] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		default:break;
	}
}
