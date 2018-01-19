#include "ADC.h"

void ADCinit(uint8_t ADCx)
{
	RCC->APB2RSTR|=1<<8;   	//ADCs��λ
	RCC->APB2RSTR&=~(1<<8);	//��λ����	
	ADC->CCR=1<<16;			//ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz
	if(ADCx&0x01)
	{
		ADC1init();
	}
	if(ADCx&0x02)
	{
		ADC2init();
	}
}

void ADC1init(void)
{
		//�ȳ�ʼ��IO��
 	RCC->APB2ENR|=1<<8;    	//ʹ��ADC1ʱ�� 
	RCC->AHB1ENR|=1<<0;    	//ʹ��PORTAʱ��	 
	
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ��	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;   //ģ������ģʽ
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	//����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  
 	
	ADC1->CR1=0;   			//CR1��������
	ADC1->CR2=0;   			//CR2��������
	ADC1->CR1|=0<<24;      	//12λģʽ
	ADC1->CR1|=0<<8;    	//��ɨ��ģʽ	
	
	ADC1->CR2&=~(1<<1);    	//����ת��ģʽ
 	ADC1->CR2&=~(1<<11);   	//�Ҷ���	
	ADC1->CR2|=0<<28;    	//�������
	
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     	//1��ת���ڹ��������� Ҳ����ֻת����������1 			   
	//����ͨ��5�Ĳ���ʱ��
	ADC1->SMPR2&=~(7<<(3*0));//ͨ��0����ʱ�����	  
 	ADC1->SMPR2|=7<<(3*0); 	//ͨ��0 480������,��߲���ʱ�������߾�ȷ��	 
 	ADC1->CR2|=1<<0;	   	//����ADת����	  
}

void ADC2init(void)
{
		//�ȳ�ʼ��IO��
 	RCC->APB2ENR|=1<<9;    	//ʹ��ADC2ʱ�� 
	RCC->AHB1ENR|=1<<0;    	//ʹ��PORTAʱ��	 
	
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ��	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;   //ģ������ģʽ
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	//����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  
 	
	ADC2->CR1=0;   			//CR1��������
	ADC2->CR2=0;   			//CR2��������
	ADC2->CR1|=0<<24;      	//12λģʽ
	ADC2->CR1|=0<<8;    	//��ɨ��ģʽ	
	
	ADC2->CR2&=~(1<<1);    	//����ת��ģʽ
 	ADC2->CR2&=~(1<<11);   	//�Ҷ���	
	ADC2->CR2|=0<<28;    	//�������
	
	ADC2->SQR1&=~(0XF<<20);
	ADC2->SQR1|=0<<20;     	//1��ת���ڹ��������� Ҳ����ֻת����������1 			   
	//����ͨ��5�Ĳ���ʱ
	ADC2->SMPR2&=~(7<<(3*7));//ͨ��7����ʱ�����	  
 	ADC2->SMPR2|=7<<(3*7); 	//ͨ��7480������,��߲���ʱ�������߾�ȷ��	 
 	ADC2->CR2|=1<<0;	   	//����ADת����	  
}

//���ADCֵ
//ch:ͨ��ֵ 0~16
//����ֵ:ת�����
uint16_t Get_Adc(uint8_t ADCx,u8 ch)   
{
	uint16_t ADCvalue;
	//����ת������
	switch(ADCx)
	{
		case 1:	ADC1->SQR3&=0XFFFFFFE0;//��������1 ͨ��ch
				ADC1->SQR3|=ch;		  			    
				ADC1->CR2|=1<<30;       //��������ת��ͨ�� 
				while(!(ADC1->SR&1<<1));//�ȴ�ת������	 	   
				ADCvalue= ADC1->DR;		//����adcֵ
		break;
		case 2:	ADC2->SQR3&=0XFFFFFFE0;//��������1 ͨ��ch
				ADC2->SQR3|=ch;		  			    
				ADC2->CR2|=1<<30;       //��������ת��ͨ�� 
				while(!(ADC2->SR&1<<1));//�ȴ�ת������	 	   
				ADCvalue= ADC2->DR;
		break;
	}
	return ADCvalue;
}

uint16_t average_ADC(uint8_t ADCx,u8 ch)
{
	int16_t i;
	uint16_t temp;
	for(i=0;i<5;i++)
	{
		temp+=Get_Adc(ADCx,ch);
	}
	return (temp/=i+1);
}

