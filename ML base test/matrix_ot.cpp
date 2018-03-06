#include "matrix_ot.h"

MatFistr matfi = MatFiInit;

//优化次数:3
//输出float型矩阵
//mat:矩阵
//return:位宽8标志位
uint8_t output(const MatStr *mat)		
{
	uint16_t i = 0, j = 0;								//行和列地址偏移量
	float* f32add;										//float类型矩阵指针
	int16_t* i16add;									//int16_t矩阵指针
	if ((mat->SaveAddr == NULL) || (mat->flag == 0))
		return false;
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

//优化次数:2
//把矩阵切割成对应大小
//matrix_a:被切割矩阵a
//matrix_b:切割部分载体
//cut_line_szie:切割行长
//cut_row_size :切割列长
//number:切割目标位置
//return:矩阵结构体
MatStr mat_cut(MatStr *mat,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type)
{
	uint16_t  i = NULL,j=NULL;
	uint16_t  rows_max=NULL;
	int16_t   *i16mat_add=NULL, *i16remat=NULL;
	float	  *f32mat_add=NULL, *f32remat=NULL;
	MatStr remat;
	if (cut_line_size <= mat->line || cut_row_size <= mat->row) {
		rows_max = mat->row / cut_row_size;
		switch (mat->flag&MatTypeFlag) {
		case i16Flag:					//切割int16_t类型
			i16mat_add = (int16_t*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//初始切割地址
			switch (remat_type)
			{
				case i16Flag:			//返回int16_t类型
					remat = mat_create(cut_line_size, cut_row_size,i16Flag);
					i16remat =(int16_t*)remat.SaveAddr;				
					for (i = 0; i < cut_line_size; i++) {
						for (j = 0; j < cut_row_size; j++) {
							*(i16remat++) = (int16_t)(*(i16mat_add + j));
						}
						i16mat_add += mat->row;
					}
					remat.flag = i16Flag;
					break;
				case f32Flag:			//返回float类型
					remat = mat_create(cut_line_size, cut_row_size, f32Flag);
					f32remat = (float*)remat.SaveAddr;
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
				remat = mat_create(cut_line_size, cut_row_size, i16Flag);
				i16remat = (int16_t*)remat.SaveAddr;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(i16remat++) = (int16_t)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat.flag = i16Flag;
				break;					//返回float类型
			case f32Flag:
				remat = mat_create(cut_line_size, cut_row_size, f32Flag);
				f32remat = (float*)remat.SaveAddr;
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

//优化次数:2
//求矩阵协方差		
//行数:样本个数(样本个数大于1),列数:样本维度
//mat:输入矩阵
//
MatStr mat_cov(const MatStr *mat)
{
	uint16_t i = 0, j = 0,k=0;
	int16_t *i16mat_add;
	uint32_t line_offset=0,diff_mat_line=0;
	MatStr remat,aver_mat,diff_mat;
	float *f32mat_add;
	remat = mat_create(mat->row,mat->row,f32Flag);		//申请内存快注意大小合适
	mat_zero(&remat);
	aver_mat = mat_create(1, mat->row, f32Flag);			//注意，注意，注意
	mat_zero(&aver_mat);
	diff_mat = mat_create(mat->line,mat->row,f32Flag);
	switch (mat->flag&MatTypeFlag){	
		case i16Flag:										//输入int16_t矩阵
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//样本不同维度总和
				for (j = 0; j < mat->row; j++) {
					*((float*)aver_mat.SaveAddr + j) +=(float)(*(i16mat_add++));		
				}
			}
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//样本不同维度均值
				*((float*)aver_mat.SaveAddr + j) /= mat->line;
			}
			for (i = 0; i < mat->line; i++) {				//样本均差
				for (j = 0; j < mat->row; j++) {
					*((float*)diff_mat.SaveAddr + line_offset + j) = (*(i16mat_add++)) - (*((float*)aver_mat.SaveAddr + j));
				}
				line_offset += mat->row;
			}
			break;
		case f32Flag:										//输入float矩阵
			f32mat_add = (float*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//样本不同维度总和
				for (j = 0; j < mat->row; j++) {
					*((float*)aver_mat.SaveAddr + j) = (*((float*)aver_mat.SaveAddr + j)) + (float)(*(f32mat_add++));
				}
			}
			f32mat_add = (float*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//样本不同维度均值
				*((float*)aver_mat.SaveAddr + j) /= mat->line;;
			}
			for (i = 0; i < mat->line; i++) {				//样本均差
				for (j = 0; j < mat->row; j++) {
					*((float*)diff_mat.SaveAddr + line_offset + j) = (*(f32mat_add++)) - (*((float*)aver_mat.SaveAddr + j));
				}
				line_offset += mat->row;
			}
	default:break;
	}
	line_offset = 0;
	for (i = 0; i < mat->row;i++) {							//求各个维度之间协方差		
		for (j = i; j < mat->row; j++) {
			for (k = 0; k < mat->line; k++) {
				*((float*)remat.SaveAddr + line_offset + j) += (*((float*)diff_mat.SaveAddr +i+ diff_mat_line))*(*((float*)diff_mat.SaveAddr +j+ diff_mat_line));
				diff_mat_line += mat->row;
			}
			diff_mat_line = 0;
			(*((float*)remat.SaveAddr + line_offset + j)) /= (mat->line - 1);
			if (i != j) {
				*((float*)remat.SaveAddr + j*mat->row + i) = (*((float*)remat.SaveAddr + line_offset + j));
			}
		}
		line_offset += mat->row;
	}
	mat_delete(&aver_mat);
	mat_delete(&diff_mat);
	return remat;
}

//优化次数:0
//创建矩阵(矩阵内存片里的值硬件随机值,需初始化0)
//mat_line:矩阵行数
//mat_row:矩阵列数
//mat_type:矩阵类型
//return:矩阵结构体
MatStr mat_create(uint16_t mat_line, uint16_t mat_row, uint16_t mat_type)
{
	int16_t *i16add;
	float *f32add;
	MatStr create_mat;
	switch (mat_type&MatTypeFlag){
		case i16Flag:
#ifdef Simulation		//仿真模式
			i16add = (int16_t*)malloc(mat_line*mat_row*2);
#else
//内存管理模块
#endif 
			if (i16add != NULL) {		//分配内存检查
				create_mat.SaveAddr = i16add;
				create_mat.flag = i16Flag;
			}
			else {						//分配内存失败
				create_mat.SaveAddr = NULL;
				create_mat.flag = 0;
				create_mat.line = 0;		
				create_mat.row  = 0;
				return create_mat;
			}
			break;
		case f32Flag:
#ifdef Simulation		//仿真模式
			f32add = (float*)malloc(mat_line*mat_row * 4);
#else
//内存管理模块
#endif 		
			if (f32add != NULL) {
				create_mat.SaveAddr = f32add;
				create_mat.flag = f32Flag;
			}
			else {
				create_mat.SaveAddr = NULL;
				create_mat.flag = 0;
				create_mat.line = 0;		
				create_mat.row  = 0;
				return create_mat;
			}
			break;
	default:
		create_mat.SaveAddr = NULL;
		create_mat.flag = 0;
		create_mat.line = 0;
		create_mat.row  = 0;
		return create_mat;
		break;
}
	create_mat.line = mat_line;		//矩阵大小赋值
	create_mat.row  = mat_row;
	return create_mat;
}

//删除矩阵并释放矩阵内存
//mat:要释放的矩阵指针
//return:位宽8标志位
uint8_t mat_delete(MatStr *mat)
{
	if (mat->SaveAddr == NULL) {
		return false;
	}
	switch (mat->flag&MatTypeFlag)
	{
		case i16Flag:
#ifdef Simulation		//仿真模式
			free((int16_t*)mat->SaveAddr);
			mat->SaveAddr = NULL;
#else
//内存管理模块
#endif // Simulation
			break;
		case f32Flag:
#ifdef Simulation		//仿真模式
			free((float*)mat->SaveAddr);
			mat->SaveAddr = NULL;
#else
//内存管理模块
#endif // Simulation
			break;
	default:
		break;
	}
	mat->flag = NULL;
	mat->line = NULL;
	mat->row  = NULL;
	return true;
}

//优化次数:0
//矩阵全员赋值value
//mat:输入赋值矩阵
//value:有效值
//return:位宽8标志位
uint8_t mat_assignment(MatStr *mat,float value)
{
	int16_t *i16add=NULL;
	float *f32add=NULL;
	uint32_t i=0,mat_size=0;
	mat_size = mat->line*mat->row;
	if ((mat->SaveAddr==NULL)||(mat_size==NULL)){			//矩阵地址和大小不能为0
		return false;
	}
	switch (mat->flag&MatTypeFlag){							//矩阵类型判断
	case i16Flag:
		i16add = (int16_t*)mat->SaveAddr;
		for (i = 0; i<mat_size; ++i) {
			*(i16add + i) = (int16_t)value;
		}
		break;
	case f32Flag:
		f32add = (float*)mat->SaveAddr;
		for (i = 0; i<mat_size; ++i) {
			*(f32add + i) = (float)value;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

//优化次数:0
//矩阵全员赋值0
//mat:输入赋值矩阵
//return:位宽8标志位
uint8_t mat_zero(MatStr *mat)
{
	if (mat_assignment(mat, 0))
		return true;
	else
		return false;
}

//优化次数:0
//计算矩阵大小
//mat:输入矩阵
//return:位宽32有效值
uint32_t mat_size(const MatStr *mat)
{
	return (uint32_t)(mat->line*mat->row);
}

//优化次数:0
//求矩阵mat二范数
//mat:输入向量矩阵
//return:返回float有效值
float mat_norm2(const MatStr *mat)
{
	int16_t *i16add;
	uint32_t mat_size=0;
	uint32_t i=0;
	float *f32add,norm2 = 0;
	mat_size=matfi.mat_size(mat);
	if ((mat_size == 0)||(mat->row!=1)) {
		return error;
	}
	switch (MatTypeFlag&mat->flag){
		case i16Flag:
			i16add = (int16_t*)mat->SaveAddr;
			for (i = 0; i < mat_size; ++i){
				norm2 += (float)((*(i16add + i)) * (*(i16add + i)));
			}
			break;
		case f32Flag:
			f32add = (float*)mat->SaveAddr;
			for (i = 0; i < mat_size; ++i) {
				norm2 += (float)((*(f32add + i)) * (*(f32add + i)));
			}
			break;
	default:
		return error;
		break;
	}
	return (float)sqrt(norm2);
}

//优化次数:0
//矩阵相乘
//mat_a:左乘矩阵a
//mat_b:右乘矩阵b
//return:float数据类型的矩阵类
MatStr mat_mult(const MatStr *mat_l,const MatStr *mat_r)
{
	uint16_t l_line = NULL, r_row = NULL, adds = NULL, l_line_offset=NULL,r_row_offset=NULL;
	int16_t *i16mat_l_add=NULL,*i16mat_r_add=NULL;
	float *f32mat_l_add = NULL, *f32mat_r_add = NULL,*remat_add=NULL;
	uint32_t line_offset = NULL;
	MatStr remat;
	if((mat_l->SaveAddr==NULL)||(mat_r->SaveAddr==NULL)||(mat_l->row!=mat_r->line)){		//空矩阵and左乘矩阵列不等于右乘矩阵返回空矩阵
		remat=mat_create(NULL,NULL,NULL);
		return  remat;
	}
	remat = mat_create(mat_l->line,mat_r->row,f32Flag);		//为返回矩阵开辟内存
	mat_zero(&remat);
	remat_add = (float*)remat.SaveAddr;
	switch (mat_l->flag&MatTypeFlag){
		case i16Flag:
			i16mat_l_add = (int16_t*)mat_l->SaveAddr;
			switch (mat_r->flag&MatTypeFlag){
				case i16Flag:
					i16mat_r_add = (int16_t*)mat_r->SaveAddr;
					for (l_line = 0; l_line < mat_l->line; ++l_line) {
						for (r_row = 0; r_row < mat_r->row; ++r_row) {
							for (adds = 0; adds < mat_r->line; ++adds) {
								*(remat_add + line_offset + r_row) += (float)((float)(*(i16mat_l_add+ l_line_offset+adds))*(float)(*(i16mat_r_add+ r_row_offset+r_row)));
								r_row_offset += mat_r->row;
							}
							r_row_offset = NULL;
						}
						line_offset += remat.row;
						l_line_offset += mat_l->row;
					}
					break;
				case f32Flag:
					f32mat_r_add = (float*)mat_r->SaveAddr;
					for (l_line = 0; l_line < mat_l->line; ++l_line) {
						for (r_row = 0; r_row < mat_r->row; ++r_row) {
							for (adds = 0; adds < mat_r->line; ++adds) {
								*(remat_add + line_offset + r_row) += (float)((float)(*(i16mat_l_add + l_line_offset + adds))*(float)(*(f32mat_r_add + r_row_offset + r_row)));
								r_row_offset += mat_r->row;
							}
							r_row_offset = NULL;
						}
						line_offset += remat.row;
						l_line_offset += mat_l->row;
					}
					break;
			default:
				break;
			}
			break;
		case f32Flag:
			f32mat_l_add = (float*)mat_l->SaveAddr;
			switch (mat_r->flag&MatTypeFlag) {
			case i16Flag:
				i16mat_r_add = (int16_t*)mat_r->SaveAddr;
				for (l_line = 0; l_line < mat_l->line; ++l_line) {
					for (r_row = 0; r_row < mat_r->row; ++r_row) {
						for (adds = 0; adds < mat_r->line; ++adds) {
							*(remat_add + line_offset + r_row) += (float)((float)(*(f32mat_l_add + l_line_offset + adds))*(float)(*(i16mat_r_add + r_row_offset + r_row)));
							r_row_offset += mat_r->row;
							printf("1");
						}
						r_row_offset = NULL;
					}
					line_offset += remat.row;
					l_line_offset += mat_l->row;
				}
				break;
			case f32Flag:
				f32mat_r_add = (float*)mat_r->SaveAddr;
				for (l_line = 0; l_line < mat_l->line; ++l_line) {
					for (r_row = 0; r_row < mat_r->row; ++r_row) {
						for (adds = 0; adds < mat_r->line; ++adds) {
							*(remat_add + line_offset + r_row) += (float)((float)(*(f32mat_l_add + l_line_offset + adds))*(float)(*(f32mat_r_add + r_row_offset + r_row)));
							r_row_offset += mat_r->row;
						}
						r_row_offset = NULL;
					}
					line_offset += remat.row;
					l_line_offset += mat_l->row;
				}
				break;
			default:
				break;
			}
			break;
	default:
		break;
	}
	return remat;
}

//优化次数:0
//打印矩阵信息
//mat:输入矩阵
//return:位宽8标志位
uint8_t mat_message(const MatStr *mat)
{
	if (mat->SaveAddr == NULL) {
		return false;
	}
#ifdef Simulation
	printf("矩阵存放地址 = %x\n", (int)mat->SaveAddr);
	if ((mat->flag&MatTypeFlag) == i16Flag) {
		printf("矩阵类型 = int16_t\n");
	}
	else {
		printf("矩阵类型 = float\n");
	}
	printf("line = %d\n",mat->line);
	printf("row  = %d\n",mat->row);
	printf("\n");
#else
//打印函数
#endif // Simulation
	return true;
}