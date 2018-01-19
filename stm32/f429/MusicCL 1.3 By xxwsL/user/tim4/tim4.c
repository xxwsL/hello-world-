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
 
/*���ض�ʱ����ǰ����ֵ*/
uint32_t GetCntValue(void)
{
	return tim4str.cnt;
}

void TIM4_Init(void)
{
	RCC->APB1ENR|=1<<2;	//TIM4ʱ��ʹ��    
 	TIM4->ARR=arr-1;  	//�趨�������Զ���װֵ 
	TIM4->PSC=psc-1;  	//Ԥ��Ƶ��	  
	TIM4->DIER|=1<<0;   //��������ж�	  
	TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	NVIC_TimConfig();	//��ռ1�������ȼ�3����2									 
}

void NVIC_TimConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//���� TIM4 �ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;					//	�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		// ��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;				// ��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);
	
}





