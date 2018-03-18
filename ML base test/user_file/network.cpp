#include "network.h"

//优化次数:0
//反向传播
//mat:输入样本矩阵
//hide_network_mat:影藏层矩阵
//out_network_mat:输出层矩阵
//target_mat:期望输出矩阵
bool back_propaga(const MatStr *mat,MatStr *hide_network_mat,MatStr *out_nework_mat,const MatStr *target_mat,float learm_speed)
{
	bool (*active_fi) (const struct MatrixStr *mat,struct MatrixStr *loadmat);
	float (*active_derfi) (float x);
	float error_total = NULL,out_network_dersum=NULL;
	float *out_matadd = NULL, *error_matadd = NULL, *out_nework_matadd = NULL, *neth_matadd = NULL, *error_der = NULL;
	float *hide_network_matadd = NULL,*matadd=NULL;
	uint32_t i=NULL,j=NULL, offset0 =NULL,offset1=NULL,update=NULL;
	MatStr *neth_mat=NULL,*out_mat=NULL,*error_mat=NULL;
	neth_mat = mat_create(hide_network_mat->line, mat->row, f32Flag);
	out_mat = mat_create(target_mat->line, target_mat->row, f32Flag);
	error_mat= mat_create(target_mat->line, target_mat->row, f32Flag);
#ifdef Simulation
	error_der = (float*)malloc(target_mat->line*4);
#else
#endif // Simulation
	if (!(out_mat&&error_mat&&neth_mat&&error_der))
		return false;
	matadd = (float*)mat->SaveAddr;
	hide_network_matadd = (float*)hide_network_mat->SaveAddr;
	neth_matadd = (float*)neth_mat->SaveAddr;
	out_matadd = (float*)out_mat->SaveAddr;
	error_matadd = (float*)error_mat->SaveAddr;
	out_nework_matadd = (float*)out_nework_mat->SaveAddr;
#ifdef signmoid_active
	active_fi = mat_signmoid_par;
	active_derfi = signmoid_der;
#endif
#ifdef tanh_active
	active_fi = mat_tanh_par;
	active_derfi = tanh_der;
#endif
#ifdef relu_active
	active_fi = mat_relu_par;
	active_derfi = relu_der;
#endif 
	while (true){
		mat_mult_par(hide_network_mat, mat, neth_mat);								//输入层*隐藏层=neth层
		mat_addto_value(neth_mat,hide_bias);
		active_fi(neth_mat, neth_mat);												//neth层经过signmoid函数压缩
		mat_mult_par(out_nework_mat, neth_mat, out_mat);							//out_neth*输出层=out_mat
		mat_addto_value(out_mat, out_bias);
		active_fi(out_mat,out_mat);													//out_neth进过signmoid函数压缩
		//output(out_nework_mat);
		//output(neth_mat);
		output(out_mat);//打印测试
		//output(mat);
		mat_sub_par(target_mat, out_mat, error_mat);

		error_total = f32mat_dotmult_par(error_mat, error_mat, NULL);
		printf("误差 = %f\n",error_total);
		//break;
		if (error_analysis(error_total)) {
			printf("模型训练完成\n");
			break;
		}
		offset0 = NULL;offset1 = NULL;
		for (i = 0; i < out_nework_mat->line; ++i) {													//计算输出层误差
			*(error_der +i) = (-(*(error_matadd + i)))*active_derfi(*(out_matadd+i));						//error_der=-(traget_i-out_i)*outi(1-out_i)
		}																
		for (i = 0; i < neth_mat->line; ++i) {															//更新隐藏层权重				
			for (j = 0; j < out_nework_mat->line;++j) {
				out_network_dersum += (*(error_der + j))*(*(out_nework_matadd + offset1 + i));			//out_dersum+=error_der*Wout_network
				offset1 += out_nework_mat->row;
			}
			offset1 = 0;
			out_network_dersum = out_network_dersum*active_derfi(*(neth_matadd + i));						//out_dersum=out_dersum*net_o(1-net_o)		
			for (j = 0; j < hide_network_mat->row;++j) {
				*(hide_network_matadd + offset0 + j) -= learm_speed*out_network_dersum*(*(matadd + j));	//hide_network_j=learm_speed*outdersum*mat_j
			}
			offset0 += hide_network_mat->row;
			out_network_dersum = NULL;
		}																					//更新隐藏层完成
		for (i = 0; i < out_nework_mat->line; ++i) {										//更新输出层权重
			for (j = 0; j < out_nework_mat->row; ++j) {
				*(out_nework_matadd + offset1 + j) -= learm_speed*(*(error_der +i))*(*(neth_matadd + j));
			}
			offset1 += out_nework_mat->row;
		}																					//更新输出层完成
		printf("迭代次数 = %d\n\n", update++);
	}
#ifdef Simulation
	free(error_der);
	error_der = NULL;
#else
#endif // Simulation
	mat_delete(neth_mat);
	mat_delete(out_mat);
	mat_delete(error_mat);
	return true;
}

//优化次数:0
//前向传播
//mat:输入样本矩阵
//hide_network_mat:影藏层矩阵
//out_network_mat:输出层矩阵
//target_mat:期望输出矩阵
bool forward_propaga(const MatStr *mat, MatStr *hide_network_mat, MatStr *out_nework_mat, const MatStr *target_mat)
{
	bool(*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
	float error_total = NULL;
	MatStr *neth_mat = NULL, *out_mat = NULL, *error_mat = NULL;
	neth_mat = mat_create(hide_network_mat->line, mat->row, f32Flag);
	out_mat = mat_create(target_mat->line, target_mat->row, f32Flag);
	error_mat = mat_create(target_mat->line, target_mat->row, f32Flag);
	if (!(neth_mat&&out_mat&&error_mat))
		return false;
#ifdef signmoid_active
	active_fi = mat_signmoid_par;
#endif
#ifdef tanh_active
	active_fi = mat_tanh_par;
#endif
#ifdef relu_active
	active_fi = mat_relu_par;
#endif 
		mat_mult_par(hide_network_mat, mat, neth_mat);										//输入层*隐藏层=neth层
		active_fi(neth_mat, neth_mat);														//neth层经过signmoid函数压缩
		mat_mult_par(out_nework_mat, neth_mat, out_mat);									//out_neth*输出层=out_mat
		active_fi(out_mat, out_mat);														//out_neth进过signmoid函数压缩
		output(out_mat);//打印测试
		mat_sub_par(target_mat, out_mat, error_mat);
		error_total = f32mat_dotmult_par(error_mat, error_mat, NULL);
		printf("误差 = %f\n", error_total);
	mat_delete(neth_mat);
	mat_delete(out_mat);
	mat_delete(error_mat);
	return true;
}

//优化次数:0
//误差分析
//error_value:误差值
//return:bool标志位
bool error_analysis(float error_value)
{
	if (error_value < error_scope)
		return true;
	else
		return false;
}