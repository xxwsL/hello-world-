#include "xxwsL.h"

uint8_t i;
uint8_t cnt;

/*系统初始化*/
void sysinit(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	// 中断优先级分组2
	LED_Init();			//LED初始化
	Delay_Init();		//延时函数初始化
	LCD_Init();
	CLinit();
	TIM4_Init();
	voiceot_init();
	ADCinit(ADC1OK|ADC2OK);
}

/*系统任务执行*/
void runtask(void){
	
//2

//
	Delay_ms(50);
	
}


