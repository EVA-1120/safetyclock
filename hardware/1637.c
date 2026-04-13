// 1637.c
#include <string.h> // 提供了一些用于处理字符串和内存块的函数。
#include <stdint.h> // 定义了具有确定大小的整数类型。
#include <stdbool.h> // 提供布尔类型支持。
#define TUBE_DISPLAY_NULL							26
#define TUBE_DISPLAY_DECIMAL_PIONT_OFFSET			16
#include "stm32f10x.h"
#include "1637.h"
#include "delay.h"

TM1637Tube_ts sDisplayData;

const uint8_t u8NumTab[] = 
{
	//0,	1,	 2,	  3,	 4,	  5,	 6,   7,   8,   9,   A,   b,  C,    d,   E,   F,  	
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
	//0., 1.,	 2.,	3.,	 4.,  5.,   6.,  7.,  8.,  9. Null
	0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x00
};

// 最左至最右数码管 ，依次为0-3号，对应的显示寄存器地址
const uint8_t u8TubeAddrTab[] = 
{
	0xC0,0xC1,0xC2,0xC3
};

void TM1637_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOB的时钟

	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//将PB10和PB11引脚初始化为开漏输出

	/*设置默认电平*/
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);			//设置PB10和PB11引脚初始化后默认为高电平（释放总线状态）
}

/**
  * 函数：I2C写SCL引脚电平
  * 参数：BitValue 协议层传入的当前需要写入SCL的电平，范围0~1
  * 返回值：无
  * 注意事项：当BitValue为0时，置SCL为低电平；当BitValue为1时，置SCL为高电平
  */
void TM1637_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);		//根据BitValue，设置SCL引脚的电平
	Delay_us(10);												//延时10us，防止时序频率超过要求
}

/**
  * 函数：I2C写SDA引脚电平
  * 参数：BitValue 协议层传入的当前需要写入SDA的电平，范围0~1
  * 返回值：无
  * 注意事项：当BitValue为0时，置SDA为低电平；当BitValue为1时，置SDA为高电平
  */
void TM1637_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);		//根据BitValue，设置SDA引脚的电平，BitValue要实现非0即1的特性
	Delay_us(10);												//延时10us，防止时序频率超过要求
}

/**
  * 函数：I2C读SDA引脚电平
  * 参数：无
  * 返回值：协议层需要得到的当前SDA的电平，范围0~1
  * 注意事项：当前SDA为低电平时，返回0；当前SDA为高电平时，返回1
  */
uint8_t TM1637_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);		//读取SDA电平
	Delay_us(10);												//延时10us，防止时序频率超过要求
	return BitValue;											//返回SDA电平
}

void TM1637_Start(void)
{
	TM1637_W_SDA(1);	//释放SDA，确保SDA为高电平
	TM1637_W_SCL(1);	//释放SCL，确保SCL为高电平
	TM1637_W_SDA(0);	//在SCL高电平期间，拉低SDA，产生起始信号
	TM1637_W_SCL(0);	//起始后把SCL也拉低，即为了占用总线，也为了方便总线时序的拼接
}

void TM1637_Stop(void)
{
	TM1637_W_SCL(0);  //拉低SCL，确保SCL为低电平
	TM1637_W_SDA(0);	//拉低SDA，确保SDA为低电平
	TM1637_W_SCL(1);	//释放SCL，使SCL呈现高电平
	TM1637_W_SDA(1);	//在SCL高电平期间，释放SDA，产生终止信号
}

// 应答信号
uint8_t TM1637_ReceiveAck(void)
{
	uint8_t AckBit;							//定义应答位变量
	TM1637_W_SDA(1);							//接收前，主机先确保释放SDA，避免干扰从机的数据发送
	TM1637_W_SCL(1);							//释放SCL，主机在SCL高电平期间读取SDA
	AckBit = TM1637_R_SDA();					//将应答位存储到变量里
	TM1637_W_SCL(0);							//拉低SCL，开始下一个时序模块
	return AckBit;							//返回应答位变量
}

// 向 TM1637 发送一个字节数据
void TM1637_Write_Byte(uint8_t data)
{
    uint8_t i;
    TM1637_W_SCL(0); // 设置时钟线 SCL 为低电平，准备开始发送数据

    // 循环发送 8 位数据
    for (i = 0; i < 8; i++)
    {
        // 根据数据的最低位决定数据线 SDA 的状态
        if(data & 0x01)
        {
            TM1637_W_SDA(1); // 发送 1
        }
        else
        {
            TM1637_W_SDA(0); // 发送 0
        }    
        
        data = data >> 1; // 右移数据，处理下一个位
        
        TM1637_W_SCL(1); // 拉高时钟线，表示位数据有效
        TM1637_W_SCL(0); // 拉低时钟线，准备发送下一个位
    }
}

// 向 TM1637 数码管写入命令
void TM1637_WriteCmd(uint8_t u8Cmd)
{
    // 开始信号，表示通信开始
    TM1637_Start();
    
    // 发送命令字节
    TM1637_Write_Byte(u8Cmd);
    
    // 接收确认应答
    TM1637_ReceiveAck();
    
    // 停止信号，表示通信结束
    TM1637_Stop();
}

// 向指定地址写入数据
// u8Addr: 要写入的地址
// u8Data: 要写入的数据
void TM1637_WriteData(uint8_t u8Addr, uint8_t u8Data)
{
    // 开始信号，表示通信开始
    TM1637_Start();
    
    // 发送地址字节
    TM1637_Write_Byte(u8Addr);
    
    // 接收确认应答
    TM1637_ReceiveAck();
    
    // 发送数据字节
    TM1637_Write_Byte(u8Data);
    
    // 接收确认应答
    TM1637_ReceiveAck();
    
    // 停止信号，表示通信结束
    TM1637_Stop();
}

// 在四个数码管上显示数据
// sData: 显示数据结构体，包含四个数码管的显示值
void TM1637_TubeDisplay(TM1637Tube_ts sData)
{
    uint8_t temp[4], i;
    
    // 根据 sData 中的值，从 u8NumTab 数组中获取对应的段码
    temp[0] = u8NumTab[sData.tube0]; // 获取第一个数码管的段码
    temp[1] = u8NumTab[sData.tube1]; // 获取第二个数码管的段码
    temp[2] = u8NumTab[sData.tube2]; // 获取第三个数码管的段码
    temp[3] = u8NumTab[sData.tube3]; // 获取第四个数码管的段码
    
    // 遍历四个数码管，逐个写入数据
    for (i = 0; i < 4; i++)
    {
        // 向每个数码管的地址写入对应的段码
        TM1637_WriteData(u8TubeAddrTab[i], temp[i]);
    }
}

// 设置亮度
// 0x88为开显示，u8Brt亮度
void TM1637_SetBrightness(uint8_t u8Brt)
{
	TM1637_WriteCmd(0x88 | u8Brt);
}

// 显示开关
// 0x88为开显示，0x80关显示
void TM1637_Switch(bool bState)
{
	bState ? TM1637_WriteCmd(0x88) : TM1637_WriteCmd(0x80);
}

// 显示数字
void TM1637_DisplayNumber(uint8_t num)
{
    // 将数字转换为显示编码并发送到数码管
    // 这里假设显示数字在最低四位
    Display_TubeDataProcess(num);
}

// 清除数码管显示
void TM1637_Clear(void)
{
    // 清除数码管显示的代码
    Display_TubeDataProcess(0); // 显示0
}

void Display_Init(void)
{
	TM1637_Switch(0); // 关显示
	TM1637_SetBrightness(0x87); // 设置亮度，开显示
	TM1637_WriteCmd(0x44); // 写数据到寄存器，固定地址模式
	memset(&sDisplayData, 0xFF, sizeof(sDisplayData));
}

void Display_TubeDataProcess(uint16_t u16Data)
{
	memset(&sDisplayData, 0xFF, sizeof(sDisplayData));
	if (u16Data > 9999)
	{
		u16Data = 9999; // 最多四位数
	}
	if (u16Data > 999) // 四位数
	{
		sDisplayData.tube0 = (uint8_t)(u16Data / 1000); // 千位
		sDisplayData.tube1 = (uint8_t)(u16Data / 100 % 10); // 百位
		sDisplayData.tube2 = (uint8_t)(u16Data / 10 % 10); // 十位
		sDisplayData.tube3 = (uint8_t)(u16Data % 10); // 个位
	}
	else if (u16Data > 99) // 三位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube1 = (uint8_t)(u16Data / 100); // 百位
		sDisplayData.tube2 = (uint8_t)(u16Data / 10 % 10); // 十位
		sDisplayData.tube3 = (uint8_t)(u16Data % 10); // 个位	   
	}
	else if (u16Data > 9) // 两位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube1 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube2 = (uint8_t)(u16Data / 10); // 十位
		sDisplayData.tube3 = (uint8_t)(u16Data % 10); // 个位
	}
	else // 一位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube1 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube2 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube3 = (uint8_t)u16Data; // 个位
	}
	TM1637_TubeDisplay(sDisplayData);
}

void Display_TubeDatafirst(uint16_t u16Data)
{
	memset(&sDisplayData, 0xFF, sizeof(sDisplayData));
	if (u16Data > 99)
	{
		u16Data = 99; // 最多两位数
	}
	
	if (u16Data > 9) // 两位数
	{		
		sDisplayData.tube0 = (uint8_t)(u16Data / 10); // 十位
		sDisplayData.tube1 = (uint8_t)(u16Data % 10); // 个位	
		sDisplayData.tube2 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube3 = TUBE_DISPLAY_NULL; // 不显示
	}
	else // 一位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube1 = (uint8_t)u16Data; // 个位
		sDisplayData.tube2 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube3 = TUBE_DISPLAY_NULL; // 不显示
	}
	TM1637_TubeDisplay(sDisplayData);
}

void Display_TubeDatalast(uint16_t u16Data)
{
	memset(&sDisplayData, 0xFF, sizeof(sDisplayData));
	if (u16Data > 99)
	{
		u16Data = 99; // 最多两位数
	}
	
	if (u16Data > 9) // 两位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube1 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube2 = (uint8_t)(u16Data / 10); // 十位
		sDisplayData.tube3 = (uint8_t)(u16Data % 10); // 个位
	}
	else // 一位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube1 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube2 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube3 = (uint8_t)u16Data; // 个位
	}
	TM1637_TubeDisplay(sDisplayData);
}

void Display_TubeDatatwo(uint16_t u16Data1, uint16_t u16Data2)
{
	//	Display_TubeDatalast(u16Data2);
	//	Display_TubeDatafirst(u16Data1);
	memset(&sDisplayData, 0xFF, sizeof(sDisplayData));
	if (u16Data1 > 99 || u16Data2 > 99)
	{
		u16Data1 = 99; // 最多两位数
		u16Data2 = 99;
	}
	
	if (u16Data1 > 9 || u16Data2 > 9) // 两位数
	{
		sDisplayData.tube0 = (uint8_t)(u16Data1 / 10); // 十位
		sDisplayData.tube1 = (uint8_t)(u16Data1 % 10); // 个位
		sDisplayData.tube2 = (uint8_t)(u16Data2 / 10); // 十位
		sDisplayData.tube3 = (uint8_t)(u16Data2 % 10); // 个位
	}
	else // 一位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube1 = (uint8_t)u16Data1; // 个位
		sDisplayData.tube2 = TUBE_DISPLAY_NULL; // 不显示
		sDisplayData.tube3 = (uint8_t)u16Data2; // 个位
	}
	TM1637_TubeDisplay(sDisplayData);
}
