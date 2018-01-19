#include "tim4.h"

struct tim4struct
{
	uint32_t cnt;
}tim4str;

void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0x0001)
	{
		ot_round(tim4str.cnt%5,GetRandColor());
		if(tim4str.cnt%7==5||tim4str.cnt%7==6)
		{
			ot_round(0,GetRandColor());
			ot_round(1,GetRandColor());
			ot_round(2,GetRandColor());
			ot_round(3,GetRandColor());
			ot_round(4,GetRandColor());
		}
		ot_round(voice_lowot(Ka1(Get_Adc(1,0))),GetRandColor());
		ot_round(voice_hightot(Ka2(Get_Adc(2,7))),GetRandColor());
		tim4str.cnt++;
		TIM4->SR&=~(1<<0);
	}
	
}
 
/*返回定时器当前计数值*/
uint32_t GetCntValue(void)
{
	return tim4str.cnt;
}

void TIM4_Init(void)
{
	RCC->APB1ENR|=1<<2;	//TIM4时钟使能    
 	TIM4->ARR=arr-1;  	//设定计数器自动重装值 
	TIM4->PSC=psc-1;  	//预分频器	  
	TIM4->DIER|=1<<0;   //允许更新中断	  
	TIM4->CR1|=0x01;    //使能定时器3
  	NVIC_TimConfig();	//抢占1，子优先级3，组2									 
}

void NVIC_TimConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//配置 TIM4 中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;					//	中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		// 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;				// 响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// 使能中断
	NVIC_Init(&NVIC_InitStructure);
	
}





