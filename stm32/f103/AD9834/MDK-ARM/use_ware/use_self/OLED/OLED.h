#ifndef OLED_H
#define OLED_H
#include "sys.h"


//#define GND PDout(0)
//#define VCC PEout(7)
#define D0  PEout(13)
#define D1  PEout(11)
#define RES PEout(9)
#define DC  PEout(7)
#define CS  PBout(1)

#define OLED_CMD  	0		//д����
#define OLED_DATA 	1		//д����

void OLED_GPIO_init(void);								//IO�ڳ�ʼ��
void OLED_Init(void);									//oled��ʼ��
void OLEDinit_dpy(void);								//��ʼ����ʾ����

void OLED_WR_Byte(uint8_t dat,uint8_t cmd);						//д����|֮��	
void OLED_Display_On(void);								//����ʾ
void OLED_Display_Off(void);							//�� ��ʾ

void OLED_Refresh_Gram(void);							//ˢ����Ļ						   		    
void OLED_Clear(void);									//����

void OLED_center_dpy(const uint8_t *str,uint8_t line);			//������ʾ�������С16				
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t mark);					//����
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);	//ָ��λ����ʾһ����
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p,uint8_t size);	//��ʾ�ַ���
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);	//ָ��λ����ʾһ������
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t mark);  		//����������
uint32_t mypow(uint8_t m,uint8_t n);

#endif

