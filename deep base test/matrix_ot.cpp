#include "matrix_ot.h"

MatStr status;
//输出float型矩阵
//mat:矩阵
uint8_t output(MatStr* mat)		
{
	uint16_t i = 0, j = 0;							//行和列地址偏移量
	float* f32add;									//float类型矩阵指针
	int16_t* i16add;								//int16_t矩阵指针
	switch (mat->flag&MatTypeFlag){
		case i16Flag:
			i16add = (int16_t*)mat->SaveAddr;			//矩阵指针首地址
			for (i = 0; i < mat->line; i++) {
				for (j = 0; j < mat->row; j++) {
#ifdef Simulation										//仿真模式
					printf("%d\t", *(i16add + j));		//制表方式输出矩阵
#else
//此处加不是仿真的执行代码
#endif
				}
				i16add += mat->row;
#ifdef Simulation										//仿真模式
				printf("\n\n");
#else
//此处加不是仿真的执行代码
#endif
			}
		break;
		case f32Flag:	
			f32add = (float*)mat->SaveAddr;				//矩阵指针首地址
			for (i = 0; i < mat->line; i++) {
				for (j = 0; j < mat->row; j++) {
#ifdef Simulation										//仿真模式
					printf("%f\t", *(f32add + j));		//制表方式输出矩阵
#else
//此处加不是仿真的执行代码
#endif
				}
				f32add += mat->row;
#ifdef Simulation										//仿真模式
				printf("\n\n");
#else
//此处加不是仿真的执行代码
#endif
			}
		break;
	}
	return true;
}

//matrix_a:被切割矩阵a
//matrix_b:切割部分载体
//cut_line_szie:切割行长
//cut_row_size :切割列长
//number:切割目标位置
MatStr matrix_cut(MatStr* mat,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type)
{
	uint16_t  i = 0,j=0;
	uint16_t  rows_max;
	int16_t   *i16mat_add, *i16remat;
	float	  *f32mat_add, *f32remat;
	MatStr remat;
	if (cut_line_size <= mat->line || cut_row_size <= mat->row) {
		remat.line = cut_line_size;
		remat.row = cut_row_size;
		rows_max = mat->row / cut_row_size;
		switch (mat->flag&MatTypeFlag) {
		case i16Flag:					//切割int16_t类型
			i16mat_add = (int16_t*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//初始切割地址
			switch (remat_type)
			{
			case i16Flag:			//返回int16_t类型
#ifdef Simulation					//仿真模式
				i16remat = (int16_t*)malloc(cut_line_size*cut_row_size * 2);
#else
//动态内存申请
#endif
				remat.SaveAddr = (int16_t*)i16remat;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(i16remat++) = (int16_t)(*(i16mat_add + j));
					}
					i16mat_add += mat->row;
				}
				remat.flag = i16Flag;
				break;
			case f32Flag:			//返回float类型
#ifdef Simulation						//仿真模式
				f32remat = (float*)malloc(cut_line_size*cut_row_size * 4);
#else
//动态内存申请
#endif
				remat.SaveAddr = (float*)f32remat;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(f32remat++) = (float)(*(i16mat_add + j));
					}
					i16mat_add += mat->row;
				}
				remat.flag = f32Flag;
				break;
				break;
			default:break;
			}
			break;
		case f32Flag:					//切割float类型
			f32mat_add = (float*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//初始切割地址
			switch (remat_type)
			{
			case i16Flag:				//返回int16_t类型
#ifdef Simulation						//仿真模式
				i16remat = (int16_t*)malloc(cut_line_size*cut_row_size * 2);
#else
//动态内存申请
#endif
				remat.SaveAddr = (int16_t*)i16remat;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(i16remat++) = (int16_t)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat.flag = i16Flag;
				break;					//返回float类型
			case f32Flag:
#ifdef Simulation						//仿真模式
				f32remat = (float*)malloc(cut_line_size*cut_row_size * 4);
#else
				//动态内存申请
#endif
				remat.SaveAddr = (float*)f32remat;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(f32remat++) = (float)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat.flag = f32Flag;
				break;
				break;
			default:break;
			}
			break;
		default:break;
		}
	}
	return remat;
}

