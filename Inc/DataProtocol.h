#ifndef __DATAPROTOCOL_H
#define __DATAPROTOCOL_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
typedef struct
{
	__IO uint16_t BufLenght;//缓存长度
	__IO uint8_t* Buff;//缓存首地址
	__IO uint8_t Flag;//数据解析标志位，1=解析出一帧数据，0=未解析出有效数据帧
	
	__IO uint8_t FE_Flag;//收到0xFE数据 置1，紧接着下一位数据是0xEF则为新的帧头，否则置0
	__IO uint8_t FH;//帧头标志，0=帧头不完整、1=帧头完整
	__IO uint8_t DataLenght;//当前数据长度
}ParseData_Struct;

void ParseData_Init(ParseData_Struct *ParseData, uint16_t BufLeng);//解析数据参数初始化
void ParseDataFunction(ParseData_Struct *ParseData, uint8_t Data);//解析数据函数

#ifdef __cplusplus
}
#endif

#endif
