#ifndef _INFRARED_H_
#define _INFRARED_H_
#include "stm32f10x.h"

#define PORT GPIOB
#define PIN GPIO_Pin_8
#define GPIOB_RCC RCC_APB2Periph_GPIOB

#define Read_STATE() GPIO_ReadInputDataBit(PORT,PIN)//????????

void Infrared_Init(void);
void  infrared_test(void);
#endif
