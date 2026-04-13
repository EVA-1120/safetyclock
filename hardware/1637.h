// 1637.h
#ifndef _1637_H_
#define _1637_H_

#include <stdbool.h>

typedef struct 
{
    uint8_t tube0;
    uint8_t tube1;
    uint8_t tube2;
    uint8_t tube3;
} TM1637Tube_ts;

// ????
void TM1637_Init(void);
void TM1637_Start(void);
void TM1637_Stop(void);
uint8_t TM1637_ReceiveAck(void);
void TM1637_Write_Byte(uint8_t data);
void TM1637_WriteCmd(uint8_t u8Cmd);
void TM1637_WriteData(uint8_t u8Addr, uint8_t u8Data);
void TM1637_TubeDisplay(TM1637Tube_ts sData);
void TM1637_SetBrightness(uint8_t u8Brt);
void TM1637_Switch(bool bState);
void Display_Init(void);
void Display_TubeDataProcess(uint16_t u16Data);
void Display_TubeDatatwo(uint16_t u16Data1, uint16_t u16Data2);
void Display_TubeDatafirst(uint16_t u16Data);
void Display_TubeDatalast(uint16_t u16Data);

// ?????????
void TM1637_DisplayNumber(uint8_t num);
void TM1637_Clear(void);

#endif
