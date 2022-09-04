/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：
1、解析数据参数初始化
2、解析数据函数
3、解析环形缓存区的数据
**************************************************************************/
#include "DataProtocol.h"
#include "ShareWare.h"

/*-----------------------------------------------------------
函数功能: 解析数据参数初始化
输入参数: 结构体参数，数据缓存长度
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void ParseData_Init(ParseData_Struct *ParseData, uint16_t BufLeng)
{
	ParseData->Flag = 0;//数据解析标志位，1=解析出一帧数据，0=未解析出有效数据帧
	ParseData->BufLenght = BufLeng;//缓存长度
	ParseData->Buff = (uint8_t*)pvPortMalloc(sizeof(uint8_t) * BufLeng);//动态分配BufLeng个uint8_t型存储单元，并将该单元的首地址存储到指针变量ringBuff->Ring_Buff中
	
	ParseData->FE_Flag = 0;//收到0xFE数据 置1，紧接着下一位数据是0xEF则为新的帧头，否则置0
	ParseData->FH = 0;//帧头标志，0=帧头不完整、1=帧头完整
	ParseData->DataLenght = 0;//当前数据长度
}

/*-----------------------------------------------------------
函数功能: 解析数据函数
输入参数: 结构体参数，数据值
返 回 值: None
说    明: 将收到的一串数据逐个传入该函数进行解析，若是解析出
一帧完整数据“ParseData->Flag”标志位会自动置1
 -----------------------------------------------------------*/
void ParseDataFunction(ParseData_Struct *ParseData, uint8_t Data)
{	
	if(!ParseData->Flag)//一帧数据未接收完整，继续处于接收数据状态
	{
		ParseData->Buff[ParseData->DataLenght]=Data;//数据存入数组
		
		switch(Data)
		{
			case 0xFE: ParseData->FE_Flag=1; break;
			
			case 0xEF:
			{
				if(ParseData->FE_Flag)//收到完整帧头
				{
					ParseData->FE_Flag=0;//清除标志
					ParseData->FH=1;//完整帧头
					ParseData->Buff[0]=0xFE;//重新赋值
					ParseData->Buff[1]=0xEF;//重新赋值
					ParseData->Buff[2]=ParseData->BufLenght;//预先将数据最大长度值赋值进数组数据长度位
					ParseData->DataLenght=1;//重新校准当前数据计数值
				}		
			}break;
			
			default: ParseData->FE_Flag=0; break;
		}
	}
		
	if( ( ParseData->DataLenght > (ParseData->Buff[2]+2) ) && ParseData->FH )//完整收齐一帧数据
	{
		uint8_t SumCheck=0;//校验码
		uint8_t i = ParseData->Buff[2] + 3;
		for(;(i--)>0;) SumCheck += ParseData->Buff[i];//计算校验和

		if(SumCheck == ParseData->Buff[ParseData->Buff[2]+3])//检验校验值是否一致
		{
			ParseData->Flag=1;//标识一帧数据完整
			ParseData->FE_Flag=0;//清除标志
			ParseData->FH=0;//清除标志位
		}
		else//校验码不一致
		{
			ParseData->FE_Flag=0;//清除标志
			ParseData->FH=0;//清除标志位
		}
	}
	if(ParseData->DataLenght < (ParseData->BufLenght - 1))ParseData->DataLenght++;//防止数组溢出
	else ParseData->DataLenght=0;
}

