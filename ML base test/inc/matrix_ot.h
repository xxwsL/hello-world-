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
#define MatInit mat_create,mat_delete
#define MatDeal output,mat_cut,mat_assignment,mat_zero,mat_size,mat_message
#define MatMath mat_cov,mat_norm2,mat_mult	
#define MatFiInit {MatInit,MatDeal,MatMath}

//矩阵初始化宏
#define i16MatInit(MatName) {i16MatrixAdd(MatName),i16MatrixMessage(MatName)}
#define f32MatInit(MatName) {f32MatrixAdd(MatName),f32MatrixMessage(MatName)}

typedef struct MatFunction {
	//矩阵初始化函数
	struct MatrixStr(*mat_create) (uint16_t mat_line, uint16_t mat_row, uint16_t mat_type);
	uint8_t (*mat_delete) (struct MatrixStr *mat);
	//矩阵处理函数
	uint8_t (*output) (const struct MatrixStr *mat);
	struct MatrixStr (*mat_cut) (struct MatrixStr *mat_a, uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number, uint8_t remat_type);
	uint8_t (*mat_assignment) (struct MatrixStr *mat, float value);
	uint8_t (*mat_zero) (struct MatrixStr *mat);
	uint32_t (*mat_size) (const struct MatrixStr *mat);
	uint8_t (*mat_message) (const struct MatrixStr *mat);
	//矩阵运算函数
	struct MatrixStr (*mat_cov) (const struct MatrixStr *mat);
	float (*mat_norm2) (const struct MatrixStr *mat);
	struct MatrixStr (*mat_mult) (const struct MatrixStr *mat_l, const struct MatrixStr *mat_r);
}MatFistr;

//一类矩阵
typedef struct MatrixStr {
	// 矩阵信息
	void* SaveAddr;	
	uint16_t flag;
	uint16_t line;
	uint16_t row;
	//uint16_t height;
	//MatFistr function;
}MatStr;

extern MatFistr matfi;

//创建矩阵
MatStr mat_create(uint16_t mat_line, uint16_t mat_row, uint16_t mat_type);
//释放矩阵
uint8_t mat_delete(MatStr *mat);

//矩阵已制表形式输出
uint8_t output(const MatStr *mat);
//切割矩阵
MatStr mat_cut(MatStr *mat_a,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type);
//矩阵赋值
uint8_t mat_assignment(MatStr *mat, float value);
//矩阵赋0
uint8_t mat_zero(MatStr *mat);
//矩阵大小
uint32_t mat_size(const MatStr *mat);
//打印矩阵信息
uint8_t mat_message(const MatStr *mat);

//求矩阵协方差
MatStr mat_cov(const MatStr *mat);
//求向量矩阵二范数
float mat_norm2(const MatStr *mat);
//矩阵相乘
MatStr mat_mult(const MatStr *mat_l, const MatStr *mat_r);

#endif // ! _matrix_ot_h_
