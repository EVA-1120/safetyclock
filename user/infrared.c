/*=================infrared.c=================*/
#include "infrared.h"

void Infrared_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//???????   
    RCC_APB2PeriphClockCmd(GPIOB_RCC,ENABLE);	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin  = PIN;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(PORT ,&GPIO_InitStructure);
}
