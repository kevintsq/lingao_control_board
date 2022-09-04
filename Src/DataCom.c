/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：
1、设置与反馈车体目标速度
2、反馈车体实时速度
3、反馈电源管理信息
4、反馈车体IMU信息
5、反馈设备号信息
**************************************************************************/
#include "DataCom.h"
#include "ShareWare.h"

/*-----------------------------------------------------------
函数功能: 数据接收接口
输入参数: 数据数组地址
返 回 值: None
说    明: 将解析出的数据帧传入该函数实现数值更新
 -----------------------------------------------------------*/
void DataCom_RX_Function(DataCom_RX_Struct *DataCom_RX, uint8_t *Buff)
{
	DataCom_RX->HeartbeatTime = 100;//心跳包时间
	switch(Buff[3])
	{
		case 1://设置与反馈车体目标速度
		{
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[4+i];
			DataCom_RX->Linear_X = floatHex.floatValue;//车体X轴目标线速度值 m/s
			
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[8+i];
			DataCom_RX->Linear_Y = floatHex.floatValue;//车体Y轴目标线速度值 m/s
			
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[12+i];
			DataCom_RX->Angular_Z = floatHex.floatValue;//车体Z轴目标角速度值 rad/s
			
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 1;
			Usart2_TX_Buf[3] = 1;
			
			uint16_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[4] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		case 2://反馈车体实时速度
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 13;
			Usart2_TX_Buf[3] = 2;
			
			floatHex.floatValue = Kinematics_Forward.Linear_X;//车体当前X轴线速度 m/s
			Usart2_TX_Buf[4] = floatHex.Hex[3];
			Usart2_TX_Buf[5] = floatHex.Hex[2];
			Usart2_TX_Buf[6] = floatHex.Hex[1];
			Usart2_TX_Buf[7] = floatHex.Hex[0];
			
			floatHex.floatValue = Kinematics_Forward.Linear_Y;//车体当前Y轴线速度 m/s
			Usart2_TX_Buf[8] = floatHex.Hex[3];
			Usart2_TX_Buf[9] = floatHex.Hex[2];
			Usart2_TX_Buf[10] = floatHex.Hex[1];
			Usart2_TX_Buf[11] = floatHex.Hex[0];
			
			floatHex.floatValue = Kinematics_Forward.Angular_Z;//车体当前Z轴角速度 rad/s
			Usart2_TX_Buf[12] = floatHex.Hex[3];
			Usart2_TX_Buf[13] = floatHex.Hex[2];
			Usart2_TX_Buf[14] = floatHex.Hex[1];
			Usart2_TX_Buf[15] = floatHex.Hex[0];
			
			uint16_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[16] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		case 3://反馈电源管理信息
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 8;
			Usart2_TX_Buf[3] = 3;
			int16_t Voltage = (int16_t)(Battery.Voltage * 100);//电池电压值 10mv
			Usart2_TX_Buf[4]= Voltage >> 8;//电池电压值 10mv
			Usart2_TX_Buf[5]= Voltage;			
			Usart2_TX_Buf[6]= 0;//电池电流值 10mA
			Usart2_TX_Buf[7]= 0;			
			Usart2_TX_Buf[8]= 0;
			Usart2_TX_Buf[9]= 0;
			Usart2_TX_Buf[10]= Battery.Capacity;//电池电量值 %
			
			uint16_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[11] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		case 4://反馈车体IMU信息
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 37;
			Usart2_TX_Buf[3] = 4;
			
			floatHex.floatValue = ICM42605.Pitch;//俯仰角 rad
			Usart2_TX_Buf[4] = floatHex.Hex[3];
			Usart2_TX_Buf[5] = floatHex.Hex[2];
			Usart2_TX_Buf[6] = floatHex.Hex[1];
			Usart2_TX_Buf[7] = floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Yaw;//偏航角 rad
			Usart2_TX_Buf[8] = floatHex.Hex[3];
			Usart2_TX_Buf[9] = floatHex.Hex[2];
			Usart2_TX_Buf[10] = floatHex.Hex[1];
			Usart2_TX_Buf[11] = floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Roll;//翻滚角 rad
			Usart2_TX_Buf[12]= floatHex.Hex[3];
			Usart2_TX_Buf[13]= floatHex.Hex[2];
			Usart2_TX_Buf[14]= floatHex.Hex[1];
			Usart2_TX_Buf[15]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Acc_X;//加速度计X轴
			Usart2_TX_Buf[16]= floatHex.Hex[3];
			Usart2_TX_Buf[17]= floatHex.Hex[2];
			Usart2_TX_Buf[18]= floatHex.Hex[1];
			Usart2_TX_Buf[19]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Acc_Y;//加速度计Y轴
			Usart2_TX_Buf[20]= floatHex.Hex[3];
			Usart2_TX_Buf[21]= floatHex.Hex[2];
			Usart2_TX_Buf[22]= floatHex.Hex[1];
			Usart2_TX_Buf[23]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Acc_Z;//加速度计Z轴
			Usart2_TX_Buf[24]= floatHex.Hex[3];
			Usart2_TX_Buf[25]= floatHex.Hex[2];
			Usart2_TX_Buf[26]= floatHex.Hex[1];
			Usart2_TX_Buf[27]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Gyro_X;//陀螺仪X轴
			Usart2_TX_Buf[28]= floatHex.Hex[3];
			Usart2_TX_Buf[29]= floatHex.Hex[2];
			Usart2_TX_Buf[30]= floatHex.Hex[1];
			Usart2_TX_Buf[31]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Gyro_Y;//陀螺仪Y轴
			Usart2_TX_Buf[32]= floatHex.Hex[3];
			Usart2_TX_Buf[33]= floatHex.Hex[2];
			Usart2_TX_Buf[34]= floatHex.Hex[1];
			Usart2_TX_Buf[35]= floatHex.Hex[0];
			
			floatHex.floatValue = ICM42605.Gyro_Z;//陀螺仪Z轴
			Usart2_TX_Buf[36]= floatHex.Hex[3];
			Usart2_TX_Buf[37]= floatHex.Hex[2];
			Usart2_TX_Buf[38]= floatHex.Hex[1];
			Usart2_TX_Buf[39]= floatHex.Hex[0];
			
			uint16_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[40] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		case 255://反馈设备号信息
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 6;
			Usart2_TX_Buf[3] = 0xFF;
			
			Usart2_TX_Buf[4] = 22;//协议版本
			Usart2_TX_Buf[5] = HAL_GetUIDw0() >> 24;//设备号
			Usart2_TX_Buf[6] = HAL_GetUIDw0() >> 16;
			Usart2_TX_Buf[7] = HAL_GetUIDw0() >> 8;			
			Usart2_TX_Buf[8] = HAL_GetUIDw0();
			
			uint16_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[9] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		default:break;
	}
}
