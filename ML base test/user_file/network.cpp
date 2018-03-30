#include "network.h"

uint8_t train_buf[train_size];

//优化次数:0
//反向传播
//mat:输入样本矩阵
//hide_network_mat:影藏层矩阵
//out_network_mat:输出层矩阵
//target_mat:期望输出矩阵
bool back_propaga(TrStr *tr)
{
	float error_total = NULL,out_network_dersum=NULL;
	float *matadd = NULL;
	float *layer0 = NULL, *layer1 = NULL;
	float *outmat0 = NULL;
	float *error_mat0=NULL,*error_mat1 = NULL;
	uint32_t i=NULL,j=NULL, offset0 =NULL,offset1=NULL,update=NULL;
	matadd = (float*)tr->mat->SaveAddr;
	layer0 = (float*)tr->layer[0]->SaveAddr;
	layer1 = (float*)tr->layer[1]->SaveAddr;
	outmat0 = (float*)tr->outmat[0]->SaveAddr;
	error_mat0 = (float*)tr->error_mat[0]->SaveAddr;
	error_mat1 = (float*)tr->error_mat[1]->SaveAddr;
	while (true){
		error_total=forward_propaga(tr);
		if (error_analysis(error_total)) {
			printf("模型训练完成\n");
			break;
		}
		tr->active_fid[0](tr->outmat[0], tr->error_mat[0], NULL);
		tr->active_fid[1](tr->outmat[1], tr->error_mat[1], tr->target);									//error_der=-(traget_i-out_i)*outi(1-out_i)	
		offset0 = NULL;offset1 = NULL;										
		for (i = 0; i < tr->outmat[0]->line; ++i) {														//更新隐藏层权重				
			for (j = 0; j < tr->layer[1]->line;++j) {
				out_network_dersum += error_mat1[j] * layer1[offset1 + i];								//out_dersum+=error_der*Wout_network
				offset1 += tr->layer[1]->row;
			}
			offset1 = 0;
			out_network_dersum = out_network_dersum * error_mat0[i];									//out_dersum=out_dersum*net_o(1-net_o)		
			for (j = 0; j < tr->layer[0]->row;++j) {
				layer0[offset0 + j] -= tr->tr_message[2] * out_network_dersum*matadd[j];				//hide_network_j=learm_speed*outdersum*mat_j
			}
			offset0 += tr->layer[0]->row;
			out_network_dersum = NULL;
		}																								//更新隐藏层完成
		for (i = 0; i < tr->layer[1]->line; ++i) {													//更新输出层权重
			for (j = 0; j < tr->layer[1]->row; ++j) {
				layer1[offset1 + j] -= tr->tr_message[2] * error_mat1[i] * outmat0[j];
			}
			offset1 += tr->layer[1]->row;
		}																								//更新输出层完成
		printf("迭代次数 = %d\n\n", update++);
	}
	return true;
}

//优化次数:3
//前向传播
//tr:训练类
//return:bool标志位
float forward_propaga(TrStr *tr)
{
	float error_total = NULL;
	mat_mult_par(tr->layer[0], tr->mat, tr->outmat[0]);										//输入层*隐藏层=neth层
	mat_addto_value(tr->outmat[0], tr->tr_message[0]);
	//output(tr->outmat[0]);printf("\n");		//debug outmat[0]
	tr->active_fi[0](tr->outmat[0], tr->outmat[0]);											//neth层经过signmoid函数压缩
	mat_mult_par(tr->layer[1], tr->outmat[0], tr->outmat[1]);								//out_neth*输出层=out_mat
	//output(tr->outmat[0]);printf("\n");		//debug outmat[0]
	//output(tr->outmat[1]); printf("\n");		//debug outmat[1]		
	mat_addto_value(tr->outmat[1], tr->tr_message[1]);
	tr->active_fi[1](tr->outmat[1], tr->outmat[1]);											//out_neth进过signmoid函数压缩
	output(tr->outmat[1]);																	//打印测试
	mat_sub_par(tr->target, tr->outmat[1],tr->error_mat[1]);
	error_total = f32mat_dotmult_par(tr->error_mat[1], tr->error_mat[1], NULL);				//总误差
	printf("误差 = %f\n", error_total);
	return error_total;
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

//优化次数:1
//训练开始
//simaple_file:样本文件路径
//simaples:样本数量
//train_buf:训练样本容器buf
//train_size:容器大小
//tr:训练类
bool Train_start(const char *simaple_file,const uint32_t i,TrStr *tr)
{
	char bmp_data[100] = {};
	char bmp_name[9] = {};
		if (i < 10) {
			bmp_name[0] = (char)(i + 48); 
			bmp_name[1] = '.'; bmp_name[2] = 'b'; bmp_name[3] = 'm'; bmp_name[4] = 'p';
		}
		else if (i < 100) {
			bmp_name[0] = (char)(i / 10 + 48);
			bmp_name[1] = (char)(i % 10 + 48);
			bmp_name[2] = '.';bmp_name[3] = 'b';bmp_name[4] = 'm';bmp_name[5] = 'p';
		}
		else if (i < 1000) {
			bmp_name[0] = (char)(i / 100 + 48);
			bmp_name[1] = (char)(i / 10 % 10 + 48);
			bmp_name[2] = (char)(i % 10 + 48);
			bmp_name[3] = '.';bmp_name[4] = 'b';bmp_name[5] = 'm';bmp_name[6] = 'p';
		}
		else if (i < 10000) {
			bmp_name[0] = (char)(i / 1000 + 48);
			bmp_name[1] = (char)(i / 100 % 10 + 48);
			bmp_name[2] = (char)(i / 10 % 10 + 48);
			bmp_name[3] = (char)(i % 10 + 48);
			bmp_name[4] = '.';bmp_name[5] = 'b';bmp_name[6] = 'm';bmp_name[7] = 'p';
		}
		else if (i < 100000) {
			bmp_name[0] = (char)(i / 10000 + 48);
			bmp_name[1] = (char)(i / 1000 % 10 + 48);
			bmp_name[2] = (char)(i / 100 % 10 + 48);
			bmp_name[3] = (char)(i / 10 % 10 + 48);
			bmp_name[4] = (char)(i % 10 + 48);
			bmp_name[5] = '.';bmp_name[6] = 'b';bmp_name[7] = 'm';bmp_name[8] = 'p';
		}
		sprintf(bmp_data, "%s%s", simaple_file, bmp_name);
		bmp_r_tobuf(bmp_data, train_buf, train_size);
		mat_tovector(train_buf, tr->mat);
		tr->target = tr->target_set[i];
		back_propaga(tr);
		printf("训练编号 = %d\n", i);
	return true;
}

//优化次数:0
//训练初始化
//tr:训练类
//hide_mat:隐藏层矩阵
//end_mat:输出层矩阵
//bias_Lspeed:偏置值和学习速率
//ac_fi0:隐藏层激活函数标志
//ac_fi1:输出层激活函数标志
bool Train_init(TrStr *tr,MatStr *hide_mat,MatStr *end_mat,MatStr **target_set,float *tr_message,uint8_t ac_fi0,uint8_t ac_fi1)
{
	uint8_t i = NULL;
	//初始化输入矩阵mat
	tr->mat = mat_create(hide_mat->row,1,f32Flag);
	//初始化隐藏层(0)&输出层网络矩阵(1)
	tr->layer[0] = hide_mat;
	tr->layer[1] = end_mat;
	//初始化隐藏层偏置(0)&输出层偏置偏置(1)&学习速率(2)
	tr->tr_message = tr_message;
	//初始化隐藏层输出矩阵(0)&输出层矩阵(1)
	tr->outmat[0] = mat_create(hide_mat->line, tr->mat->row, f32Flag);
	tr->outmat[1] = mat_create(end_mat->line, tr->outmat[0]->row, f32Flag);
	//初始化标签集
		tr->target_set = target_set;
	//以似正态分布随机数初始化神经网络
	mat_rand_normal(tr->layer[0]);		
	mat_rand_normal(tr->layer[1]);
	//初始化误差矩阵
	tr->error_mat[0] = mat_create(tr->outmat[0]->line,tr->outmat[0]->row,f32Flag);
	tr->error_mat[1] = mat_create(tr->outmat[1]->line,tr->outmat[1]->row,f32Flag);
	//初始化隐藏层激活函数&输出层激活函数
	switch (ac_fi0) {
		case signmoid_active:
			tr->active_fi[0]= mat_signmoid_par;
			tr->active_fid[0] = mat_signmoid_der;
			break;
		case tanh_active:
			tr->active_fi[0] = mat_tanh_par;
			tr->active_fid[0] = mat_tanh_der;
			break;
		case relu_active:
			tr->active_fi[0] = mat_relu_par;
			tr->active_fid[0] = mat_relu_der;
			break;
		default:return false; break;
	}
	switch (ac_fi1) {
	case signmoid_active:
		tr->active_fi[1] = mat_signmoid_par;
		tr->active_fid[1] = mat_signmoid_der;
		break;
	case tanh_active:
		tr->active_fi[1] = mat_tanh_par;
		tr->active_fid[1] = mat_tanh_der;
		break;
	case relu_active:
		tr->active_fi[1] = mat_relu_par;
		tr->active_fid[1] = mat_relu_der;
		break;
	case softmax_active:
		//tr->active_fi[1] = mat_softmax_par;
		tr->active_fi[1] = mat_softmax_submax_par;
		tr->active_fid[1] = mat_softmax_der;
		break;
	default:return false; break;
	}
	return true;
}

//优化次数:0
//测试泛化
//simaple_file:输入样本文件地址
//i:样本编号
//tr:训练类
//target:期望矩阵
bool train_test(const char *simaple_file,const uint32_t i,TrStr *tr)
{
	char bmp_data[100] = {};
	char bmp_name[9] = {};
		if (i < 10) {
			bmp_name[0] = (char)(i + 48);
			bmp_name[1] = '.'; bmp_name[2] = 'b'; bmp_name[3] = 'm'; bmp_name[4] = 'p';
		}
		else if (i < 100) {
			bmp_name[0] = (char)(i / 10 + 48);
			bmp_name[1] = (char)(i % 10 + 48);
			bmp_name[2] = '.'; bmp_name[3] = 'b'; bmp_name[4] = 'm'; bmp_name[5] = 'p';
		}
		else if (i < 1000) {
			bmp_name[0] = (char)(i / 100 + 48);
			bmp_name[1] = (char)(i / 10 % 10 + 48);
			bmp_name[2] = (char)(i % 10 + 48);
			bmp_name[3] = '.'; bmp_name[4] = 'b'; bmp_name[5] = 'm'; bmp_name[6] = 'p';
		}
		else if (i < 10000) {
			bmp_name[0] = (char)(i / 1000 + 48);
			bmp_name[1] = (char)(i / 100 % 10 + 48);
			bmp_name[2] = (char)(i / 10 % 10 + 48);
			bmp_name[3] = (char)(i % 10 + 48);
			bmp_name[4] = '.'; bmp_name[5] = 'b'; bmp_name[6] = 'm'; bmp_name[7] = 'p';
		}
		else if (i < 100000) {
			bmp_name[0] = (char)(i / 10000 + 48);
			bmp_name[1] = (char)(i / 1000 % 10 + 48);
			bmp_name[2] = (char)(i / 100 % 10 + 48);
			bmp_name[3] = (char)(i / 10 % 10 + 48);
			bmp_name[4] = (char)(i % 10 + 48);
			bmp_name[5] = '.'; bmp_name[6] = 'b'; bmp_name[7] = 'm'; bmp_name[8] = 'p';
		}
		sprintf(bmp_data, "%s%s", simaple_file, bmp_name);
		bmp_r_tobuf(bmp_data, train_buf, train_size);
		mat_tovector(train_buf, tr->mat);
		tr->target = tr->target_set[i];
		forward_propaga(tr);
	return true;
}