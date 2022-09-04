#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define Usart2_RX_LEN 100
#define Usart2_TX_LEN 100
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern __IO uint8_t Usart2_RX_Buf[Usart2_RX_LEN];
extern __IO uint8_t Usart2_TX_Buf[Usart2_TX_LEN];
extern __IO uint8_t Usart2_TX_State;
extern __IO uint8_t Usart2_RX_State;
void MX_USART2_Init(void);//USART2初始化函数

#define Usart3_RX_LEN 60
#define Usart3_TX_LEN 60
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern __IO uint8_t Usart3_RX_Buf[Usart3_RX_LEN];
extern __IO uint8_t Usart3_TX_Buf[Usart3_TX_LEN];
void MX_USART3_Init(void);//USART3初始化函数

#define Uart4_RX_LEN 30
#define Uart4_TX_LEN 30
extern UART_HandleTypeDef huart4;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
extern __IO uint8_t Uart4_RX_Buf[Uart4_RX_LEN];
extern __IO uint8_t Uart4_TX_Buf[Uart4_TX_LEN];
void MX_UART4_Init(void);//UART4初始化函数

void UsartReceive_IDLE(UART_HandleTypeDef *huart);//串口DMA接收中断函数
void dma_printf(const char *format, ...);//DMA发送方式printf()函数
	
#ifdef __cplusplus
}
#endif

#endif
