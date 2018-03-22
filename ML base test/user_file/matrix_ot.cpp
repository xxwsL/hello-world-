#include "matrix_ot.h"

MatFistr mat_tf = MatFiInit;

//优化次数:4
//输出float型矩阵
//mat:矩阵
//return:位宽8标志位
bool output(const MatStr *mat)		
{
	uint16_t i = 0, j = 0;								//行和列地址偏移量
	float* f32add;										//float类型矩阵指针
	int16_t* i16add;									//int16_t矩阵指针
	if (mat == NULL) {
		return false;
	}
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
		default:
			return false;
			break;
	}
	return true;
}

//优化次数:3
//把矩阵切割成对应大小
//matrix_a:被切割矩阵a
//matrix_b:切割部分载体
//cut_line_szie:切割行长
//cut_row_size :切割列长
//number:切割目标位置
//return:矩阵结构体(内存管理申请内存,没被释放)
MatStr* mat_cut(const MatStr *mat,uint16_t cut_line_size, uint16_t cut_row_size, uint16_t number, uint16_t remat_type)
{
	uint16_t  i = NULL,j=NULL;
	uint16_t  rows_max=NULL;
	int16_t   *i16mat_add=NULL, *i16remat=NULL;
	float	  *f32mat_add=NULL, *f32remat=NULL;
	MatStr *remat=NULL;
	if (mat == NULL) {
		return false;
	}
	if (cut_line_size <= mat->line || cut_row_size <= mat->row) {
		rows_max = mat->row / cut_row_size;
		switch (mat->flag&MatTypeFlag) {
		case i16Flag:					//切割int16_t类型
			i16mat_add = (int16_t*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//初始切割地址
			switch (remat_type)
			{
				case i16Flag:			//返回int16_t类型
					remat = mat_create(cut_line_size, cut_row_size,i16Flag);
					i16remat =(int16_t*)remat->SaveAddr;				
					for (i = 0; i < cut_line_size; i++) {
						for (j = 0; j < cut_row_size; j++) {
							*(i16remat++) = (int16_t)(*(i16mat_add + j));
						}
						i16mat_add += mat->row;
					}
					remat->flag = i16Flag;
					break;
				case f32Flag:			//返回float类型
					remat = mat_create(cut_line_size, cut_row_size, f32Flag);
					f32remat = (float*)remat->SaveAddr;
					for (i = 0; i < cut_line_size; i++) {
						for (j = 0; j < cut_row_size; j++) {
							*(f32remat++) = (float)(*(i16mat_add + j));
						}
						i16mat_add += mat->row;
					}
					remat->flag = f32Flag;
					break;
				break;
			default:
				return false;
				break;
			}
			break;
		case f32Flag:					//切割float类型
			f32mat_add = (float*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//初始切割地址
			switch (remat_type)
			{
			case i16Flag:				//返回int16_t类型
				remat = mat_create(cut_line_size, cut_row_size, i16Flag);
				i16remat = (int16_t*)remat->SaveAddr;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(i16remat++) = (int16_t)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat->flag = i16Flag;
				break;					//返回float类型
			case f32Flag:
				remat = mat_create(cut_line_size, cut_row_size, f32Flag);
				f32remat = (float*)remat->SaveAddr;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(f32remat++) = (float)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat->flag = f32Flag;
				break;
				break;
			default:
				return false;
				break;
			}
			break;
		default:
			return false;
			break;
		}
	}
	return remat;
}

//优化次数:2
//求矩阵协方差		
//行数:样本个数(样本个数大于1),列数:样本维度
//mat:输入矩阵
//
MatStr* mat_cov(const MatStr *mat)
{
	uint16_t i = 0, j = 0,k=0;
	int16_t *i16mat_add;
	uint32_t line_offset=0,diff_mat_line=0;
	MatStr *remat,*aver_mat,*diff_mat;
	float *f32mat_add;
	if (!mat) {
		return false;
	}
	remat = mat_create(mat->row,mat->row,f32Flag);		//申请内存快注意大小合适
	mat_zero(remat);
	aver_mat = mat_create(1, mat->row, f32Flag);			//注意，注意，注意
	mat_zero(aver_mat);
	diff_mat = mat_create(mat->line,mat->row,f32Flag);
	switch (mat->flag&MatTypeFlag){	
		case i16Flag:										//输入int16_t矩阵
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//样本不同维度总和
				for (j = 0; j < mat->row; j++) {
					*((float*)aver_mat->SaveAddr + j) +=(float)(*(i16mat_add++));		
				}
			}
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//样本不同维度均值
				*((float*)aver_mat->SaveAddr + j) /= mat->line;
			}
			for (i = 0; i < mat->line; i++) {				//样本均差
				for (j = 0; j < mat->row; j++) {
					*((float*)diff_mat->SaveAddr + line_offset + j) = (*(i16mat_add++)) - (*((float*)aver_mat->SaveAddr + j));
				}
				line_offset += mat->row;
			}
			break;
		case f32Flag:										//输入float矩阵
			f32mat_add = (float*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//样本不同维度总和
				for (j = 0; j < mat->row; j++) {
					*((float*)aver_mat->SaveAddr + j) = (*((float*)aver_mat->SaveAddr + j)) + (float)(*(f32mat_add++));
				}
			}
			f32mat_add = (float*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//样本不同维度均值
				*((float*)aver_mat->SaveAddr + j) /= mat->line;;
			}
			for (i = 0; i < mat->line; i++) {				//样本均差
				for (j = 0; j < mat->row; j++) {
					*((float*)diff_mat->SaveAddr + line_offset + j) = (*(f32mat_add++)) - (*((float*)aver_mat->SaveAddr + j));
				}
				line_offset += mat->row;
			}
			break;
		default:return false;
		break;
	}
	line_offset = 0;
	for (i = 0; i < mat->row;i++) {							//求各个维度之间协方差		
		for (j = i; j < mat->row; j++) {
			for (k = 0; k < mat->line; k++) {
				*((float*)remat->SaveAddr + line_offset + j) += (*((float*)diff_mat->SaveAddr +i+ diff_mat_line))*(*((float*)diff_mat->SaveAddr +j+ diff_mat_line));
				diff_mat_line += mat->row;
			}
			diff_mat_line = 0;
			(*((float*)remat->SaveAddr + line_offset + j)) /= (mat->line - 1);
			if (i != j) {
				*((float*)remat->SaveAddr + j*mat->row + i) = (*((float*)remat->SaveAddr + line_offset + j));
			}
		}
		line_offset += mat->row;
	}
	mat_delete(aver_mat);
	mat_delete(diff_mat);
	return remat;
}

//优化次数:0
//创建矩阵(矩阵内存片里的值硬件随机值,需初始化0)
//mat_line:矩阵行数
//mat_row:矩阵列数
//mat_type:矩阵类型
//return:矩阵结构体
MatStr* mat_create(uint16_t mat_line, uint16_t mat_row, uint16_t mat_type)
{
	int16_t *i16add;
	float *f32add;
	MatStr *create_mat;
#ifdef Simulation		//仿真模式
	 create_mat= (MatStr*)malloc(sizeof(MatStr));
#else
//内存管理模块
#endif 
	switch (mat_type&MatTypeFlag){
		case i16Flag:
#ifdef Simulation		//仿真模式
			i16add = (int16_t*)malloc(mat_line*mat_row*2);
#else
//内存管理模块
#endif 
			if ((i16add != NULL)&&(create_mat!=NULL)) {		//分配内存检查
				create_mat->SaveAddr = i16add;
				create_mat->flag = i16Flag;
			}
			else {						//分配内存失败
				return false;
			}
			break;
		case f32Flag:
#ifdef Simulation		//仿真模式
			f32add = (float*)malloc(mat_line*mat_row * 4);
#else
//内存管理模块
#endif 		
			if ((f32add != NULL) && (create_mat != NULL)) {
				create_mat->SaveAddr = f32add;
				create_mat->flag = f32Flag;
			}
			else {
				return false;
			}
			break;
	default:
		return false;
		break;
}
	create_mat->line = mat_line;		//矩阵大小赋值
	create_mat->row  = mat_row;
	return create_mat;
}

//优化次数:1
//删除矩阵并释放矩阵内存
//mat:要释放的矩阵指针
//return:位宽8标志位
bool mat_delete(MatStr *mat)
{
	if (mat == NULL) {
		return false;
	}
	switch (mat->flag&MatTypeFlag)
	{
		case i16Flag:
#ifdef Simulation		//仿真模式
			free((int16_t*)mat->SaveAddr);
			mat->SaveAddr = NULL;
			free(mat);
			mat = NULL;
#else
//内存管理模块
#endif // Simulation
			break;
		case f32Flag:
#ifdef Simulation		//仿真模式
			free((float*)mat->SaveAddr);
			mat->SaveAddr = NULL;
			free(mat);
			mat = NULL;
#else
//内存管理模块
#endif // Simulation
			break;
	default:
		return false;
		break;
	}
	return true;
}

//优化次数:1
//矩阵全员赋值value
//mat:输入赋值矩阵
//value:有效值
//return:位宽8标志位
bool mat_assignment(MatStr *mat,float value)
{
	int16_t *i16add=NULL;
	float *f32add=NULL;
	uint32_t i=0,mat_size=0;
	mat_size = mat->line*mat->row;
	if (!mat){			//矩阵地址和大小不能为0
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

//优化次数:1
//矩阵全员赋值0
//mat:输入赋值矩阵
//return:位宽8标志位
bool mat_zero(MatStr *mat)
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
	if (!mat) {
		return false;
	}
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
	mat_size=mat_tf.mat_size(mat);
	if (!mat) {
		return false;
	}
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
MatStr* mat_mult(const MatStr *mat_l,const MatStr *mat_r)
{
	uint16_t l_line = NULL, r_row = NULL, adds = NULL, l_line_offset=NULL,r_row_offset=NULL;
	int16_t *i16mat_l_add=NULL,*i16mat_r_add=NULL;
	float *f32mat_l_add = NULL, *f32mat_r_add = NULL,*remat_add=NULL;
	uint32_t line_offset = NULL;
	MatStr *remat;
	if((mat_l->SaveAddr==NULL)||(mat_r->SaveAddr==NULL)||(mat_l->row!=mat_r->line)){		//空矩阵and左乘矩阵列不等于右乘矩阵返回空矩阵
		remat=mat_create(NULL,NULL,NULL);
		return remat;
	}
	remat = mat_create(mat_l->line,mat_r->row,f32Flag);		//为返回矩阵开辟内存
	mat_zero(remat);
	remat_add = (float*)remat->SaveAddr;
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
						line_offset += remat->row;
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
						line_offset += remat->row;
						l_line_offset += mat_l->row;
					}
					break;
			default:
				return false;
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
						}
						r_row_offset = NULL;
					}
					line_offset += remat->row;
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
					line_offset += remat->row;
					l_line_offset += mat_l->row;
				}
				break;
			default:
				return false;
				break;
			}
			break;
	default:
		return false;
		break;
	}
	return remat;
}

//优化次数:0
//矩阵相乘
//mat_l:左乘矩阵l
//mat_r:右乘矩阵r
//loadmat:装载矩阵
//return:bool标志位
bool mat_mult_par(const MatStr *mat_l, const MatStr *mat_r,MatStr *loadmat)
{
	uint16_t l_line = NULL, r_row = NULL, adds = NULL, l_line_offset = NULL, r_row_offset = NULL;
	int16_t *i16mat_l_add = NULL, *i16mat_r_add = NULL;
	float *f32mat_l_add = NULL, *f32mat_r_add = NULL, *remat_add = NULL;
	uint32_t line_offset = NULL;
	if ((!mat_l) || (!mat_r)||(!loadmat)) {		//空矩阵and左乘矩阵列不等于右乘矩阵返回空矩阵
		return false;
	}
	if ((mat_l->row != mat_r->line)||(mat_l->line!=loadmat->line)||(mat_r->row!=loadmat->row)) {
		return false;
	}
	mat_zero(loadmat);
	remat_add = (float*)loadmat->SaveAddr;
	switch (mat_l->flag&MatTypeFlag) {
	case i16Flag:
		i16mat_l_add = (int16_t*)mat_l->SaveAddr;
		switch (mat_r->flag&MatTypeFlag) {
		case i16Flag:
			i16mat_r_add = (int16_t*)mat_r->SaveAddr;
			for (l_line = 0; l_line < mat_l->line; ++l_line) {
				for (r_row = 0; r_row < mat_r->row; ++r_row) {
					for (adds = 0; adds < mat_r->line; ++adds) {
						*(remat_add + line_offset + r_row) += (float)((float)(*(i16mat_l_add + l_line_offset + adds))*(float)(*(i16mat_r_add + r_row_offset + r_row)));
						r_row_offset += mat_r->row;
					}
					r_row_offset = NULL;
				}
				line_offset += loadmat->row;
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
				line_offset += loadmat->row;
				l_line_offset += mat_l->row;
			}
			break;
		default:
			return false;
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
					}
					r_row_offset = NULL;
				}
				line_offset += loadmat->row;
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
				line_offset += loadmat->row;
				l_line_offset += mat_l->row;
			}
			break;
		default:
			return false;
			break;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

//优化次数:1
//打印矩阵信息
//mat:输入矩阵
//return:位宽8标志位
bool mat_message(const MatStr *mat)
{
	if (!mat) {
		return false;
	}
#ifdef Simulation
	printf("矩阵存放地址 = %x\n", mat->SaveAddr);
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

//优化次数:0
//矩阵QR分解
//mat:输入矩阵
//q_mat:分解矩阵q
//r_mat:分解矩阵r
//return:bool标志位
bool mat_qr(const MatStr *mat,MatStr *q_mat,MatStr *r_mat)			//debug
{
	uint16_t i = NULL, j = NULL, k = NULL,m=NULL;
	int16_t *mat_i16add=NULL;
	float *buf_a = NULL, *buf_b = NULL,temp=NULL;
	float *mat_f32add=NULL,*q_f32add=NULL,*r_f32add=NULL;
	MatStr *qmat,*rmat,b_mat;
	if (mat == NULL) {
		return false;
	}
#ifdef Simulation
	buf_a = (float*)malloc(mat->line*4);
	buf_b = (float*)malloc(mat->line * 4);
#else
#endif 
	qmat = mat_create(mat->line,mat->row,f32Flag);
	rmat = mat_create(mat->row, mat->row, f32Flag);
	q_f32add = (float*)qmat->SaveAddr;
	r_f32add = (float*)rmat->SaveAddr;
	mat_zero(rmat);
	mat_load(&b_mat,mat->line,1,f32Flag,buf_b);
	switch (mat->flag&MatTypeFlag){
		case i16Flag:
			mat_i16add = (int16_t*)(mat->SaveAddr);
			for (j = 0; j < mat->line; ++j){
				for (i = 0; i < mat->line; ++i){
					buf_a[i] = buf_a[i]= mat_i16add[i * mat->row + j];
				}
				for (k = 0; k < j; ++k)
				{
					r_f32add[k * rmat->row + j] = 0;
					for (m = 0; m < mat->line; ++m){
						r_f32add[k * rmat->row + j] += buf_a[m] * q_f32add[m * qmat->row + k];
					}
					for (m = 0; m < mat->line; ++m){
						buf_b[m] -= r_f32add[k * rmat->row + j] * q_f32add[m * qmat->row + k];
					}
				}
				temp = mat_norm2(&b_mat);
				r_f32add[j * rmat->row + j] = temp;

				for (i = 0; i < mat->line; ++i){
					q_f32add[i * qmat->row + j] = buf_b[i] / temp;
				}
			}
			break;
		case f32Flag:
			mat_f32add = (float*)(mat->SaveAddr);
			for (j = 0; j < mat->line; ++j) {
				for (i = 0; i < mat->line; ++i) {
					buf_a[i] = buf_b[i] = mat_f32add[i * mat->row + j];
				}
				for (k = 0; k < j; ++k)
				{
					r_f32add[k * rmat->row + j] = 0;
					for (m = 0; m < mat->line; ++m) {
						r_f32add[k * rmat->row + j] += buf_a[m] * q_f32add[m * qmat->row + k];
					}
					for (m = 0; m < mat->line; ++m) {
						buf_b[m] -= r_f32add[k * rmat->row + j] * q_f32add[m * qmat->row + k];
					}
				}
				temp = mat_norm2(&b_mat);
				r_f32add[j * rmat->row + j] = temp;

				for (i = 0; i < mat->line; ++i) {
					q_f32add[i * qmat->row + j] = buf_b[i] / temp;
				}
			}
			break;
	default:
		return false;
		break;
	}
#ifdef Simulation
	free(buf_a);
	buf_a = NULL;
	free(buf_b);
	buf_b = NULL;
#else
#endif 
	return true;
}

//优化次数:0
//矩阵加法
//q_mat:左加float矩阵a
//r_mat:右加float矩阵b
//return:float型矩阵
MatStr* mat_add(const MatStr *mat_a,const MatStr *mat_b)
{
	uint32_t i=NULL,matsize=NULL;
	float *f32mata_add = NULL, *f32matb_add = NULL,*f32remat_add;
	MatStr *remat;
	if ((!mat_a) || (!mat_b))
		return false;
	if ((mat_a->line != mat_b->line) || (mat_a->row != mat_b->row))
		return false;
	matsize = mat_size(mat_a);
	f32mata_add = (float*)mat_a->SaveAddr;
	f32matb_add = (float*)mat_b->SaveAddr;
	remat=mat_create(mat_a->line,mat_a->row,f32Flag);
	f32remat_add = (float*)remat->SaveAddr;
		for (i = 0; i <matsize; ++i) {
		*(f32remat_add + i) = *(f32mata_add + i) + (*(f32matb_add + i));
	}
	return remat;
}

//优化次数:0
//矩阵减法
//q_mat:左减float矩阵a
//r_mat:右减float矩阵b
//return:float型矩阵
MatStr* mat_sub(const MatStr *mat_a, const MatStr *mat_b)
{
	uint32_t i = NULL, matsize = NULL;
	float *f32mata_add = NULL, *f32matb_add = NULL, *f32remat_add;
	MatStr *remat;
	if ((!mat_a) || (!mat_b))
		return false;
	if ((mat_a->line != mat_b->line) || (mat_a->row != mat_b->row))
		return false;
	matsize = mat_size(mat_a);
	f32mata_add = (float*)mat_a->SaveAddr;
	f32matb_add = (float*)mat_b->SaveAddr;
	remat = mat_create(mat_a->line, mat_a->row, f32Flag);
	f32remat_add = (float*)remat->SaveAddr;
	for (i = 0; i <matsize; ++i) {
		*(f32remat_add + i) = *(f32mata_add + i) - (*(f32matb_add + i));
	}
	return remat;
}

//优化次数:0
//矩阵减法
//q_mat:左减float矩阵a
//r_mat:右减float矩阵b
//loadmat:载体矩阵
//return:bool型标志
bool mat_sub_par(const MatStr *mat_a, const MatStr *mat_b,MatStr *loadmat)
{
	uint32_t i = NULL, matsize = NULL;
	float *f32mata_add = NULL, *f32matb_add = NULL, *f32remat_add;
	if ((!mat_a) || (!mat_b)||(!loadmat))
		return false;
	if ((mat_a->line != mat_b->line) || (mat_a->row != mat_b->row))
		return false;
	matsize = mat_size(mat_a);
	f32mata_add = (float*)mat_a->SaveAddr;
	f32matb_add = (float*)mat_b->SaveAddr;
	f32remat_add = (float*)loadmat->SaveAddr;
	for (i = 0; i <matsize; ++i) {
		*(f32remat_add + i) = *(f32mata_add + i) - (*(f32matb_add + i));
	}
	return true;
}

//优化次数:0
//矩阵转换
//mat:输入矩阵
//return:与输入矩阵相反类型矩阵
MatStr* mat_change(const MatStr *mat)
{
	uint32_t i = NULL, matsize = NULL;
	int16_t *i16mat_add = NULL,*i16remat_add=NULL;
	float *f32mat_add=NULL,*f32remat_add=NULL;
	MatStr *remat;
	if (!mat->SaveAddr)
		return false;
	matsize = mat_size(mat);
	switch (mat->flag&MatTypeFlag){
		case i16Flag:
			i16mat_add = (int16_t*)mat->SaveAddr;
			remat = mat_create(mat->line, mat->row, f32Flag);
			f32remat_add = (float*)remat->SaveAddr;
			for (i = 0; i < matsize; ++i) {
				*(f32remat_add + i) = (float)(*(i16mat_add+i));
			}
			break;
		case f32Flag:
			f32mat_add = (float*)mat->SaveAddr;
			remat = mat_create(mat->line, mat->row, i16Flag);
			i16remat_add = (int16_t*)remat->SaveAddr;
			for (i = 0; i < matsize; ++i) {
				*(f32remat_add + i) = (int16_t)(*(i16mat_add + i));
			}
			break;
	default:
		return false;
		break;
	}
	return remat;
}

//优化次数:0
//矩阵signmoid函数化
//mat:输入任意类型矩阵
//return:float型矩阵
MatStr* mat_signmoid(const MatStr *mat)
{
	uint16_t lines = NULL, rows = NULL;
	int16_t *i16mat_add = NULL;
	float *f32mat_add = NULL,*f32remat_add=NULL;
	MatStr *remat;
	if (!mat)
		return false;
	remat = mat_create(mat->line,mat->row,f32Flag);
	f32remat_add = (float*)remat->SaveAddr;
	switch (mat->flag&MatTypeFlag){
		case i16Flag:
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (lines = 0; lines < mat->line; ++lines) {
				for (rows = 0; rows < mat->row; ++rows) {
					*(f32remat_add++) = signmoid((float)*(i16mat_add++));
				}
			}
			break;
		case f32Flag:
			f32mat_add = (float*)mat->SaveAddr;
			for (lines = 0; lines < mat->line; ++lines) {
				for (rows = 0; rows < mat->row; ++rows) {
					*(f32remat_add++) = signmoid(*(f32mat_add++));
				}
			}
			break;
	default:
		return false;
		break;
	}
	return remat;
}

//优化次数:0
//矩阵signmoid函数化
//mat:输入任意类型矩阵
//return:bool标志位
//loadmat:装载矩阵
bool mat_signmoid_par(const MatStr *mat,MatStr *loadmat)
{
	uint16_t lines = NULL, rows = NULL;
	int16_t *i16mat_add = NULL;
	float *f32mat_add = NULL, *f32remat_add = NULL;
	if (!mat_proofread(mat,loadmat))
		return false;
	f32remat_add = (float*)loadmat->SaveAddr;
	switch (mat->flag&MatTypeFlag) {
	case i16Flag:
		i16mat_add = (int16_t*)mat->SaveAddr;
		for (lines = 0; lines < mat->line; ++lines) {
			for (rows = 0; rows < mat->row; ++rows) {
				*(f32remat_add++) = signmoid((float)*(i16mat_add++));
			}
		}
		break;
	case f32Flag:
		f32mat_add = (float*)mat->SaveAddr;
		for (lines = 0; lines < mat->line; ++lines) {
			for (rows = 0; rows < mat->row; ++rows) {
				*(f32remat_add++) = signmoid(*(f32mat_add++));
			}
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

//优化次数:0
//把一个数组装载到矩阵上
//mat:存放数据的矩阵类
//line:矩阵的行长
//row:矩阵的列长
//mattype:矩阵的类型
//数据地址
bool mat_load(MatStr *mat,uint16_t line,uint16_t row, uint16_t mattype, void *saveadd)
{
	if ((!mat)||(mat->SaveAddr))
		return false;
	mat->flag = mattype;
	mat->line = line;
	mat->row = row;
	mat->SaveAddr = saveadd;
	return true;
}

//优化次数:0
//两个矩阵校对
//mat_a:输入矩阵a
//mat_b:输入矩阵b
//return:bool型标志位
bool mat_proofread(const MatStr *mat_a, const MatStr *mat_b)
{
	if (!(mat_a&&mat_b))
		return false;
	if ((mat_a->line == mat_b->line) && (mat_a->row == mat_b->row))
		return true;
	else
		return false;
}

//优化次数:0
//矩阵点乘and叉乘
//mat_l:左输入矩阵
//mat_r:有输入矩阵
//loadmat:载体矩阵,参数为0则求叉乘
//return:float型标志或数据
float f32mat_dotmult_par(const MatStr *mat_l,const MatStr *mat_r,MatStr *loadmat)
{
	float *mat_ladd = NULL, *mat_radd = NULL, *loadmat_add = NULL, redate=NULL;
	uint32_t i=NULL,matsize=NULL;
	if ((mat_l->line != mat_r->line) || (mat_l->row != mat_r->row))
		return false;
	matsize = mat_size(mat_l);
	if (!loadmat){
		mat_ladd = (float*)mat_l->SaveAddr;
		mat_radd = (float*)mat_r->SaveAddr;
		for (i = 0; i < matsize; ++i) {
			redate += (*(mat_ladd++))*(*(mat_radd)++);
		}
		return redate;
	}
	else {
		mat_ladd = (float*)mat_l->SaveAddr;
		mat_radd = (float*)mat_r->SaveAddr;
		loadmat_add = (float*)loadmat->SaveAddr;
		for (i = 0; i < matsize; ++i) {
			*(loadmat_add++) = (*(mat_ladd++))*(*(mat_radd)++);
		}
	}
	return true;
}

//优化次数:0
//将一个8byte类型数组里的每一位对应转化为一个向量
//buf:数组地址
//loadmat:装载矩阵矩阵
//return:bool型标志
bool mat_tovector(const uint8_t *buf,MatStr *loadmat)
{
	float l_value = 0.0f,r_value=0.1f;
	float *loadmatadd = NULL;
	uint16_t j = NULL;
	uint32_t i = NULL;
	if (!loadmat)
		return false;
	loadmatadd = (float*)loadmat->SaveAddr;
	for (i = 0; i < loadmat->line;++i) {
		*(loadmatadd + i) = (*(buf + j) & 0x01) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x02) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x04) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x08) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x10) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x20) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x40) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x80) ? l_value : r_value;
		j++;
	}
	return true;
}

//优化次数:0
//矩阵tanh函数化
//mat:输入任意类型矩阵
//return:bool标志位
//loadmat:装载矩阵
bool mat_tanh_par(const MatStr *mat, MatStr *loadmat)
{
	uint16_t lines = NULL, rows = NULL;
	float *f32mat_add = NULL, *f32remat_add = NULL;
	if (!mat_proofread(mat, loadmat))
		return false;
	f32mat_add = (float*)mat->SaveAddr;
	for (lines = 0; lines < mat->line; ++lines) {
		for (rows = 0; rows < mat->row; ++rows) {
			*(f32remat_add++) = (float)tanh(*(f32mat_add++));
		}
	}
	return true;
}


//优化次数:0
//矩阵relu函数化
//mat:输入矩阵
//loadmat:装载矩阵
bool mat_relu_par(const MatStr *mat,MatStr *loadmat)
{
	uint16_t lines = NULL, rows = NULL;
	float *f32mat_add = NULL, *f32remat_add = NULL;
	if (!mat_proofread(mat, loadmat))
		return false;
	f32remat_add = (float*)loadmat->SaveAddr;
		f32mat_add = (float*)mat->SaveAddr;
		for (lines = 0; lines < mat->line; ++lines) {
			for (rows = 0; rows < mat->row; ++rows) {
				*(f32remat_add++) = relu(*(f32mat_add++));
			}
		}
	return true;
}


//优化次数:0
//矩阵似正态随机赋值
//mat:输入矩阵
bool mat_rand_normal(MatStr *mat)
{
	float *f32add = NULL,temp=NULL,tempsum=NULL;
	uint32_t i = 0, mat_size = 0;
	if (!mat) {			//矩阵地址和大小不能为0
		return false;
	}
	mat_size = mat->line*mat->row;
	f32add = (float*)mat->SaveAddr;
		for (i = 0; i < mat_size; ++i) {
			temp = (float)rand();
			tempsum += temp;
			*(f32add + i) = temp;
		}
		temp = tempsum / i;
		for (i = 0; i < mat_size; ++i) {
			f32add[i] = (f32add[i]-temp)/tempsum*100;
		}
	return true;
}


//优化次数:0
//矩阵所有元素偏置一个值
//mat:输入一个矩阵
//value:偏置值
bool mat_addto_value(MatStr *mat, const float value)
{
	float *matadd = NULL;
	uint32_t matszie = NULL,i=NULL;
	if (!mat)
		return false;
	matszie = mat_size(mat);
	matadd = (float*)mat->SaveAddr;
	for (i = 0; i < matszie; ++i) {
		matadd[i] += value;
	}
	return true;
}

//优化次数:0
//矩阵softmax化
//mat:输入矩阵
//loadmat:装载矩阵
bool mat_softmax(const MatStr *mat,MatStr *loadmat) 
{
	uint32_t i = NULL, matszie = NULL;
	float exp_pow_sum = NULL;
	float *f32mat_add = NULL, *f32loadmat_add = NULL;
	if (!mat_proofread(mat, loadmat))
		return false;
	matszie = mat_size(mat);
	f32mat_add = (float*)mat->SaveAddr;
	f32loadmat_add = (float*)loadmat->SaveAddr;
	for (i = 0; i < matszie; ++i) {
		f32loadmat_add[i] = exp_pow(f32mat_add[i]);
		exp_pow_sum += f32loadmat_add[i];
		}
	for (i = 0; i < matszie; ++i) {
		f32loadmat_add[i] /= exp_pow_sum;
	}
	return true;
}

//优化次数:0
//矩阵s所有元素求和
//mat:输入矩阵
//return:double数据
double mat_element_sum(const MatStr *mat)
{
	uint32_t i = NULL,matsize=NULL;
	double sum = NULL;
	float *f32mat_add = NULL;
	if (!mat)
		return false;
	matsize = mat_size(mat);
	f32mat_add = (float*)mat->SaveAddr;
	for (i = 0; i < matsize; ++i) {
			sum += (double)f32mat_add[i];
		}
	return sum;
}

//优化次数:0
//矩阵softmax求导
//mat:输入矩阵
//loadmat:装载矩阵
//addr:求导位置
//return:bool标志位
bool mat_softmax_der(MatStr *mat,MatStr *loadmat,uint32_t addr)
{
	uint32_t i = NULL, matsize = NULL;
	float *mataddr = NULL, *loadmataddr = NULL;
	if (mat_proofread(mat, loadmat)) {
		return true;
		mataddr = (float*)mat->SaveAddr;
		loadmataddr = (float*)loadmat->SaveAddr;
		matsize = mat_size(mat);
		for (i = 0; i < matsize; ++i) {
			loadmataddr[i] = (i == addr) ? (mataddr[i] - 1) : mataddr[i];
		}
		return true;
	}
	return false;
}











































