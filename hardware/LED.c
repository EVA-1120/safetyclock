
#include "LED.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_gpiox|RCC_APB2Periph_gpiox1,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure.GPIO_Mode=GPIO_mode;
	GPIO_InitStructure.GPIO_Pin=GPIO_PINa|GPIO_PINb|GPIO_PINc|GPIO_PINd|GPIO_PINe|GPIO_PINf|GPIO_PINg|GPIO_PINh;
	GPIO_InitStructure.GPIO_Speed=GPIO_speed;
	GPIO_Init(GPIO_PORTa,&GPIO_InitStructure);
	//GPIO_SetBits(GPIO_PORTa,GPIO_PINa|GPIO_PINb|GPIO_PINc|GPIO_PINd|GPIO_PINe|GPIO_PINf|GPIO_PINg|GPIO_PINh);
	
	GPIO_InitStructure1.GPIO_Mode=GPIO_mode;
	GPIO_InitStructure1.GPIO_Pin=GPIO_PINi|GPIO_PINj|GPIO_PINk|GPIO_PINl;
	GPIO_InitStructure1.GPIO_Speed=GPIO_speed;
	GPIO_Init(GPIO_PORTb,&GPIO_InitStructure1);
	//GPIO_SetBits(GPIO_PORTb,GPIO_PINi|GPIO_PINj|GPIO_PINk|GPIO_PINl);
}
void LED_ON(GPIO_TypeDef* a, uint16_t GPIO_pin)
{
	GPIO_ResetBits(a,GPIO_pin);
}

void LED_OFF(GPIO_TypeDef* a, uint16_t GPIO_pin)
{
	GPIO_SetBits(a,GPIO_pin);	
}
void LED_turn(GPIO_TypeDef* a, uint16_t GPIO_pin)
{
	if(GPIO_ReadOutputDataBit(a,GPIO_pin))
	{
		GPIO_ResetBits(a,GPIO_pin);
	}
	else
	{
		GPIO_SetBits(a,GPIO_pin);
	}	
}

void LED_ONGREEN1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2)
{
	
//	GPIO_ResetBits(a,GPIO_pin1);
//	GPIO_ResetBits(a,GPIO_pin2);
	GPIO_SetBits(a,GPIO_pin1);
	GPIO_SetBits(a,GPIO_pin2);
}

void LED_OFFGREEN1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2)
{
	
	GPIO_ResetBits(a,GPIO_pin1);
	GPIO_ResetBits(a,GPIO_pin2);
//	GPIO_SetBits(a,GPIO_pin1);
//	GPIO_SetBits(a,GPIO_pin2);
}
void LED_ONYELLOW1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2)
{
	
	GPIO_SetBits(a,GPIO_pin1);
	GPIO_SetBits(a,GPIO_pin2);
}

void LED_OFFYELLOW1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2)
{
	
	GPIO_ResetBits(a,GPIO_pin1);
	GPIO_ResetBits(a,GPIO_pin2);
}
void LED_ONRED1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2)
{
	
	GPIO_SetBits(a,GPIO_pin1);
	GPIO_SetBits(a,GPIO_pin2);
}
void LED_OFFRED1(GPIO_TypeDef* a, uint16_t GPIO_pin1,uint16_t GPIO_pin2)
{
	
	GPIO_ResetBits(a,GPIO_pin1);
	GPIO_ResetBits(a,GPIO_pin2);
}
