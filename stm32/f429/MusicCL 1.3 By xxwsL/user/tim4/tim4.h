#ifndef _tim4_h_
#define _tim4_h_
#include "xxwsL.h"

#define TimerClkAPB//1 90000000								//挂载在 APB1 时钟线上的定时器时钟频率为 90M
#define arr 40000											//重装载值
#define psc	900												//预分频后频率值

/*user function*/
uint32_t GetCntValue(void);

/*systems function*/
void NVIC_TimConfig(void);
void TIM4_Init(void);						// TIM4初始化函数
#endif

