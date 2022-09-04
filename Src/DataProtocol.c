/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1���������ݲ�����ʼ��
2���������ݺ���
3���������λ�����������
**************************************************************************/
#include "DataProtocol.h"
#include "ShareWare.h"

/*-----------------------------------------------------------
��������: �������ݲ�����ʼ��
�������: �ṹ����������ݻ��泤��
�� �� ֵ: None
˵    ��: None
 -----------------------------------------------------------*/
void ParseData_Init(ParseData_Struct *ParseData, uint16_t BufLeng)
{
	ParseData->Flag = 0;//���ݽ�����־λ��1=������һ֡���ݣ�0=δ��������Ч����֡
	ParseData->BufLenght = BufLeng;//���泤��
	ParseData->Buff = (uint8_t*)pvPortMalloc(sizeof(uint8_t) * BufLeng);//��̬����BufLeng��uint8_t�ʹ洢��Ԫ�������õ�Ԫ���׵�ַ�洢��ָ�����ringBuff->Ring_Buff��
	
	ParseData->FE_Flag = 0;//�յ�0xFE���� ��1����������һλ������0xEF��Ϊ�µ�֡ͷ��������0
	ParseData->FH = 0;//֡ͷ��־��0=֡ͷ��������1=֡ͷ����
	ParseData->DataLenght = 0;//��ǰ���ݳ���
}

/*-----------------------------------------------------------
��������: �������ݺ���
�������: �ṹ�����������ֵ
�� �� ֵ: None
˵    ��: ���յ���һ�������������ú������н��������ǽ�����
һ֡�������ݡ�ParseData->Flag����־λ���Զ���1
 -----------------------------------------------------------*/
void ParseDataFunction(ParseData_Struct *ParseData, uint8_t Data)
{	
	if(!ParseData->Flag)//һ֡����δ�����������������ڽ�������״̬
	{
		ParseData->Buff[ParseData->DataLenght]=Data;//���ݴ�������
		
		switch(Data)
		{
			case 0xFE: ParseData->FE_Flag=1; break;
			
			case 0xEF:
			{
				if(ParseData->FE_Flag)//�յ�����֡ͷ
				{
					ParseData->FE_Flag=0;//�����־
					ParseData->FH=1;//����֡ͷ
					ParseData->Buff[0]=0xFE;//���¸�ֵ
					ParseData->Buff[1]=0xEF;//���¸�ֵ
					ParseData->Buff[2]=ParseData->BufLenght;//Ԥ�Ƚ�������󳤶�ֵ��ֵ���������ݳ���λ
					ParseData->DataLenght=1;//����У׼��ǰ���ݼ���ֵ
				}		
			}break;
			
			default: ParseData->FE_Flag=0; break;
		}
	}
		
	if( ( ParseData->DataLenght > (ParseData->Buff[2]+2) ) && ParseData->FH )//��������һ֡����
	{
		uint8_t SumCheck=0;//У����
		uint8_t i = ParseData->Buff[2] + 3;
		for(;(i--)>0;) SumCheck += ParseData->Buff[i];//����У���

		if(SumCheck == ParseData->Buff[ParseData->Buff[2]+3])//����У��ֵ�Ƿ�һ��
		{
			ParseData->Flag=1;//��ʶһ֡��������
			ParseData->FE_Flag=0;//�����־
			ParseData->FH=0;//�����־λ
		}
		else//У���벻һ��
		{
			ParseData->FE_Flag=0;//�����־
			ParseData->FH=0;//�����־λ
		}
	}
	if(ParseData->DataLenght < (ParseData->BufLenght - 1))ParseData->DataLenght++;//��ֹ�������
	else ParseData->DataLenght=0;
}

