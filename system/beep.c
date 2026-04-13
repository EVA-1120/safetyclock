// beep.c
#include "stm32f10x.h"    // Device header
#include "beep.h"

// ?????????
volatile uint8_t beep_state = 0;

// ???????
volatile uint8_t beep_count = 0;

// ??????
void Beep_init(void)
{
    // ?? GPIOA ??
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_gpiox, ENABLE);
    
    // ????????
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_mode;
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_speed;
    GPIO_Init(GPIO_PORTa, &GPIO_InitStructure);
    
    BEEP_OFF;
    
    // ??? TIM4
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // ?? TIM4 ? 400ms ??????
    TIM_TimeBaseInitStructure.TIM_Period = 4000 - 1; // ?????? 72MHz, 72MHz / 7200 (Prescaler) = 10kHz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; // 72MHz / 7200 = 10kHz
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
    
    // ?? TIM4 ??????
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    
    // ?? TIM4 ????
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    
    // ?? NVIC ?????
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    
    // ?? TIM4,???????
    TIM_Cmd(TIM4, DISABLE);
}

// ???????
void BEEP_Start(void)
{
    beep_state = 1;
    beep_count = 0;
    TIM_SetCounter(TIM4, 0); // ?????
    TIM_Cmd(TIM4, ENABLE);    // ?? TIM4
}

// ???????
void BEEP_Stop(void)
{
    beep_state = 0;
    TIM_Cmd(TIM4, DISABLE); // ?? TIM4
    BEEP_OFF;
}

// ?????????
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        
        if (beep_state)
        {
            if (beep_count < 5) // ??5?,??400ms??400ms?
            {
                if (beep_count % 2 == 0)
                {
                    BEEP_ON;
                }
                else
                {
                    BEEP_OFF;
                }
                beep_count++;
            }
            else
            {
                BEEP_OFF;
                beep_state = 0;
                TIM_Cmd(TIM4, DISABLE); // ?? TIM4
            }
        }
    }
}
