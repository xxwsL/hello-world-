#include "network.h"

uint8_t train_buf[train_size];

//优化次数:1(不在优化:废弃版本)
//反向传播
//tr:训练模型的类B
//bool back_propaga(TrStr *tr)
//{
//	float error_total = NULL,out_network_dersum=NULL;
//	float *matadd = NULL;
//	float *layer0 = NULL, *layer1 = NULL;
//	float *outmat0 = NULL;
//	float *der_mat0=NULL,*der_mat1 = NULL;
//	uint32_t i=NULL,j=NULL, offset0 =NULL,offset1=NULL,update=NULL;
//	matadd = (float*)tr->train_mat->SaveAddr;
//	layer0 = (float*)tr->layer[0]->SaveAddr;
//	layer1 = (float*)tr->layer[1]->SaveAddr;
//	outmat0 = (float*)tr->outmat[0]->SaveAddr;
//	der_mat0 = (float*)tr->der_mat[0]->SaveAddr;
//	der_mat1 = (float*)tr->der_mat[1]->SaveAddr;
//	while (true){
//		error_total=forward_propaga(tr);
//		if (error_analysis(error_total)) {
//			printf("模型训练完成\n");
//			break;
//		}
//		tr->active_fid[0](tr->outmat[0], tr->der_mat[0], NULL);
//		tr->active_fid[1](tr->outmat[1], tr->der_mat[1], tr->target_load);							//error_der=-(traget_i-out_i)*outi(1-out_i)	
//		offset0 = NULL;offset1 = NULL;										
//		for (i = 0; i < tr->outmat[0]->line; ++i) {														//更新隐藏层权重				
//			for (j = 0; j < tr->layer[1]->line;++j) {
//				out_network_dersum += der_mat1[j] * layer1[offset1 + i];								//out_dersum+=error_der*Wout_network
//				offset1 += tr->layer[1]->row;
//			}
//			offset1 = 0;
//			out_network_dersum = out_network_dersum * der_mat0[i];									//out_dersum=out_dersum*net_o(1-net_o)		
//			for (j = 0; j < tr->layer[0]->row;++j) {
//				layer0[offset0 + j] -= tr->tr_message[3] * out_network_dersum*matadd[j];				//hide_network_j=learm_speed*outdersum*mat_j
//			}
//			offset0 += tr->layer[0]->row;
//			out_network_dersum = NULL;
//		}																								//更新隐藏层完成
//		for (i = 0; i < tr->layer[1]->line; ++i) {													//更新输出层权重
//			for (j = 0; j < tr->layer[1]->row; ++j) {
//				layer1[offset1 + j] -= tr->tr_message[3] * der_mat1[i] * outmat0[j];
//			}
//			offset1 += tr->layer[1]->row;
//		}																								//更新输出层完成
//		printf("迭代次数 = %d\n\n", update++);
//	}
//	return true;
//}


bool back_propaga(ms *tr)
{
	uint16_t update = NULL;
	float error_total = NULL;
	while (true) {
		error_total = forward_propaga(tr);
		if (error_analysis(error_total)) {
			printf("模型训练完成\n");
			break;
		}
		mlp_der(tr); 
		update_all_layer(tr);				
		printf("迭代次数 = %d\n\n", update++);
	}
	return true;
}

//优化次数:3
//前向传播
//tr:训练类
//return:bool标志位
float forward_propaga(ms *tr)
{

	float error_total = NULL;
	uint16_t networks = NULL,i=NULL;
	networks = tr->mlp_message[0];
	mat_mult_par(tr->layer[0], tr->train_mat, tr->outmat[0]);
	mat_addto_value(tr->outmat[0], tr->op_set[1]);							
	tr->active_fi[0](tr->outmat[0], tr->outmat[0]);
	for (i = 1; i <= networks;++i) {
		mat_mult_par(tr->layer[i], tr->outmat[i-1], tr->outmat[i]);						
		mat_addto_value(tr->outmat[i], tr->op_set[i+1]);
		tr->active_fi[1](tr->outmat[i], tr->outmat[i]);
	}
	//打印测试
	output(tr->outmat[networks]);													
	error_total = tr->loss_fi(tr->outmat[networks], tr->target_load);
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
bool Train_start(const char *simaple_file,const uint32_t i,ms *tr)
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
		mat_tovector(train_buf, tr->train_mat);
		f32mat_up_down_change(tr->train_mat);
		tr->target_load = tr->target_set[i];
		back_propaga(tr);
		printf("训练编号 = %d\n", i);
	return true;
}

//优化次数:4
//训练初始化
//tr:训练类
//layer:全链接层集
//target_set:训练期望标签集
//tr_message:训练模型类的信息头
//tr_fi:训练模型激活函数&求导函数集
//return:bool标志位
bool Train_init(ms *tr,MatStr **layer,MatStr **target_set,float *op_set,uint16_t *mlp_message_buf,active_fi_str(fi))
{
	int16_t i = NULL;
	//初始化输入矩阵mat
	tr->train_mat = mat_create(layer[0]->row,1,f32Flag);
	//初始化连接层
	tr->layer = layer;
	//初始化算子
	tr->op_set = op_set;
	//初始化算子
	tr->active_fi = fi;
	//初始化mlp信息
	tr->mlp_message = mlp_message_buf;
	//初始化输出层 & 用正态分部随机数初始化隐藏层 & 初始化微分层
	tr->outmat = mat_vetor_create(tr->mlp_message[0] + 1);
	tr->der_mat = mat_vetor_create(tr->mlp_message[0] + 1);
	for(i = tr->mlp_message[0];i>=0;--i){
		tr->outmat[i] = mat_create(layer[i]->line, 1, f32Flag);
		mat_rand_normal(tr->layer[i]);
		tr->der_mat[i] = mat_create(tr->outmat[i]->line, 1, f32Flag);
	}
	//初始化标签集
	tr->target_set = target_set;
	//初始化损失函数
	switch (tr->mlp_message[2]){
		case sqaure_loss:
			tr->loss_fi = mat_square_loss;
			break;
		case cross_entropy:
			tr->loss_fi = mat_cross_entropy;
			break;
	default:return false;
		break;
	}
	return true;
}

//优化次数:1
//测试泛化
//simaple_file:输入样本文件地址
//i:样本编号
//tr:训练类
bool train_test(const char *simaple_file,const uint32_t i,ms *tr)
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
		mat_tovector(train_buf, tr->train_mat);
		f32mat_up_down_change(tr->train_mat);
		tr->target_load = tr->target_set[i];
		forward_propaga(tr);
	return true;
}

//优化次数:0
//各个连接层微分算子
//tr:训练模型类
//rreturn:bool标志位
bool mlp_der(ms *tr) 
{
	uint16_t i = NULL, mlps = NULL,mlp_l=NULL,mlp_r=NULL;
	uint16_t j = NULL, k = NULL, mlps_temp0 = NULL, mlps_temp1 = NULL;
	uint32_t line_offset = NULL;
	float *der_mataddr = NULL, *r_mlpaddr = NULL,*mlp_waddr=NULL;
	float temp_sum = NULL;
	mlps = (uint16_t)tr->mlp_message[0];
	//最后输出层微分算子
	auto_load_active_fd(mlps, tr);
	tr->active_fid(tr->outmat[mlps], tr->der_mat[mlps], tr->target_load);
	//除最后一层还需微分的层数
	for (i=1; i <= mlps;++i) {
		//确定微分层的元素个数及数据地址赋值
		mlp_l = mlps - i;
		mlps_temp0 = tr->outmat[mlp_l]->line;
		//对各个输出层求导
		auto_load_active_fd(mlp_l, tr);
		tr->active_fid(tr->outmat[mlp_l],tr->der_mat[mlp_l],NULL);
		der_mataddr = (float*)tr->der_mat[mlp_l]->SaveAddr;
		//确定微分算子层元素个数及地址赋值
		mlp_r = mlps - i + 1;
		mlps_temp1 = tr->outmat[mlp_r]->line;
		r_mlpaddr = (float*)tr->der_mat[mlp_r]->SaveAddr;
		mlp_waddr = (float*)tr->layer[mlp_r]->SaveAddr;
		//微分层元素更新个数
		for (j=0; j < mlps_temp0; ++j) {
			//影响层使能元素个数
			for (k = 0; k < mlps_temp1; ++k) {
				temp_sum += r_mlpaddr[k] * mlp_waddr[line_offset + j];
				line_offset += tr->layer[mlp_r]->row;
			}
			der_mataddr[j] *= temp_sum;
			temp_sum = NULL;
			line_offset = NULL;
		}
	}
	return true;
}

//优化次数:0
//更新全部连接层权重
//tr:训练模型类
bool update_all_layer(ms *tr)
{
	uint8_t mlps = NULL,i=NULL;
	mlps = (uint8_t)tr->mlp_message[0];
	update_layer(tr->layer[0],tr->der_mat[0],tr->train_mat,tr);
	for (i = 1; i <= mlps;++i) {
		update_layer(tr->layer[i],tr->der_mat[i],tr->outmat[i-1],tr);
	}
	return true;
}

//优化次数:0
//更新连接层权重
//update_mat:更新权重对象
//der_mat:更新权重对象对应的微分层
//o_mat:更新权重对象对应的影响层
//tr:训练模型类
bool update_layer(MatStr *update_mat,const MatStr *der_mat,const MatStr *o_mat,ms *tr)
{
	uint16_t i = NULL,j=NULL;
	uint32_t line_offset = NULL;
	float *update_mataddr = NULL, *der_mataddr = NULL, *o_mataddr = NULL;
	update_mataddr = (float*)update_mat->SaveAddr;
	der_mataddr = (float*)der_mat->SaveAddr;
	o_mataddr = (float*)o_mat->SaveAddr;
	for (i = 0; i < der_mat->line;++i) {
		for (j = 0; j < update_mat->row;++j) {
			update_mataddr[line_offset + j] -= tr->op_set[0] * der_mataddr[i] * o_mataddr[j];
		}
		line_offset += update_mat->row;
	}
	return true;
}

//优化次数:0
//自动装载求导函数
//i:输出层对应层数
//tr:全链接网络类
bool auto_load_active_fd(uint16_t i,ms *tr)
{
	if ((uint64_t)tr->active_fi[i] == (uint64_t)mat_signmoid_par)
		tr->active_fid = signmoid_fd;
	else if ((uint64_t)tr->active_fi[i] == (uint64_t)mat_tanh_par)
		tr->active_fid = tanh_fd;
	else if ((uint64_t)tr->active_fi[i] == (uint64_t)mat_relu_par)
		tr->active_fid = relu_fd;
	else if ((uint64_t)tr->active_fi[i] == (uint64_t)mat_softmax_par)
		tr->active_fid = softmax_fd;
	else
		return false;
	return true;
}














