#ifndef __AD9834_H 
#define __AD9834_H 
#include "sys.h"

#define Triangle_Wave    0x2002 
#define Sine_Wave  0x2008 
#define Square_Wave 0x2028
/* AD9834����Ƶ�� */ 

#define AD9834_SYSTEM_COLCK     75000000UL 
// B6 FS  B5 PS    B7 FSY   B8 SCK   B9 SDA B10 RST 

/* AD9834 �������� */ 
#define AD9834_Control_Port  	GPIOA
#define AD9834_FSYNC  	 		GPIO_PIN_3    	//A3
#define AD9834_SCLK   		 	GPIO_PIN_4		//A4
#define AD9834_SDATA  		 	GPIO_PIN_5 		//A5
#define AD9834_RESET  			GPIO_PIN_6		//A6
#define AD9834_FS  				GPIO_PIN_0		//B0
#define AD9834_PS  				GPIO_PIN_1		//B1

#define AD9834_FSYNC_SET   PAout(3)=1 

#define AD9834_FSYNC_CLR   PAout(3)=0 

#define AD9834_SCLK_SET    PAout(4)=1 

#define AD9834_SCLK_CLR    PAout(4)=0 

#define AD9834_SDATA_SET   PAout(5)=1 

#define AD9834_SDATA_CLR   PAout(5)=0 

#define AD9834_RESET_SET   PAout(6)=1

#define AD9834_RESET_CLR   PAout(6)=0 

 

#define FREQ_0      0 

#define FREQ_1      1 

 

#define DB15        0 

#define DB14        0 

#define DB13        B28 

#define DB12        HLB 

#define DB11        FSEL 

#define DB10        PSEL 

#define DB9         PIN_SW 

#define DB8         RESET 

#define DB7         SLEEP1 

#define DB6         SLEEP12 

#define DB5         OPBITEN 

#define DB4         SIGN_PIB 

#define DB3         DIV2 

#define DB2         0 

#define DB1         MODE 

#define DB0         0 

#define CONTROL_REGISTER    (DB15<<15)|(DB14<<14)|(DB13<<13)|(DB12<<12)|(DB11<<11)|(DB10<<10)|(DB9<<9)|(DB8<<8)|(DB7<<7)|(DB6<<6)|(DB5<<5)|(DB4<<4)|(DB3<<3)|(DB2<<2)|(DB1<<1)|(DB0<<0) 

/* AD9834�������� */ 

 void AD9834_Write_16Bits(unsigned int data) ;  //дһ���ֵ�AD9834 

 void AD9834_Select_Wave(unsigned int initdata) ; //ѡ��������� 

void AD9834_Init(void);  					//��ʼ������ 

 void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq) ;//ѡ������Ĵ��������Ƶ��ֵ 
 
 int16_t ot_AD9834(int16_t input);

#endif /* AD9834_H */ 

