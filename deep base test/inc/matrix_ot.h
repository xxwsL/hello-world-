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
#define MatrixFunction //output,matrix_cut

//矩阵初始化宏
#define i16MatrixInit(MatName) {i16MatrixAdd(MatName),i16MatrixMessage(MatName),MatrixFunction}
#define f32MatrixInit(MatName) {f32MatrixAdd(MatName),f32MatrixMessage(MatName),MatrixFunction}

//一类矩阵
typedef struct MatrixStr {
	// 矩阵信息
	void* SaveAddr;	
	uint16_t flag;
	uint16_t line;
	uint16_t row;
	//矩阵调用函数
	//uint8_t (*output) (struct MatrixStr);
	//struct MatrixStr (*matrix_cut) (struct MatrixStr, uint8_t, uint8_t, uint8_t,uint8_t);
}MatStr;

uint8_t output(MatStr* mat); //矩阵已制表形式输出
MatStr matrix_cut(MatStr* mat_a,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type);	//切割矩阵


#endif // ! _matrix_ot_h_
