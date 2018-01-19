#ifndef _ADC_h_
#define _ADC_h_
#include "xxwsL.h"

#define ADC1OK 0x01
#define ADC2OK 0x02

void ADCinit(uint8_t ADCx);
void ADC1init(void);
void ADC2init(void);

uint16_t Get_Adc(uint8_t ADCx,u8 ch);
uint16_t average_ADC(uint8_t ADCx,u8 ch);

#endif

