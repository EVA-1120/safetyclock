// KEY.h
#ifndef _KEY_H__
#define _KEY_H__

#include "stm32f10x.h" 
#define RCC_APB2Periph_gpiox      RCC_APB2Periph_GPIOA
#define GPIO_PORTa                GPIOA
#define GPIO_PINC                 GPIO_Pin_5
#define GPIO_PIND                 GPIO_Pin_7
#define GPIO_PINE                 GPIO_Pin_3
#define GPIO_KEY_mode             GPIO_Mode_IPU
#define GPIO_speed                GPIO_Speed_50MHz

void Key_Init(void);
uint8_t KEy_getNUM(void);
uint8_t KEy_getNUM1(void);

// ?????????
uint8_t keycount(void);
uint16_t shownum(void);

#endif
