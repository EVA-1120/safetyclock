#include "stm32f10x.h"    // Device header
#include "beep.h"
#include "delay.h"
#include "timer.h"
#include "KEY.h"
#include "LED.h"
#include "OLED.h"
#include "1637.h"
#include "showtimer.h"
#include "MQ-2.h"
#include "Infrared.h"
#include "Voice.h"

#include <stdbool.h>
#include "1637.h"         // ????? TM1637_DisplayNumber ? TM1637_Clear

// ???????
typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} SoftwareClock;

// ??????????
extern volatile SoftwareClock SysClock;

// ????
uint8_t Keynum;
uint16_t shownum(void);
uint8_t keycount(void);
uint16_t NUM = 0;
uint16_t J = 0;
uint16_t NUM1 = 0;
uint16_t num1 = 0;
uint16_t year, month;

uint16_t arr1[] = {2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029, 2030, 2031, 2032};
uint16_t arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0};
uint16_t arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0};
uint16_t arr4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
uint16_t arr5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59};

uint16_t y = 0;
uint16_t m = 0;
uint16_t d = 0;
uint16_t t = 0;
uint16_t s = 0;
uint16_t t1 = 0;
uint16_t s1 = 1;
uint8_t bFlag = 0;
uint8_t SK = 0;
uint8_t KS = 0;
uint32_t flag = 0;
uint8_t S = 0;
uint8_t S1 = 0;
uint16_t value;

// ??????
bool display_on = false;

// ????
void show(uint16_t Year, uint16_t Mon, uint16_t Day, uint16_t Tim, uint16_t sec);
bool TIM3_HasElapsed(void);
void TIM3_Start(void);
void TIM3_Stop(void);
uint8_t keycount(void);
uint16_t shownum(void);

int main()
{
    // ?????
    Beep_init();
    Timer_Init();         // ??? TIM2 ??????
    Key_Init();
    OLED_Init();
    Infrared_Init();      // ????????
    VoiceSensor_Init();   // ????????
    TM1637_Switch(0);
    Timer_Init1();        // ??? TIM3 ????????

    OLED_ShowString(1,1,"System Ready");
    
    while(1)
    {   
        // ????
        OLED_ShowString(1,1,"Key1 select");
        OLED_ShowString(2,1,"Key2 ok");
        OLED_ShowNum(3,1,t,5);
        OLED_ShowNum(3,7,s,5);
        OLED_ShowNum(4,1,t1,5);
        OLED_ShowNum(4,7,s1,5);
        TM1637_Switch(0);
        
        // ????
        if((uint32_t)t == (uint32_t)t1 && (uint32_t)s == (uint32_t)s1)
        {
            // ????????????? BEEP_work
            BEEP_Start();
        }
        
        Keynum = KEy_getNUM();
        if(Keynum == 2)
        {
            OLED_Clear();
            OLED_ShowString(2,1,"1.timer");
            OLED_ShowString(2,8,"2.counter");
            OLED_ShowString(3,1,"3.clock");
            OLED_ShowString(3,8,"4.alarm");
            uint8_t Keyn = keycount();            
            switch(Keyn)
            {
                case 1:
                {
                    OLED_Clear();
                    while(1)
                    {
                        Keynum = KEy_getNUM();
                        OLED_ShowString(1,1,"1.show");
                        OLED_ShowString(2,1,"2.set");
                        if(Keynum == 1)
                        {
                            while(1)
                            {
                                OLED_Clear();
                                OLED_ShowString(2,1,"1.year");
                                OLED_ShowString(2,10,"2.month");
                                OLED_ShowString(3,1,"3.day");
                                OLED_ShowString(3,10,"4.time");
                                OLED_ShowString(4,1,"5.minute");
                                OLED_ShowString(4,10,"6.back");
                                if(S == 1)
                                {
                                    OLED_Clear();
                                    break;
                                }
                                uint8_t Km = keycount();
                                bFlag = 0;
                                flag = 0;
                                switch(Km)
                                {
                                    case 1:
                                    {
                                        OLED_Clear();
                                        while(1)
                                        {   
                                            TM1637_Init();
                                            Display_Init();   
                                            bFlag = 1;
                                            uint8_t K = KEy_getNUM();
                                            OLED_ShowString(1,1,"show year");
                                            if(flag == 0)
                                            {   
                                                flag = 1;
                                                y = shownum();
                                            }
                                            Display_TubeDataProcess(arr1[y-1]);
                                            if(K == 3)
                                            {
                                                TM1637_Switch(0);
                                                OLED_Clear();
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    case 2:
                                    {
                                        OLED_Clear();
                                        while(1)
                                        {   
                                            TM1637_Init();
                                            Display_Init();   
                                            bFlag = 2;
                                            uint8_t K = KEy_getNUM();
                                            OLED_ShowString(1,1,"show month");
                                            if(flag == 0)
                                            {                                                   
                                                flag = 1;
                                                m = shownum();                                                                        
                                            }
                                            Display_TubeDataProcess(arr2[m-1]);
                                            if(K == 3)
                                            {
                                                TM1637_Switch(0);
                                                OLED_Clear();
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    case 3:
                                    {
                                        OLED_Clear();
                                        while(1)
                                        {   
                                            TM1637_Init();
                                            Display_Init();   
                                            bFlag = 3;
                                            uint8_t K = KEy_getNUM();
                                            OLED_ShowString(1,1,"show day");
                                            if(flag == 0)
                                            {   
                                                flag = 1;
                                                d = shownum();                                        
                                            }
                                            Display_TubeDataProcess(arr3[d-1]);
                                            if(K == 3)
                                            {
                                                TM1637_Switch(0);
                                                OLED_Clear();                   
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    case 4:
                                    {
                                        OLED_Clear();
                                        while(1)
                                        {   
                                            TM1637_Init();
                                            Display_Init();   
                                            bFlag = 4;
                                            uint8_t K = KEy_getNUM();
                                            OLED_ShowString(1,1,"show time");
                                            if(flag == 0)
                                            {   
                                                flag = 1;
                                                t = shownum();                                        
                                            }
                                            Display_TubeDataProcess(arr4[t-1]);
                                            if(K == 3)
                                            {
                                                TM1637_Switch(0);
                                                OLED_Clear();
                                                break;
                                            }   
                                        }   
                                        break;
                                    }                                   
                                    case 5:
                                    {
                                        OLED_Clear();
                                        while(1)
                                        {   
                                            TM1637_Init();
                                            Display_Init();   
                                            bFlag = 5;
                                            uint8_t K = KEy_getNUM();
                                            OLED_ShowString(1,1,"show minute");
                                            if(flag == 0)
                                            {   
                                                flag = 1;
                                                s = shownum();                                        
                                            }
                                            Display_TubeDataProcess(arr5[s-1]);
                                            if(K == 3)
                                            {
                                                TM1637_Switch(0);
                                                OLED_Clear();                            
                                                break;
                                            }
                                            
                                        }
                                        break;
                                    }
                                    case 6:
                                    {           
                                        OLED_Clear();
                                        S = 1;
                                        break;                                       
                                    }
                                }
                            }
                        }
                        if(Keynum == 2)
                        {
                            OLED_Clear();
                            TM1637_Init();
                            Display_Init();   
                            while(1)
                            {
                                Keynum = KEy_getNUM();
                                OLED_ShowString(1,1,"1.show");
                                
                                OLED_ShowNum(2,5,J,5);
                                if(J > 0 && J < 6)
                                {
                                    Display_TubeDataProcess(arr1[y-1]);
                                }
                                else if(J >= 6 && J < 12)
                                {
                                    Display_TubeDatatwo(arr2[m-1], arr3[d-1]);
                                }
                                else
                                {
                                    Display_TubeDatatwo(arr4[t-1], arr5[s-1]);
                                }
                                if(Keynum == 3)
                                {
                                    OLED_Clear();
                                    break;      
                                }
                            }
                            
                            //show(s,m,d,t,num);
                        }
                        if(Keynum == 3)
                        {
                            break;
                        }
                    }
                    break;
                }
                case 2:
                {
                    OLED_Clear();
                    Timer_Init1();
                    TM1637_Init();
                    Display_Init();   
                    while(1)
                    {
                        uint8_t Km = KEy_getNUM1();
                        OLED_ShowString(2,1,"Num:");
                        Display_TubeDatatwo(num1, NUM1);
                        OLED_ShowNum(2,5,NUM1,5);
                        OLED_ShowNum(3,5,num1,5);
                        if(Km == 1)
                        {
                            TIM_Cmd(TIM3, ENABLE);
                        }
                        if(Km == 2)
                        {
                            TIM_Cmd(TIM3, DISABLE);
                        }
                        if(Km == 4)
                        {
                            NUM1 = 0;
                            num1 = 0;
                        }
                        if(Km == 3)
                        {
                            OLED_Clear();
                            TM1637_Switch(0);
                            break;
                        }                           
                    }   
                        break;
                }
                case 3:
                {
                    OLED_Clear();
                    while(1)
                    {
                        uint8_t Km = KEy_getNUM();
                        
                        OLED_ShowString(2,1,"1.set time");
                        OLED_ShowString(3,1,"2.set minute");
                        OLED_ShowString(4,1,"2.back");
                        bFlag = 0;
                        flag = 0;
                        if(S1 == 1)
                        {
                            OLED_Clear();
                            break;
                        }
                        uint8_t k = keycount();
                        switch(k)
                        {
                            case 1:
                            {
                                OLED_Clear();
                                while(1)
                                {
                                    TM1637_Init();
                                    Display_Init();   
                                    bFlag = 4;
                                    
                                    uint8_t K = KEy_getNUM();
                                    if(flag == 0)
                                    {   
                                        flag = 1;
                                        t1 = shownum();
                                        //O = t1;                                    
                                    }
                                    Display_TubeDataProcess(arr4[t1-1]);
                                    if(K == 3)
                                    {
                                        TM1637_Switch(0);
                                        OLED_Clear();
                                        break;
                                    }   
                                }
                                break;
                            }
                            case 2:
                            {
                                OLED_Clear();
                                while(1)
                                {
                                    TM1637_Init();
                                    Display_Init();   
                                    bFlag = 5;
                                    uint8_t K = KEy_getNUM();
                                    if(flag == 0)
                                    {   
                                        flag = 1;
                                        s1 = shownum();    
                                        //P = s1;
                                    }
                                    Display_TubeDataProcess(arr5[s1-1]);
                                    if(K == 3)
                                    {
                                        TM1637_Switch(0);
                                        OLED_Clear();
                                        break;
                                    }   
                                }
                                break;
                            }
                            case 3:
                            {           
                                    OLED_Clear();
                                    S1 = 1;
                                    break;   
                                
                            }
                        }
                        if(t == t1 && s == s1)
                        {
                            BEEP_Start(); // ?????????
                        }
                        if(Km == 3)
                        {
                            OLED_Clear();
                            break;
                        }
                    }   
                    break;
                }
                case 4:
                {
                    OLED_Clear();
                    MQ_2_init();
                    value = MQ2_getData();
                    while(1)
                    {
                        OLED_ShowString(3,8,"alarm");
                        if(value)
                        {
                            BEEP_Start(); // ?????????
                        }
                    }
                    
                    break;
                }
                case 5:
                {
                    OLED_Clear();
                    break;
                }
            }
        }

        // ??????????
        uint8_t current_hour = SysClock.hour;
        bool is_daytime = (current_hour >= 6 && current_hour < 18);
        
        if (is_daytime)
        {
            // ??:???????
            if (Read_STATE()) // ?????
            {
                if (!display_on)
                {
                    OLED_Clear();
                    OLED_ShowString(1, 1, "Person Detected");
                    TM1637_DisplayNumber(1); // ?? 1 ??????
                    display_on = true;
                    TIM3_Start(); // ?????????
                }
            }
        }
        else
        {
            // ??:???????
            if (VoiceSensor_Get() == 1) // ?????????????
            {
                if (!display_on)
                {
                    OLED_Clear();
                    OLED_ShowString(1, 1, "Sound Detected");
                    TM1637_DisplayNumber(2); // ?? 2 ??????
                    display_on = true;
                    TIM3_Start(); // ?????????
                }
            }
        }
        
        // ???????????1??
        if (display_on && TIM3_HasElapsed())
        {
            OLED_Clear();
            TM1637_Clear();
            display_on = false;
            OLED_ShowString(1, 1, "System Ready");
        }

        Delay_ms(100); // ????,??CPU??
    }
}

// ??? main.c ????? TIM4_IRQHandler
// TIM2_IRQHandler ?? timer.c ???
// TIM4_IRQHandler ?? beep.c ???
