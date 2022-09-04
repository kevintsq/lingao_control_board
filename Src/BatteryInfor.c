/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：
1、更新电池状态信息
2、计算电池组剩余电量百分比
**************************************************************************/
#include "BatteryInfor.h"
#include "ShareWare.h"

#define R1_R2 ((82.0f + 10.0f) / 10.0f)	//通过分压电阻计算分压系数
#define	ADC_VREFINT 1.212f				//ADC内部参照电压

/*-----------------------------------------------------------
函数功能: 电池状态初始化函数
输入参数: 电池参数结构体指针，低通滤波系数
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void Battery_Init(Battery_Struct *Battery, float a)
{	
	Battery->ADchx = 0;//电压ADC值
	Battery->ADre = 0; //STM32内部参照电压ADC值
	Battery->a = a; //低通滤波系数
	Battery->Voltage = 0; //电压值 V
	Battery->Current = 0; //电流值 A
	Battery->Capacity = 0;//剩余电量 %
}

/*-----------------------------------------------------------
函数功能: 更新电池状态信息
输入参数: 电池参数结构体指针，ADC的DMA缓存数组指针
返 回 值: None
说    明: 调用该函数更新电池的电压、电量信息
 -----------------------------------------------------------*/
void UpdateBatteryInfor(Battery_Struct *Battery, uint16_t *ADCx_DMA_Buff)
{
	Battery->ADchx =  ADCx_DMA_Buff[0];//获取电池电压ADC值
	Battery->ADre  =  ADCx_DMA_Buff[1];//STM32内部参照电压ADC值	
	float Voltage = ADC_VREFINT * (float)Battery->ADchx / (float)Battery->ADre * R1_R2;//通过采样电阻分压换算出电池电压值赋值给低通滤波器结构体中的采集值
	Battery->Voltage = (Battery->a * Voltage) + (1.0f - Battery->a) * Battery->Voltage;//电池电压值经过低通滤波器后数值会更加稳定	
	Battery->Capacity = GetdBatteryCapacity(Battery->Voltage, 4);//获取电池剩余电量百分比
}

/*-----------------------------------------------------------
函数功能: 计算电池组剩余电量百分比
输入参数: 当前电池组输出电压值，锂电池串联数
返 回 值: 当前电池组剩余电量百分比值
说    明: 电量百分比数值范围0-100，该函数仅对锂电池电量计算有效。
 -----------------------------------------------------------*/
uint8_t GetdBatteryCapacity(float BatteryVoltag, uint8_t BatterySeriesNumber)
{
	uint8_t BatteryCapacity;//锂电池组电量百分比值
	float SingleBatteryVoltag = (float)BatteryVoltag / BatterySeriesNumber;//计算锂电池组单个锂电池电压值
	if(SingleBatteryVoltag >= 4.06f)      BatteryCapacity=(((SingleBatteryVoltag - 4.06f)/0.14f)*10+90);
	else if(SingleBatteryVoltag >= 3.98f) BatteryCapacity=(((SingleBatteryVoltag - 3.98f)/0.08f)*10+80);
	else if(SingleBatteryVoltag >= 3.92f) BatteryCapacity=(((SingleBatteryVoltag - 3.92f)/0.06f)*10+70);
	else if(SingleBatteryVoltag >= 3.87f) BatteryCapacity=(((SingleBatteryVoltag - 3.87f)/0.05f)*10+60);
	else if(SingleBatteryVoltag >= 3.82f) BatteryCapacity=(((SingleBatteryVoltag - 3.82f)/0.05f)*10+50);
	else if(SingleBatteryVoltag >= 3.79f) BatteryCapacity=(((SingleBatteryVoltag - 3.79f)/0.03f)*10+40);
	else if(SingleBatteryVoltag >= 3.77f) BatteryCapacity=(((SingleBatteryVoltag - 3.77f)/0.02f)*10+30);
	else if(SingleBatteryVoltag >= 3.74f) BatteryCapacity=(((SingleBatteryVoltag - 3.74f)/0.03f)*10+20);
	else if(SingleBatteryVoltag >= 3.68f) BatteryCapacity=(((SingleBatteryVoltag - 3.68f)/0.06f)*10+10);
	else if(SingleBatteryVoltag >= 3.45f) BatteryCapacity=(((SingleBatteryVoltag - 3.45f)/0.23f)*10+5);
	else if(SingleBatteryVoltag >= 3.0f)  BatteryCapacity=(((SingleBatteryVoltag - 3.0f)/0.45f)*10+0);
	else BatteryCapacity = 0;
	if(BatteryCapacity > 100) BatteryCapacity = 100;
	return BatteryCapacity;//电池电量
}
