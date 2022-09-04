#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 
extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_spi1_rx;
extern DMA_HandleTypeDef hdma_spi1_tx;

void SPI1_CSX_GPIO_Init(void);//SPI1片选IO初始化
void MX_SPI1_Init(void);//SPI1初始化函数


#ifdef __cplusplus
}
#endif

#endif
