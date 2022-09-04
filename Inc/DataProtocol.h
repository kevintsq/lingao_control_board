#ifndef __DATAPROTOCOL_H
#define __DATAPROTOCOL_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
typedef struct
{
	__IO uint16_t BufLenght;//���泤��
	__IO uint8_t* Buff;//�����׵�ַ
	__IO uint8_t Flag;//���ݽ�����־λ��1=������һ֡���ݣ�0=δ��������Ч����֡
	
	__IO uint8_t FE_Flag;//�յ�0xFE���� ��1����������һλ������0xEF��Ϊ�µ�֡ͷ��������0
	__IO uint8_t FH;//֡ͷ��־��0=֡ͷ��������1=֡ͷ����
	__IO uint8_t DataLenght;//��ǰ���ݳ���
}ParseData_Struct;

void ParseData_Init(ParseData_Struct *ParseData, uint16_t BufLeng);//�������ݲ�����ʼ��
void ParseDataFunction(ParseData_Struct *ParseData, uint8_t Data);//�������ݺ���

#ifdef __cplusplus
}
#endif

#endif
