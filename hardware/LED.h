#ifndef _LED_H__
#define _LED_H__

#include "stm32f10x.h" 
#define RCC_APB2Periph_gpiox      RCC_APB2Periph_GPIOA
#define RCC_APB2Periph_gpiox1      RCC_APB2Periph_GPIOB
#define GPIO_PORTa                 GPIOA
#define GPIO_PINa                 GPIO_Pin_1 
#define GPIO_PINb                 GPIO_Pin_2 
#define GPIO_PINc                 GPIO_Pin_8
#define GPIO_PINd                 GPIO_Pin_9
#define GPIO_PINe                 GPIO_Pin_10
#define GPIO_PINf                GPIO_Pin_11 
#define GPIO_PINg                 GPIO_Pin_12 
#define GPIO_PINh                 GPIO_Pin_0 
#define GPIO_PORTb                 GPIOB
#define GPIO_PINi                 GPIO_Pin_11 
#define GPIO_PINj                 GPIO_Pin_10 
#define GPIO_PINk                 GPIO_Pin_5 
#define GPIO_PINl                 GPIO_Pin_6 

#define GPIO_mode                 GPIO_Mode_Out_PP
#define GPIO_speed                GPIO_Speed_50MHz
void LED_ON(GPIO_TypeDef* a, uint16_t GPIO_pin);
void LED_OFF(GPIO_TypeDef* a, uint16_t GPIO_pin);
void LED_ONYELLOW1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2);
void LED_OFFYELLOW1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2);
void LED_ONRED1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2);
void LED_OFFRED1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2);
void LED_ONGREEN1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2);
void LED_OFFGREEN1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2);

void LED_Init(void);
void LED_turn(GPIO_TypeDef* a, uint16_t GPIO_pin);
#endif

