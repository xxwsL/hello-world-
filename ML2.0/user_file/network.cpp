#include "network.h"

uint8_t train_buf[train_size];


//优化次数:3
//前向传播
//tr:训练类
//return:int标志位
float forward_propaga(train *train)
{

	float error_total = NULL;
	//uint16_t networks = NULL,i=NULL;
	//mlp *mlp_add = NULL;
	//networks = tr->tr_message[4];
	//tr->load_in = tr->train_mat;
	//for (i = 0; i <= networks;++i) {
	//	forward_propaga_step(tr, i);
	//}
	//mlp_add = (mlp*)tr->graph_set[networks]->graph_add;
	////打印测试
	//output(mlp_add->outmat);													
	//error_total = tr->loss_fi(mlp_add->outmat, tr->target_load);
	//printf("误差 = %f\n", error_total);
	return error_total;
}

//优化次数:0
//误差分析
//error_value:误差值
//return:int标志位
int error_analysis(float error_value)
{
	//if (error_value < error_scope)
	//	return true;
	//else
		return false;
}

//优化次数:1
//训练开始
//simaple_file:样本文件路径
//simaples:样本数量
//train_buf:训练样本容器buf
//train_size:容器大小
//tr:训练类
int Train_start(const char *simaple_file,const uint32_t i,train *train)
{
	//char bmp_data[100] = {};
	//char bmp_name[9] = {};
	//	if (i < 10) {
	//		bmp_name[0] = (char)(i + 48); 
	//		bmp_name[1] = '.'; bmp_name[2] = 'b'; bmp_name[3] = 'm'; bmp_name[4] = 'p';
	//	}
	//	else if (i < 100) {
	//		bmp_name[0] = (char)(i / 10 + 48);
	//		bmp_name[1] = (char)(i % 10 + 48);
	//		bmp_name[2] = '.';bmp_name[3] = 'b';bmp_name[4] = 'm';bmp_name[5] = 'p';
	//	}
	//	else if (i < 1000) {
	//		bmp_name[0] = (char)(i / 100 + 48);
	//		bmp_name[1] = (char)(i / 10 % 10 + 48);
	//		bmp_name[2] = (char)(i % 10 + 48);
	//		bmp_name[3] = '.';bmp_name[4] = 'b';bmp_name[5] = 'm';bmp_name[6] = 'p';
	//	}
	//	else if (i < 10000) {
	//		bmp_name[0] = (char)(i / 1000 + 48);
	//		bmp_name[1] = (char)(i / 100 % 10 + 48);
	//		bmp_name[2] = (char)(i / 10 % 10 + 48);
	//		bmp_name[3] = (char)(i % 10 + 48);
	//		bmp_name[4] = '.';bmp_name[5] = 'b';bmp_name[6] = 'm';bmp_name[7] = 'p';
	//	}
	//	else if (i < 100000) {
	//		bmp_name[0] = (char)(i / 10000 + 48);
	//		bmp_name[1] = (char)(i / 1000 % 10 + 48);
	//		bmp_name[2] = (char)(i / 100 % 10 + 48);
	//		bmp_name[3] = (char)(i / 10 % 10 + 48);
	//		bmp_name[4] = (char)(i % 10 + 48);
	//		bmp_name[5] = '.';bmp_name[6] = 'b';bmp_name[7] = 'm';bmp_name[8] = 'p';
	//	}
	//	sprintf(bmp_data, "%s%s", simaple_file, bmp_name);
	//	bmp_r_tobuf(bmp_data, train_buf, train_size);
	//	mat_tovector(train_buf, tr->train_mat->mat[0]);
	//	f32mat_up_down_change(tr->train_mat->mat[0]);
	//	tr->target_load = tr->target_set->mat[i];
	//	back_propaga(tr);
	//	printf("训练编号 = %d\n", i);
	return true;
}

//优化次数:1
//测试泛化
//simaple_file:输入样本文件地址
//i:样本编号
//tr:训练类
int train_test(const char *simaple_file,const uint32_t i,MlpStr *train)
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
	//	mat_tovector(train_buf, tr->train_mat);
	//	f32mat_up_down_change(tr->train_mat);
	//	tr->target_load = tr->target_set[i];
	//	forward_propaga(tr);
	return true;
}

//优化次数:0
//各个连接层微分算子
//tr:训练模型类
//rreturn:int标志位
int mlp_der(MlpStr *train) 
{
	//uint16_t i = NULL, mlps = NULL,mlp_l=NULL,mlp_r=NULL;
	//uint16_t j = NULL, k = NULL, mlps_temp0 = NULL, mlps_temp1 = NULL;
	//uint32_t line_offset = NULL;
	//float *der_mataddr = NULL, *r_mlpaddr = NULL,*mlp_waddr=NULL;
	//float temp_sum = NULL;
	//mlps = (uint16_t)tr->mlp_message[0];
	////最后输出层微分算子
	//auto_load_active_fd(mlps, tr);
	//tr->active_fid(tr->outmat[mlps], tr->der_mat[mlps], tr->target_load);
	////除最后一层还需微分的层数
	//for (i=1; i <= mlps;++i) {
	//	//确定微分层的元素个数及数据地址赋值
	//	mlp_l = mlps - i;
	//	mlps_temp0 = tr->outmat[mlp_l]->line;
	//	//对各个输出层求导
	//	auto_load_active_fd(mlp_l, tr);
	//	tr->active_fid(tr->outmat[mlp_l],tr->der_mat[mlp_l],NULL);
	//	der_mataddr = (float*)tr->der_mat[mlp_l]->SaveAddr;
	//	//确定微分算子层元素个数及地址赋值
	//	mlp_r = mlps - i + 1;
	//	mlps_temp1 = tr->outmat[mlp_r]->line;
	//	r_mlpaddr = (float*)tr->der_mat[mlp_r]->SaveAddr;
	//	mlp_waddr = (float*)tr->layer[mlp_r]->SaveAddr;
	//	//微分层元素更新个数
	//	for (j=0; j < mlps_temp0; ++j) {
	//		//影响层使能元素个数
	//		for (k = 0; k < mlps_temp1; ++k) {
	//			temp_sum += r_mlpaddr[k] * mlp_waddr[line_offset + j];
	//			line_offset += tr->layer[mlp_r]->row;
	//		}
	//		der_mataddr[j] *= temp_sum;
	//		temp_sum = NULL;
	//		line_offset = NULL;
	//	}
	//}
	return true;
}

//优化次数:0
//更新全部连接层权重
//tr:训练模型类
int update_all_layer(MlpStr *train)
{
	//uint8_t mlps = NULL,i=NULL;
	//mlps = (uint8_t)tr->mlp_message[0];
	//update_layer(tr->layer[0],tr->der_mat[0],tr->train_mat,tr);
	//for (i = 1; i <= mlps;++i) {
	//	update_layer(tr->layer[i],tr->der_mat[i],tr->outmat[i-1],tr);
	//}
	return true;
}

//优化次数:0
//更新连接层权重
//update_mat:更新权重对象
//der_mat:更新权重对象对应的微分层
//o_mat:更新权重对象对应的影响层
//tr:训练模型类
int update_layer(MatStr *update_mat,const MatStr *der_mat,const MatStr *o_mat,MlpStr *train)
{
	//uint16_t i = NULL,j=NULL;
	//uint32_t line_offset = NULL;
	//float *update_mataddr = NULL, *der_mataddr = NULL, *o_mataddr = NULL;
	//update_mataddr = (float*)update_mat->SaveAddr;
	//der_mataddr = (float*)der_mat->SaveAddr;
	//o_mataddr = (float*)o_mat->SaveAddr;
	//for (i = 0; i < der_mat->line;++i) {
	//	for (j = 0; j < update_mat->row;++j) {
	//		update_mataddr[line_offset + j] -= tr->op[0] * der_mataddr[i] * o_mataddr[j];
	//	}
	//	line_offset += update_mat->row;
	//}
	return true;
}

//优化次数:0
//自动装载求导函数
//i:输出层对应层数
//tr:全链接网络类
int auto_load_active_fd(uint16_t i,MlpStr *train)
{
	//if ((void*)tr->active_fi[i] == (void*)mat_signmoid_par)
	//	tr->active_fid = signmoid_fd;
	//else if ((void*)tr->active_fi[i] == (void*)mat_tanh_par)
	//	tr->active_fid = tanh_fd;
	//else if ((void*)tr->active_fi[i] == (void*)mat_relu_par)
	//	tr->active_fid = relu_fd;
	//else if ((void*)tr->active_fi[i] == (void*)mat_softmax_par)
	//	tr->active_fid = softmax_fd;
	//else
	//	return false;
	return true;
}

//优化次数:0
//re_message:训练类信息
//statr_graph:训练图初始节点
//end_graph:训练图结尾节点
//target_set:标签集
//神经网络类构造函数(输入形参)
network_l::network_l(float *tr_message, struct GraphStr *start_graph, TensorStr *target_set, TensorStr *in_train)
{
	GraphStr *p=NULL;
	//训练模型信息初始化
	tr.tr_message = tr_message;
	//训练图初始节点初始化
	tr.strat_graph = start_graph;
	//训练图结尾节点初始化
	p = tr.strat_graph;
	while (p->right_add) {
		p = p->right_add;
	}
	tr.end_graph = p;
	//训练标签集合初始化
	tr.target_set = target_set;
	//初始化损失函数
	switch ((uint16_t)tr.tr_message[0]) {
	case (uint16_t)sqaure_loss:
		//平方差损失函数
		tr.loss_fi = mat_square_loss;
		break;
	case (uint16_t)cross_entropy:
		//交叉熵损失函数
		tr.loss_fi = mat_cross_entropy;
		break;
	default:tr.loss_fi=NULL;
		break;
	}
	tr.in_train = in_train;
}

//优化次数:0
//神经网络默认构造函数
network_l::network_l()
{
	//训练模型信息初始化
	tr.tr_message = NULL;
	//训练图初始节点初始化
	tr.strat_graph = NULL;
	//训练图结尾节点初始化
	tr.end_graph = NULL;
	//训练标签集合初始化
	tr.target_set = NULL;
	//初始化损失函数
	tr.loss_fi = NULL;
}

//优化次数:0
//network_l类析构函数
network_l::~network_l()
{

}

//优化:0
//打印network_l类
//content0:内容0
//content1:内容1
int network_l::output(uint16_t content_0, uint8_t content_1)
{
	uint16_t i = NULL;
	GraphStr *graph_p = NULL;
	//打印信息
	if (content_0&_tr_mes) {
		cout << "tr_message :" << endl;
		switch ((uint16_t)tr.tr_message[0]) {
		case (uint16_t)sqaure_loss:
			cout << "loss_flag = sqaure_loss" << endl;
			break;
		case (uint16_t)cross_entropy:
			cout << "loss_flag = cross_entropy" << endl;
			break;
		default:
			cout << "error !" << endl;
			return false;
			break;
		}
		cout << "max_update = " << tr.tr_message[1] << endl;
		cout << "batch_size = " << tr.tr_message[2] << endl;
		cout << "error_scope = " << tr.tr_message[3] << endl;
		cout << "learmspeed = " << tr.tr_message[4] << endl << endl;
	}
	//打印开始图
	if (content_0&_tr_strat_graph) {
		cout << "tr_strat_graph :" << endl << "addr = " << tr.strat_graph << endl << "graph_type = ";
		graph_output(tr.strat_graph, content_1);
		cout << endl;
	}
	//打印结尾图
	if (content_0&_tr_end_graph) {
		cout << "tr_end_graph :" << endl << "addr = " << tr.end_graph << endl << "graph_type = ";
		graph_output(tr.end_graph, content_1);
		cout << endl;
	}
	//打印全部图
	if (content_0&_tr_all_graph) {
		graph_p = tr.strat_graph;
		while (graph_p) {
			cout << "graph " << "[" << i << "]" << " : " << endl << "addr = " << graph_p << endl << "graph_type = ";
			graph_output(graph_p, content_1);
			cout << endl;
			i++;
			graph_p = graph_next(graph_p, _direct_left);
		}
		cout << endl;
	}
	//打印标签集信息
	if (content_0&_tr_target_mes) {
		cout << "target_set_mes : ";
		tensor_message(tr.target_set);
	}
	//打印标签集数据
	if (content_0&_tr_target_data) {
		cout << "target_set_data : " << endl;
		tensor_output(tr.target_set);
	}
	//打印训练输入数据信息
	if (content_0&_tr_train_mes) {
		cout << "tr_train_mes : " << endl;
		tensor_message(tr.in_train);
	}
	//打印训练输入数据
	if (content_0&_tr_train_data) {
		cout << "tr_train_data : " << endl;
		tensor_output(tr.in_train);
	}
	return true;
}

//优化次数:0
//单步前向传播
int network_l::forward_propaga_step(struct GraphStr *graph,uint8_t direct)
{
	//装载作为当前节点输入的张量
	graph_forward_switch(get_graph_tensor( graph, direct), graph, direct);
	return true;
}

//神经网络前向传播
int network_l::forward_propaga(void)
{
	float error_total = NULL;
	GraphStr *graph_p = tr.strat_graph;
	//第一步前向传播
	graph_forward_switch(tr.in_train, graph_p, _direct_left);
	//中间层前向传播
	graph_p = tr.strat_graph->right_add;
	while (graph_p){
		//前向传播一次
		forward_propaga_step(graph_p, _direct_left);
		graph_p = graph_p->right_add;
	}
	return true;
}

//求输出总误差
//label:标签
float network_l::total_error(uint16_t label)
{
	return tr.loss_fi(get_graph_tensor(tr.end_graph, _direct_now)->mat[0],tr.target_set->mat[label]);
}

//神经网络反向传播
//label:标签
int network_l::back_propaga(uint16_t label)
{
	MlpStr *mlp_0=NULL;
	GraphStr *graph_p = tr.end_graph;
	//判断误差是否符合要求
	if (total_error(label) < tr.tr_message[3]) {
		cout << "模型效果良好" << endl;
		return false;
	}
	else {
		mlp_0 = (MlpStr*)graph_p->graph_data;
		//求最后一层微分(最后一层只允许为mlp层)
		mlp_0->active_fid(mlp_0->outmat->mat[0], mlp_0->outmat->mat[0],tr.target_set->mat[label]);
		//求各个层梯度(除了开始层)
		while (graph_p!=tr.strat_graph) {
			//当前图反向传播
			graph_back_switch(graph_p->left_add, graph_p);
			//向前移一个图
			graph_p = graph_p->left_add;
		}
		//开始层反向传播(此处使用了函数重载)
		graph_back_switch(tr.in_train, graph_p);
	}
	return true;
}

//更新神经网络
int network_l::update(void)
{
	GraphStr *graph_p = tr.end_graph;
	//更新神经网络
	while (graph_p) {
		graph_update(graph_p, tr.tr_message[4]);
		graph_p = graph_p->left_add;
	}
	return true;
}


















