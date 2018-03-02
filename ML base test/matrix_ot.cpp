#include "matrix_ot.h"

MatFistr matfi = { MarFiInit };

//优化次数:1
//输出float型矩阵
//mat:矩阵
uint8_t output(MatStr *mat)		
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

//优化次数:1
//把矩阵切割成对应大小
//matrix_a:被切割矩阵a
//matrix_b:切割部分载体
//cut_line_szie:切割行长
//cut_row_size :切割列长
//number:切割目标位置
MatStr mat_cut(MatStr *mat,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type)
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
动态内存申请
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
动态内存申请
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
动态内存申请
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
				动态内存申请
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

//优化次数:0
//求矩阵协方差		
//行数:样本个数(样本个数大于1),列数:样本维度
//mat:输入矩阵
MatStr mat_cov(MatStr *mat)
{
	uint16_t i = 0, j = 0,k=0;
	uint32_t line_offset=0,diff_mat_line=0;
	MatStr remat = {};		//标准c不能这样初始化
	int16_t *i16mat_add;
	float *aver_mat,*cov_mat,*f32mat_add,*diff_mat;
#ifdef Simulation		//仿真模式下
	cov_mat  = (float*)malloc(mat->row*mat->row*4);		//申请内存快注意大小合适
	aver_mat = (float*)malloc(mat->row * 4);			//注意，注意，注意
	diff_mat = (float*)malloc(mat->line*mat->row*4);
	for (i = 0; i < mat->row; i++) {
		*(aver_mat + i) = 0;
	}
	for (i = 0; i < mat->row*mat->row; i++) {
		*(cov_mat + i) = 0;
	}
#else
//内存管理函数
#endif
	switch (mat->flag&MatTypeFlag){	
		case i16Flag:										//输入int16_t矩阵
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//样本不同维度总和
				for (j = 0; j < mat->row; j++) {
					*(aver_mat + j) +=(float)(*(i16mat_add++));		
				}
			}
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//样本不同维度均值
				*(aver_mat + j) /= mat->line;
			}
			for (i = 0; i < mat->line; i++) {				//样本均差
				for (j = 0; j < mat->row; j++) {
					*(diff_mat + line_offset + j) = (*(i16mat_add++)) - (*(aver_mat + j));
				}
				line_offset += mat->row;
			}
			break;
		case f32Flag:										//输入float矩阵
			f32mat_add = (float*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//样本不同维度总和
				for (j = 0; j < mat->row; j++) {
					*(aver_mat + j) = (*(aver_mat + j)) + (float)(*(f32mat_add++));
				}
			}
			f32mat_add = (float*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//样本不同维度均值
				*(aver_mat + j) /= mat->line;;
			}
			for (i = 0; i < mat->line; i++) {				//样本均差
				for (j = 0; j < mat->row; j++) {
					*(diff_mat+ line_offset + j) = (*(f32mat_add++)) - (*(aver_mat + j));
				}
				line_offset += mat->row;
			}
	default:break;
	}
	line_offset = 0;
	for (i = 0; i < mat->row;i++) {							//求各个维度之间协方差		
		for (j = i; j < mat->row; j++) {
			for (k = 0; k < mat->line; k++) {
				*(cov_mat + line_offset + j) += (*(diff_mat+i+ diff_mat_line))*(*(diff_mat+j+ diff_mat_line));
				diff_mat_line += mat->row;
			}
			diff_mat_line = 0;
			(*(cov_mat + line_offset + j)) /= (mat->line - 1);
			if (i != j) {
				*(cov_mat + j*mat->row + i) = (*(cov_mat + line_offset + j));
			}
		}
		line_offset += mat->row;
	}
	remat.flag = f32Flag;
	remat.line = mat->row;
	remat.row = mat->row;
	remat.SaveAddr = (float*)cov_mat;
#ifdef Simulation		//仿真模式下
	free(aver_mat);		//释放内存
	free(diff_mat);
	aver_mat = NULL;	//指针清空
	diff_mat = NULL;
#else
//内存管理函数
	aver_mat = NULL;
	diff_mat = NULL;
#endif
	return remat;
}


