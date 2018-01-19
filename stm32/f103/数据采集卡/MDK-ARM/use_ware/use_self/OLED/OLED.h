#ifndef OLED_H
#define OLED_H
#include "sys.h"


//#define GND PDout(0)
//#define VCC PEout(7)
#define D0  PDout(14)
#define D1  PDout(0)
#define RES PEout(7)
#define DC  PEout(9)
#define CS  PEout(11)

#define OLED_CMD  	0		//д����
#define OLED_DATA 	1		//д����

void OLED_GPIO_init(void);								//IO�ڳ�ʼ��
void OLED_Init(void);									//oled��ʼ��
void OLEDinit_dpy(void);								//��ʼ����ʾ����

void OLED_WR_Byte(u8 dat,u8 cmd);						//д����|֮��	
void OLED_Display_On(void);								//����ʾ
void OLED_Display_Off(void);							//�� ��ʾ

void OLED_Refresh_Gram(void);							//ˢ����Ļ						   		    
void OLED_Clear(void);									//����

void OLED_center_dpy(const u8 *str,u8 line);			//������ʾ�������С16				
void OLED_DrawPoint(u8 x,u8 y,u8 mark);					//����
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);	//ָ��λ����ʾһ����
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	//��ʾ�ַ���
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);	//ָ��λ����ʾһ������
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 mark);  		//����������
u32 mypow(u8 m,u8 n);

#endif

