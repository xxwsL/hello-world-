#ifndef _tim4_h_
#define _tim4_h_
#include "xxwsL.h"

#define TimerClkAPB//1 90000000								//������ APB1 ʱ�����ϵĶ�ʱ��ʱ��Ƶ��Ϊ 90M
#define arr 40000											//��װ��ֵ
#define psc	900												//Ԥ��Ƶ��Ƶ��ֵ

/*user function*/
uint32_t GetCntValue(void);

/*systems function*/
void NVIC_TimConfig(void);
void TIM4_Init(void);						// TIM4��ʼ������
#endif

