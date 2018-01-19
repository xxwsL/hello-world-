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

#define OLED_CMD  	0		//写命令
#define OLED_DATA 	1		//写数据

void OLED_GPIO_init(void);								//IO口初始化
void OLED_Init(void);									//oled初始化
void OLEDinit_dpy(void);								//初始化显示测试

void OLED_WR_Byte(u8 dat,u8 cmd);						//写命令|之类	
void OLED_Display_On(void);								//开显示
void OLED_Display_Off(void);							//关 显示

void OLED_Refresh_Gram(void);							//刷新屏幕						   		    
void OLED_Clear(void);									//清屏

void OLED_center_dpy(const u8 *str,u8 line);			//居中显示，字体大小16				
void OLED_DrawPoint(u8 x,u8 y,u8 mark);					//填充点
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);	//指定位置显示一个字
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	//显示字符串
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);	//指定位置显示一个数字
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 mark);  		//填错矩形区域
u32 mypow(u8 m,u8 n);

#endif

