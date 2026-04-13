// timer.c
#include "stm32f10x.h"    
#include "timer.h"
#include "stdbool.h"

// ???????
typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} SoftwareClock;

// ????????????
volatile SoftwareClock SysClock = {6, 0, 0}; // ?????? 6:00:00

// ???????????
volatile uint8_t display_elapsed = 0;

// ????????? TIM3 ??
volatile uint16_t TIM3_Count = 0;

// ??? TIM2 ??????(1 Hz)
void Timer_Init(void)
{
    // ?? TIM2 ??
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    // ?? TIM2 ????
    TIM_InternalClockConfig(TIM2);
    
    // ?? TIM2 ?????
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1; // 10 kHz / 10000 = 1 Hz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; // 72 MHz / 7200 = 10 kHz
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    
    // ?? TIM2 ??????
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    
    // ?? TIM2 ????
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    
    // ?? NVIC ?????
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    
    // ?? TIM2
    TIM_Cmd(TIM2, ENABLE);
}

// ??? TIM3 ?????????(60 ?)
void Timer_Init1(void)
{
    // ?? TIM3 ??
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    // ?? TIM3 ????
    TIM_InternalClockConfig(TIM3);
    
    // ?? TIM3 ?????
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1; // 10 kHz / 10000 = 1 Hz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; // 72 MHz / 7200 = 10 kHz
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    
    // ?? TIM3 ??????
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    
    // ?? TIM3 ????
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    
    // ?? NVIC ?????
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    
    // ?? TIM3,???????
    TIM_Cmd(TIM3, DISABLE);
}

// TIM2 ??????(??????)
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        // ?? TIM2 ??????
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        
        // ??????
        SysClock.second++;
        if (SysClock.second >= 60)
        {
            SysClock.second = 0;
            SysClock.minute++;
            if (SysClock.minute >= 60)
            {
                SysClock.minute = 0;
                SysClock.hour++;
                if (SysClock.hour >= 24)
                {
                    SysClock.hour = 0;
                }
            }
        }
    }
}

// TIM3 ??????(??????)
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        // ?? TIM3 ??????
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        
        TIM3_Count++;
        if (TIM3_Count >= 60)
        {
            // ???60?,??????????
            display_elapsed = 1;
            TIM3_Count = 0;
            TIM_Cmd(TIM3, DISABLE); // ?? TIM3
        }
    }
}

// ?? TIM3(????????)
void TIM3_Start(void)
{
    TIM3_Count = 0;
    display_elapsed = 0;
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE);
}

// ?? TIM3(????????)
void TIM3_Stop(void)
{
    TIM_Cmd(TIM3, DISABLE);
    TIM3_Count = 0;
}

// ?? TIM3 ??????60???
bool TIM3_HasElapsed(void)
{
    if (display_elapsed)
    {
        display_elapsed = 0;
        return true;
    }
    return false;
}
