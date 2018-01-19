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

#define OLED_CMD  	0		//写命令
#define OLED_DATA 	1		//写数据

void OLED_GPIO_init(void);								//IO口初始化
void OLED_Init(void);									//oled初始化
void OLEDinit_dpy(void);								//初始化显示测试

void OLED_WR_Byte(uint8_t dat,uint8_t cmd);						//写命令|之类	
void OLED_Display_On(void);								//开显示
void OLED_Display_Off(void);							//关 显示

void OLED_Refresh_Gram(void);							//刷新屏幕						   		    
void OLED_Clear(void);									//清屏

void OLED_center_dpy(const uint8_t *str,uint8_t line);			//居中显示，字体大小16				
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t mark);					//填充点
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);	//指定位置显示一个字
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p,uint8_t size);	//显示字符串
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);	//指定位置显示一个数字
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t mark);  		//填错矩形区域
uint32_t mypow(uint8_t m,uint8_t n);

#endif

