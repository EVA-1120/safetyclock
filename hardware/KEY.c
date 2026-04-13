// key.c
#include "KEY.h"
#include "delay.h"

// ???????
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_gpiox, ENABLE); // ??GPIOA???
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_KEY_mode;
	GPIO_InitStructure.GPIO_Pin = GPIO_PINC | GPIO_PIND | GPIO_PINE;
	GPIO_InitStructure.GPIO_Speed = GPIO_speed;
	GPIO_Init(GPIO_PORTa, &GPIO_InitStructure);
}

// ??????(???)
uint8_t KEy_getNUM(void)
{
	uint8_t Num = 0;
	if(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PINC) == 0)
	{
		Delay_ms(30); // ????
		while(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PINC) == 0); 
		Delay_ms(30);
		Num = 1;
	}
	if(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PIND) == 0)
	{
		Delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PIND) == 0); 
		Delay_ms(30);
		Num = 2;
	}
	if(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PINE) == 0)
	{
		Delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PINE) == 0); 
		Delay_ms(30);
		Num = 3;
	}
	return Num;
}

// ??????(????)
uint8_t KEy_getNUM1(void)
{
	uint8_t Num = 0;
	if(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PINC) == 0)
	{
		Num = 1;
	}
	if(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PIND) == 0)
	{
		Num = 2;
	}
	if(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PINE) == 0)
	{
		Num = 3;
	}
	if(GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PINC) == 0 && GPIO_ReadInputDataBit(GPIO_PORTa, GPIO_PIND) == 0)
	{
		Num = 4;
	}
	return Num;
}

// ??????(????)
uint8_t keycount(void)
{
	return KEy_getNUM(); // ??:???? KEy_getNUM ???
}

// ????(????)
uint16_t shownum(void)
{
	// ?? shownum ???
	// ??????????,??????????
	// ??,?????????????,???????????
	// ?????????,???????
	return 0; // ?????
}
