#include "network.h"

//优化次数:0
//re_message:训练类信息
//statr_graph:训练图初始节点
//end_graph:训练图结尾节点
//target_set:标签集
//神经网络类构造函数(输入形参)
network_l::network_l(float *tr_message, struct GraphStr *start_graph, TensorStr *target_set, TensorStr *in_tensor)
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
	case (uint16_t)_sqaure_loss:
		//平方差损失函数
		tr.loss_fi = mat_square_loss;
		break;
	case (uint16_t)_cross_entropy:
		//交叉熵损失函数
		tr.loss_fi = mat_cross_entropy;
		break;
	default:tr.loss_fi=NULL;
		break;
	}
	//装载训练输入数据
	tr.in_train = in_tensor;
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
bool network_l::output(uint16_t content_0, uint8_t content_1)
{
	char key = NULL;
	int16_t i = NULL;
	GraphStr *graph_p = NULL;
	//打印信息
	if (content_0&_tr_mes) {
		cout << "tr_message :" << endl;
		switch ((uint16_t)tr.tr_message[0]) {
		case (uint16_t)_sqaure_loss:
			cout << "loss_flag = sqaure_loss" << endl;
			break;
		case (uint16_t)_cross_entropy:
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
		cout << "now is start_graph\n";
		while (true) {
			loop_0:cout << "input  'n'  to  now_graph\n"<<"input  'l'  to  left_graph\n"<< "input  'r'  to  right_graph\n"<< "input  'q'  to  exit\n";
			cin >> key;
			cout << "\n";
			switch (key) {
			case 'n':
				break;
			case 'l':
				if(graph_p->left_add){
					graph_p = graph_p->left_add;
					i--;
				}
				else{
					cout << "left_graph is empty\n\n";
					goto loop_0;
				}
				break;
			case 'r':
				if (graph_p->right_add) {
					graph_p = graph_p->right_add;
					i++;
				}
				else {
					cout << "right_graph is empty\n\n";
					goto loop_0;
				}
				break;
			case 'q':
				cout << "output exit\n";
				return true;
				break;
			default:
				cout << "input invalid\n\n";
				goto loop_0;
				break;
			}
			cout << "graph " << "[" << i << "]" << " : " << endl << "addr = " << graph_p << endl << "graph_type = ";
			graph_output(graph_p, content_1);
		}
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
bool network_l::forward_propaga_step(struct GraphStr *graph,uint8_t direct)
{
	//装载作为当前节点输入的张量
	graph_forward_switch(get_graph_tensor( graph, direct), graph, direct);
	return true;
}

//nums:批数据当前进度
//神经网络前向传播
bool network_l::forward_propaga(void)
{
	float error_total = NULL;
	GraphStr *graph_p = tr.strat_graph;
	//第一步前向传播
	graph_forward_switch(tr.in_train, graph_p, _direct_left);
	//搜索下一张图
	graph_p = tr.strat_graph->right_add;
	while (graph_p){
		//前向传播一次
		graph_forward_switch(get_graph_tensor(graph_p, _direct_left), graph_p, _direct_left);
		graph_p = graph_p->right_add;
	}
	return true;
}

//求输出总误差
//label:标签
float network_l::total_error(void)
{
	return tr.loss_fi(get_graph_tensor(tr.end_graph, _direct_now)->mat[0],tr.target_set->mat[tr.label]);
}

//神经网络反向传播
//label:标签
bool network_l::back_propaga(void)
{
	MlpStr *mlp_0=NULL;
	GraphStr *graph_p = tr.end_graph;
	//判断误差是否符合要求
	if (total_error() < tr.tr_message[3]) {
		cout << "模型效果良好\n";
		cout << "_______________________________________________________________________________\n";
		return false;
	}
	else {
		mlp_0 = (MlpStr*)graph_p->graph_data;
		//求最后一层微分(最后一层只允许为mlp层)
		mlp_0->active_fid(mlp_0->outmat->mat[0], mlp_0->outmat->mat[0],tr.target_set->mat[tr.label]);
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
bool network_l::update(void)
{
	GraphStr *graph_p = tr.end_graph;
	//更新神经网络
	while (graph_p) {
		graph_update(graph_p, tr.tr_message[4]);
		graph_p = graph_p->left_add;
	}
	return true;
}

//喂数据
bool network_l::feed_data(const char *simaple_file, const uint32_t name, uint16_t label)
{
	read_bmp_to_buf(simaple_file, name, tr.in_train->mat[0]);
	tr.label = label;
	return true;
}

bool network_l::feed_data(struct TensorStr *tensor, const uint16_t label) {
		tr.in_train = tensor;
		tr.label = label;
	return true;
}

bool network_l::feed_data(void)
{
	return true;
}


//训练
int network_l::train(void)
{
	uint16_t i = NULL;
	//前向传播+反向传播
	forward_propaga();
	cout << "输出总误差 = " << test() << "\n";
	output(_tr_end_graph, _mlp_outmat);
	back_propaga();
	//更新神经网络
	update();
	return true;
}

//测试
float network_l::test(void)
{
	//前向传播
	forward_propaga();
	//计算输出总误差
	return total_error();
}
















