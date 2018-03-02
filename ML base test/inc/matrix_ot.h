#ifndef  _matrix_ot_h_
#define  _matrix_ot_h_
#include "xxwsL.h"

//矩阵类型flag
#define MatTypeFlag 0x0003
#define i16Flag		0x0001
#define f32Flag		0x0002

//矩阵存放地址
#define i16MatrixAdd(MatName) (int16_t*)MatName
#define f32MatrixAdd(MatName) (float*)MatName

//矩阵维度
#define MatLine(MatName)   sizeof(MatName)/sizeof(MatName[0])
#define i16MatRow(MatName) sizeof(MatName[0])/2
#define f32MatRow(MatName) sizeof(MatName[0])/4

//矩阵信息
#define i16MatrixMessage(MatName) i16Flag,MatLine(MatName),i16MatRow(MatName) 
#define f32MatrixMessage(MatName) f32Flag,MatLine(MatName),f32MatRow(MatName)

//矩阵可执行函数
#define MarFiInit output,mat_cut,mat_cov	

//矩阵初始化宏
#define i16MatInit(MatName) {i16MatrixAdd(MatName),i16MatrixMessage(MatName)}
#define f32MatInit(MatName) {f32MatrixAdd(MatName),f32MatrixMessage(MatName)}

typedef struct MatFunction {
	//矩阵调用函数
	uint8_t (*output) (struct MatrixStr *mat);
	struct MatrixStr (*mat_cut) (struct MatrixStr *mat_a, uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number, uint8_t remat_type);
	struct MatrixStr (*mat_cov) (struct MatrixStr *mat);
}MatFistr;

//一类矩阵
typedef struct MatrixStr {
	// 矩阵信息
	void* SaveAddr;	
	uint16_t flag;
	uint16_t line;
	uint16_t row;
	//MatFistr function;
}MatStr;

extern MatFistr matfi;

//矩阵已制表形式输出
uint8_t output(MatStr *mat); 
//切割矩阵
MatStr mat_cut(MatStr *mat_a,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type);
//求矩阵协方差
MatStr mat_cov(MatStr *mat);


#endif // ! _matrix_ot_h_
