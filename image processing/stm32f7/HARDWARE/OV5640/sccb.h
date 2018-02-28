#ifndef __SCCB_H
#define __SCCB_H
#include "xxwsL.h"


//IO��������
#define SCCB_SDA_IN()  {GPIOB->MODER&=~(3<<(3*2));GPIOB->MODER|=0<<3*2;}	//PB3 ����
#define SCCB_SDA_OUT() {GPIOB->MODER&=~(3<<(3*2));GPIOB->MODER|=1<<3*2;} 	//PB3 ���


//IO��������	   
#define SCCB_SCL(x)		GPIO_Pin_Set(GPIOB,PIN4,x)		//SCL
#define SCCB_SDA(x)		GPIO_Pin_Set(GPIOB,PIN3,x)		//SDA
#define SCCB_READ_SDA	GPIO_Pin_Get(GPIOB,PIN3)   		//��ȡSDA
 
///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void); 
#endif













