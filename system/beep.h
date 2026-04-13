// beep.h
#ifndef BEEP_H
#define BEEP_H

#include "stm32f10x.h"

#define RCC_APB2Periph_gpiox      RCC_APB2Periph_GPIOA
#define GPIO_PORTa                 GPIOA
#define GPIO_PIN                GPIO_Pin_0 
#define GPIO_mode                 GPIO_Mode_Out_PP
#define GPIO_speed                GPIO_Speed_50MHz
#define BEEP_ON           GPIO_ResetBits(GPIO_PORTa,GPIO_PIN)
#define BEEP_OFF          GPIO_SetBits(GPIO_PORTa,GPIO_PIN)

// ??????
void Beep_init(void);

// ???????(???)
void BEEP_Start(void);

// ???????
void BEEP_Stop(void);

// ?????????(? Timer4 ?????)
void TIM4_IRQHandler(void);

#endif
