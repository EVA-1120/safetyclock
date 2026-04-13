#ifndef _MQ_2_H
#define _MQ_2_H
#include "stm32f10x.h"  
#define RCC_APB2Periph_gpiox      RCC_APB2Periph_GPIOA
#define GPIO_PORTa                 GPIOA
#define GPIO_PIN1               	 GPIO_Pin_1 
#define GPIO_mode1                GPIO_Mode_IPU
#define GPIO_speed                GPIO_Speed_50MHz
void MQ_2_init(void);
uint16_t MQ2_getData(void);
#endif
