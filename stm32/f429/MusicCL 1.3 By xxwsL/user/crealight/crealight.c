#include "crealight.h"

CL CLstr;		//定义CL类


/*
CL默认初始化函数
*/
void CLinit(void)
{
	_CLinit(RoundMaxdef,RoundLines,RoundRows,LCD_WHITE,RoundRad);
}

/*
CL初始化函数（参数可变）
*/
void _CLinit(uint8_t RoundMaxi,uint8_t Linei,uint8_t Rowi,uint32_t SetColori,uint16_t Radi)
{
	CLstr.RoundMax=RoundMaxi;
	CLstr.Lines = Linei;
	CLstr.Rows  = Rowi; 
	CLstr.SetColor=SetColori;
	CLstr.Rad=Radi;							//系统参数写入
	
	rond_XY_get();							//得到XY基底坐标	
	crea_round(CLstr.Rad);						//生成圆形矩阵界面
	
}

/*
CL类的X和Y坐标获得函数
*/
void rond_XY_get(void)
{
	CLstr.Xpos=LCD_Width/(CLstr.Lines*2);	//X坐标基底
	CLstr.Ypos=LCD_Height/(CLstr.Rows*2);	//Y坐标基底
}

/*
创建一个圆形排列矩阵函数（默认参数调用CL类）
*/
int crea_round(uint16_t Radi)
{
	uint16_t i;
	if((Radi>CLstr.Xpos)&&(Radi>CLstr.Ypos))
	{
		return error;
	}
	else
	{
		LCD_SetColor(CLstr.SetColor);			//初始化画笔颜色
		for(i=0;i<CLstr.RoundMax;i++)
		{   
			LCD_FillCircle((i%CLstr.Lines*2+1)*CLstr.Xpos,(i/CLstr.Lines*2+1)*CLstr.Ypos,Radi);
		}
	}
	return true;
}

/*
圆形排列矩阵单个操作函数（半径参数可变）
*/
int ot_round_Rad(int8_t RoundNumsi,uint32_t colori,uint16_t Radi)
{
	if(RoundNumsi==error)
	{
		return error;
	}
	if(Radi>CLstr.Rad)
	{
		return error;
	}
	LCD_SetColor(colori);
	LCD_FillCircle((RoundNumsi%CLstr.Lines*2+1)*CLstr.Xpos,(RoundNumsi/CLstr.Lines*2+1)*CLstr.Ypos,Radi);
	return true;
}	

/*Operation of a single circle from the matrix(The radius parameter is immutable)*/
void ot_round(int8_t RoundNumsi,uint32_t colori)
{
	ot_round_Rad(RoundNumsi,colori,CLstr.Rad);
}

/*use rand() to get setcolor value*/
uint32_t GetRandColor(void)
{
	uint32_t setcolor;
	switch(rand()%21)
	{
		case 1 : setcolor=  LCD_WHITE  	;	  break;
		case 2 : setcolor=	DARK_GREY  	;     break;                          
		case 3 : setcolor=	DARK_YELLOW ;     break;
		case 4 : setcolor=	LCD_GREEN  	;     break;
		case 5 : setcolor=	LCD_RED    	;     break;
		case 6 : setcolor=	LCD_CYAN   	;     break;
		case 7 : setcolor=	LCD_MAGENTA	;     break;
		case 8 : setcolor=	LCD_YELLOW 	;     break;
		case 9 : setcolor=	LCD_GREY   	;     break;                   
		case 10: setcolor=	LIGHT_BLUE 	;     break;
		case 11: setcolor=  LIGHT_GREEN	;     break;
		case 12: setcolor=	LIGHT_RED  	;     break;
		case 13: setcolor=	LIGHT_CYAN 	;     break;
		case 14: setcolor=	LIGHT_YELLOW;     break;
		case 15: setcolor=	LIGHT_GREY	;	  break;  
		case 16: setcolor=	DARK_BLUE 	;     break;
		case 17: setcolor=	DARK_GREEN	;     break;
		case 18: setcolor=	DARK_RED	;     break;
		case 19: setcolor=	DARK_CYAN	;     break;
		case 20: setcolor=	DARK_MAGENTA;     break;
		default: setcolor=	LCD_BLUE	;     break;
		}
	return setcolor;
}


