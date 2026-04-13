#include "stm32f10x.h"                
 
void VoiceSensor_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//??PA11?
 
uint8_t VoiceSensor_Get(void)     //??PA11????
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15);
}
 
