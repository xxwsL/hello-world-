#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

//ͨ���ı�TIM3->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
#define LED0_PWM_VAL TIM3->CCR2    

void TIM3_Int_Init(uint16_t arr,uint16_t psc);
void TIM3_PWM_Init(uint16_t arr,uint16_t psc);
void TIM5_Cap_Init(uint16_t arr,uint16_t psc);
void TIM7_Int_Init(uint16_t arr,uint16_t psc);
#endif























