#include "xxwsL.h"

uint8_t i;
uint8_t cnt;

/*ϵͳ��ʼ��*/
void sysinit(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	// �ж����ȼ�����2
	LED_Init();			//LED��ʼ��
	Delay_Init();		//��ʱ������ʼ��
	LCD_Init();
	CLinit();
	TIM4_Init();
	voiceot_init();
	ADCinit(ADC1OK|ADC2OK);
}

/*ϵͳ����ִ��*/
void runtask(void){
	
//2

//
	Delay_ms(50);
	
}


