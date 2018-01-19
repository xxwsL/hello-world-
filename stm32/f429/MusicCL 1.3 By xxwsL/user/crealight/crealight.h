#ifndef _ceralight_h
#define _ceralight_h

#include "xxwsL.h"
#include "lcd_rgb.h"

//系统参数
#define RoundMaxdef 15							
#define RoundLines 5
#define RoundRows 3
#define RoundRad 60

//系统宏定功能

typedef struct
{
	//user interface
    uint8_t RoundMax;
	uint8_t Lines; 
	uint8_t Rows;
	uint32_t SetColor;
	uint8_t Rad;
	
	//sys save messmage
	uint16_t Xpos;
	uint16_t Ypos;
	
	//user funtion
	void (*inrond_NLR)(u16 in);
	
}CL;

//系统操作函数
void CLinit(void);
void _CLinit(uint8_t RoundMaxi,uint8_t Linei,uint8_t Rowi,uint32_t SetColori,uint16_t Radi);
void rond_XY_get(void);

//用户操作函数
int crea_round(uint16_t radii);
int ot_round_Rad(int8_t RoundNumsi,uint32_t colori,uint16_t Radi);
void ot_round(int8_t RoundNumsi,uint32_t colori);
uint32_t GetRandColor(void);


#endif


