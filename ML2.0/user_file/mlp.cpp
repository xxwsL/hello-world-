#include "mlp.h"

//优化次数:5
//训练初始化
//tr:训练类
//layer:全链接层集
//target_set:训练期望标签集
//tr_message:训练模型类的信息头
//tr_fi:训练模型激活函数&求导函数集
//return:int标志位
int mlp_init(mlpstr *mlp, float op, active_fi_str(fi), TensorStr *layer)
{
	int16_t i = NULL;
	//初始化连接层
	mlp->layer = layer;
	//初始化算子
	mlp->op = op;
	//初始化算子
	mlp->active_fi = fi;
	//初始化输出层 & 用正态分部随机数初始化隐藏层 & 初始化微分层	
		mlp->outmat->mat[0] = mat_create(layer->mat[0]->line, 1, f32Flag);
		mat_rand_normal(mlp->layer->mat[0]);
		mlp->gr_mat->mat[0] = mat_create(mlp->outmat->mat[0]->line, 1, f32Flag);
		//激活函数求导函数装载
		if ((void*)mlp->active_fi == (void*)mat_signmoid_par)
			//signmoid
			mlp->active_fid = signmoid_fd;
		else if ((void*)mlp->active_fi == (void*)mat_tanh_par)
			//tanh
			mlp->active_fid = tanh_fd;
		else if ((void*)mlp->active_fi == (void*)mat_relu_par)
			//relu
			mlp->active_fid = relu_fd;
		else if ((void*)mlp->active_fi == (void*)mat_softmax_par)
			//softmax
			mlp->active_fid = softmax_fd;
		else
			mlp->active_fid = NULL;
	return true;
}

//优化次数:0
//单节点mlp前向过程
//mlp:mlp节点
//inmat:输入矩阵
int mlp_one_op(void *mlp_add,TensorStr *inmat)
{
	MlpStr *mlp = (MlpStr*)mlp_add;
	mat_mult_par(mlp->layer->mat[0], inmat->mat[0], mlp->outmat->mat[0]);
	mat_addto_value(mlp->outmat->mat[0], mlp->op);
	mlp->active_fi(mlp->outmat->mat[0], mlp->outmat->mat[0]);
	return true;
}

//优化次数:0
//op:偏置算子
//fi:激活函数
//line:行长
//row:列长
//return:MlpStr指针
//创建mlp数据域
MlpStr *mlp_create(float op, active_fi_str(fi), uint16_t line, uint16_t row)
{
	MlpStr *remlp = NULL;
	//申请mlp内存
	remlp = (MlpStr*)malloc(sizeof(MlpStr));
	if(remlp){
		//分配张量容量
		remlp->layer = tensor_create(line, row, 1);
		remlp->outmat = tensor_create(line, 1, 1);
		remlp->gr_mat = tensor_create(line, row, 1);
		//如果分配失败
		if ((!remlp->layer) || (!remlp->gr_mat) || (!remlp->outmat)) {
			tensor_delete(remlp->layer);
			tensor_delete(remlp->outmat);
			tensor_delete(remlp->gr_mat);
			free(remlp);
			remlp = NULL;
			return false;
		}
		//初始化输出层 & 用正态分部随机数初始化隐藏层 & 初始化微分层	
		remlp->layer->mat[0] = mat_create(line, row, f32Flag);
		remlp->outmat->mat[0] = mat_create(line, 1, f32Flag);
		remlp->gr_mat->mat[0] = mat_create(line, row, f32Flag); 
		mat_zero(remlp->gr_mat->mat[0]);
		mat_rand_normal(remlp->layer->mat[0]);
		remlp->op = op;
		remlp->active_fi = fi;
		//激活函数求导函数装载
		if ((void*)remlp->active_fi == (void*)mat_signmoid_par)
			//signmoid
			remlp->active_fid = signmoid_fd;
		else if ((void*)remlp->active_fi == (void*)mat_tanh_par)
			//tanh
			remlp->active_fid = tanh_fd;
		else if ((void*)remlp->active_fi == (void*)mat_relu_par)
			//relu
			remlp->active_fid = relu_fd;
		else if ((void*)remlp->active_fi == (void*)mat_softmax_par)
			//softmax
			remlp->active_fid = softmax_fd;
		else
			remlp->active_fid = NULL;
	}
	return remlp;
}

//优化次数:0
//mlp_add:mlp地址
//return:int标志
//content:要打印的内容
//打印mlp
int mlp_output(void *mlp_add , uint8_t content) 
{
	MlpStr *mlp = (MlpStr*)mlp_add;
	char fi[] = "mlp_fi = " ;
	char fid[] = "mlp_fid = ";
	if (content&_mlp_layer) {
		//打印layer
		cout << "_mlp_layer = " << endl;
		tensor_output(mlp->layer);
	}
	if (content&_mlp_outmat) {
		//打印out_mat
		cout << "mlp_out_mat = " << endl;
		tensor_output(mlp->outmat);
	}
	if (content&_mlp_gr_mat) {
		//打印gr_mat
		cout << "mlp_gr_mat = " << endl;
		tensor_output(mlp->gr_mat);
	}
	if (content&_mlp_op) {
		//打印偏置算子
		cout << "mlp_op = " << mlp->op << endl<<endl;
	}
	if (content&_mlp_fi) {
		//激活函数求导函数装载
		if ((void*)mlp->active_fi == (void*)mat_signmoid_par)
			//signmoid
			cout << fi << "signmoid" << endl << endl;
		else if ((void*)mlp->active_fi == (void*)mat_tanh_par)
			//tanh
			cout << fi << "tanh" << endl << endl;
		else if ((void*)mlp->active_fi == (void*)mat_relu_par)
			//relu
			cout << fi << "relu" << endl << endl;
		else if ((void*)mlp->active_fi == (void*)mat_softmax_par)
			//softmax
			cout << fi << "softmax" << endl << endl;
		else
			cout << fi << "NULL" << endl << endl;
	}
	if (content&_mlp_fid) {
		//激活函数求导函数装载
		if ((void*)mlp->active_fid == (void*)signmoid_fd)
			//signmoid
			cout << fid << "= signmoid_der" << endl << endl;
		else if ((void*)mlp->active_fid == (void*)tanh_fd)
			//tanh
			cout << fid << "tanh_der" << endl << endl;
		else if ((void*)mlp->active_fid == (void*)relu_fd)
			//relu
			cout << fid << "relu_der" << endl << endl;
		else if ((void*)mlp->active_fid == (void*)softmax_fd)
			//softmax
			cout << "fid" << "softmax_der" << endl << endl;
		else
			cout << fid <<  "NULL" << endl << endl;
	}

	return true;
}

//优化次数:0
//tensor:输入张量
//r_mlp:mlp
//各个连接层梯度
int mlp_gr(TensorStr *tensor, MlpStr *r_mlp)
{
	uint16_t i = NULL, j = NULL, nums_0 = NULL, nums_1 = NULL;
	uint32_t line_offset0 = NULL;
	float  *mat0 = NULL, *mat1 = NULL, *mat2 = NULL;

	//梯度矩阵的行长
	nums_0 = r_mlp->gr_mat->mat[0]->line;
	//梯度矩阵的列长
	nums_1 = r_mlp->gr_mat->mat[0]->row;
	//r_mlp的输出矩阵指针(作为微分矩阵装载体)
	mat0 = (float*)r_mlp->outmat->mat[0]->SaveAddr;
	//当前层layer矩阵指针
	mat1 = (float*)tensor->mat[0]->SaveAddr;
	//梯度矩阵数据指针
	mat2 = (float*)r_mlp->gr_mat->mat[0]->SaveAddr;
	//更新梯度矩阵
	for (; i < nums_0; ++i) {
		for (; j < nums_1; ++j) {
			mat2[line_offset0 + j] = mat0[i] * mat1[j];
		}
		line_offset0 += nums_1;
	}
	return true;
}

//优化:0
//l_mlp:当前mlp层
//r_mlp:上一mlp层
//输出误差传递
int mlp_error_pass(MlpStr *l_mlp, MlpStr* r_mlp)
{
	uint16_t  i = NULL, j = NULL, nums_0 = NULL, nums_1 = NULL;
	float *mat_0 = NULL, *mat_1 = NULL, *mat_2 = NULL, sum_temp_0 = NULL;
	uint32_t line_offset0 = NULL;

	//l_mlp输出矩阵的行长(更新的误差个数)
	nums_0 = l_mlp->outmat->mat[0]->line;
	//r_mlp输出矩阵的行长(每更新一个误差进行的加法数)
	nums_1 = r_mlp->outmat->mat[0]->line;
	//当前层要更新的误差矩阵的载体
	mat_0 = (float*)l_mlp->outmat->mat[0]->SaveAddr;
	//权重矩阵,用于更新误差矩阵
	mat_1 = (float*)r_mlp->layer->mat[0]->SaveAddr;
	//上一层误差矩阵载体
	mat_2 = (float*)r_mlp->outmat->mat[0]->SaveAddr;
	//当前输出层激活函数求导过程
	l_mlp->active_fid(l_mlp->outmat->mat[0],l_mlp->outmat->mat[0],NULL);
	//更新并传递误差
	for (i = NULL; i < nums_0; ++i) {
		for (j = NULL; j < nums_1; ++j) {
			sum_temp_0 += mat_2[j] * mat_1[line_offset0 + i];
			line_offset0 += nums_0;
		}
		line_offset0 = NULL;
		mat_0[i] *= sum_temp_0;
	}
	return true;
}

//优化:0
//mlp:mlp
//learmspeed:学习速率
//更新mlp网络权重
int mlp_update(MlpStr *mlp,float learmspeed)
{
	uint32_t i = NULL,nums_0=mat_size(mlp->layer->mat[0]);
	float *mat_0 = (float*)mlp->layer->mat[0]->SaveAddr, *mat_1 = (float*)mlp->gr_mat->mat[0]->SaveAddr;
	for (; i < nums_0; ++i) {
		mat_0[i] -= learmspeed * mat_1[i];
	}
	return true;
}