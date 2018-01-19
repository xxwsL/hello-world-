#include "ADC.h"

void ADCinit(uint8_t ADCx)
{
	RCC->APB2RSTR|=1<<8;   	//ADCs复位
	RCC->APB2RSTR&=~(1<<8);	//复位结束	
	ADC->CCR=1<<16;			//ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz
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
		//先初始化IO口
 	RCC->APB2ENR|=1<<8;    	//使能ADC1时钟 
	RCC->AHB1ENR|=1<<0;    	//使能PORTA时钟	 
	
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;   //模拟输入模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	//上拉
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  
 	
	ADC1->CR1=0;   			//CR1设置清零
	ADC1->CR2=0;   			//CR2设置清零
	ADC1->CR1|=0<<24;      	//12位模式
	ADC1->CR1|=0<<8;    	//非扫描模式	
	
	ADC1->CR2&=~(1<<1);    	//单次转换模式
 	ADC1->CR2&=~(1<<11);   	//右对齐	
	ADC1->CR2|=0<<28;    	//软件触发
	
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     	//1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道5的采样时间
	ADC1->SMPR2&=~(7<<(3*0));//通道0采样时间清空	  
 	ADC1->SMPR2|=7<<(3*0); 	//通道0 480个周期,提高采样时间可以提高精确度	 
 	ADC1->CR2|=1<<0;	   	//开启AD转换器	  
}

void ADC2init(void)
{
		//先初始化IO口
 	RCC->APB2ENR|=1<<9;    	//使能ADC2时钟 
	RCC->AHB1ENR|=1<<0;    	//使能PORTA时钟	 
	
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;   //模拟输入模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	//上拉
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  
 	
	ADC2->CR1=0;   			//CR1设置清零
	ADC2->CR2=0;   			//CR2设置清零
	ADC2->CR1|=0<<24;      	//12位模式
	ADC2->CR1|=0<<8;    	//非扫描模式	
	
	ADC2->CR2&=~(1<<1);    	//单次转换模式
 	ADC2->CR2&=~(1<<11);   	//右对齐	
	ADC2->CR2|=0<<28;    	//软件触发
	
	ADC2->SQR1&=~(0XF<<20);
	ADC2->SQR1|=0<<20;     	//1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道5的采样时
	ADC2->SMPR2&=~(7<<(3*7));//通道7采样时间清空	  
 	ADC2->SMPR2|=7<<(3*7); 	//通道7480个周期,提高采样时间可以提高精确度	 
 	ADC2->CR2|=1<<0;	   	//开启AD转换器	  
}

//获得ADC值
//ch:通道值 0~16
//返回值:转换结果
uint16_t Get_Adc(uint8_t ADCx,u8 ch)   
{
	uint16_t ADCvalue;
	//设置转换序列
	switch(ADCx)
	{
		case 1:	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
				ADC1->SQR3|=ch;		  			    
				ADC1->CR2|=1<<30;       //启动规则转换通道 
				while(!(ADC1->SR&1<<1));//等待转换结束	 	   
				ADCvalue= ADC1->DR;		//返回adc值
		break;
		case 2:	ADC2->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
				ADC2->SQR3|=ch;		  			    
				ADC2->CR2|=1<<30;       //启动规则转换通道 
				while(!(ADC2->SR&1<<1));//等待转换结束	 	   
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

