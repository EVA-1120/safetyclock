#include "stm32f10x.h"    // Device header
#include "delay.h"
#include "MQ-2.h"
void MQ_2_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_gpiox,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_mode1;
	GPIO_InitStructure.GPIO_Pin=GPIO_PIN1;
	GPIO_Init(GPIO_PORTa,&GPIO_InitStructure);		
}

uint16_t MQ2_getData(void)
{
	uint16_t tempData;
	tempData=GPIO_ReadInputDataBit(GPIO_PORTa,GPIO_PIN1);
	return tempData;
}
