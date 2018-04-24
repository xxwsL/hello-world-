#include "graph.h"

//优化次数:0
//graph:当前图
//direct:方向
//load_tensor:装载张量
//return:bool标志
//提取上一层节点的张量
TensorStr* get_graph_tensor(struct GraphStr *graph, uint8_t direct)
{
	GraphStr *temp_add = NULL;
	switch (direct) {
	case _direct_left:
		//读取方向左的图的地址
		temp_add = graph->left_add;
		break;
	case _direct_up:
		//读取方向上的图的地址
		temp_add = graph->up_add;
		break;
	case _direct_right:
		//读取方向右的图的地址
		temp_add = graph->right_add;
		break;
	case _direct_down:
		//读取方向下的图的地址
		temp_add = graph->down_add;
		break;
	default:
		if (direct&_direct_now) {
			temp_add = graph;
		}
		else { 
			return false;
		}
		break;
	}
	switch (temp_add->graph_type) {
		//dnn节点
	case _mlp:
		return ((mlpstr*)temp_add->graph_data)->outmat;
		break;
		//cnn节点
	case _cnn:
		//tensor_add = ((cnn*)temp_add->graph_data);
		return false;
		break;
		//tensor_c节点
	case _tensorarch:
		//方向左或者上,提取tensor_c的r_tensor
		if ((direct&_direct_left) || (direct&_direct_up)) {
			return ((TensorArch*)temp_add->graph_data)->r_d_tensor;
		}
		//方向右或者下,提取tensor_c的l_tensor
		else if (direct == _direct_right || direct == _direct_down) {
			return ((TensorArch*)temp_add->graph_data)->l_u_tensor;
		}
		break;
	default:return false; break;
	}
	return false;
}

//优化次数:0
//op:mlp偏置算子
//fi:激活函数
//line:行长
//row:列长
//return:GraphStr指针
//创建mlp图
GraphStr *graph_mlp_create(float op, active_fi_str(fi), uint16_t line, uint16_t row)
{
	GraphStr *re_graph = NULL;
	re_graph = (GraphStr*)malloc(sizeof(GraphStr));
	re_graph->graph_type = _mlp;
	re_graph->graph_data = mlp_create(op, fi, line, row);
	re_graph->left_add = NULL;
	re_graph->up_add = NULL;
	re_graph->right_add = NULL;
	re_graph->down_add = NULL;
	return re_graph;
}

//优化次数:0
//l_u_line:左张量行长
//l_u_row:左张量列长
//l_u_height:左张量高
//r_d_lin:右张量行长
//r_d_row:右张量列长
//r_d_height:右张量高
//return:GraphStr指针
//创建tensorarch图
GraphStr *graph_tensorarch_create(uint16_t l_u_line, uint16_t l_u_row, uint16_t l_u_height, uint16_t r_d_line, uint16_t r_d_row, uint16_t r_d_height)
{
	GraphStr *re_graph = NULL;
	re_graph = (GraphStr*)malloc(sizeof(GraphStr));
	re_graph->graph_type = _tensorarch;
	re_graph->graph_data = tensorarch_create(l_u_line, l_u_row, l_u_height, r_d_line, r_d_row, r_d_height);
	re_graph->left_add = NULL;
	re_graph->up_add = NULL;
	re_graph->right_add = NULL;
	re_graph->down_add = NULL;
	return re_graph;
}

//优化:0
//graph_add:图地址
//content:内容
//打印图
bool graph_output(void *graph_add, uint8_t content) 
{
	GraphStr *graph = (GraphStr*)graph_add;
	switch(graph->graph_type){
	case _mlp:
		cout << "mlp_graph : " << endl;
		mlp_output((MlpStr*)graph->graph_data,content);
		break;
	case _tensorarch:
		cout << "tensorarchraph : " << endl;
		tensorarch_output(graph->graph_data,content);
		break;
	default:return false; break;
	}
	return true;
}

//优化次数:0
//张量转移图运算
//load_tensor:装载张量
//in_tensor:输入张量
//direct:数据流方向方向
//tensorarch图运算
bool graph_tensorarch_op(GraphStr *tensorarch_add, const uint8_t direct)
{
	if (tensorarch_op(tensorarch_add->graph_data, get_graph_tensor(tensorarch_add,direct), direct))
		return true;
	else
		return false;
}

//优化:0
//graph_buf:graph的buf
//chain:链长
//图链初始化
GraphStr *graph_chain_init(GraphStr **graph_buf,uint16_t chain_len)
{
	uint16_t i = NULL;
	graph_buf[0]->right_add = graph_buf[1];
	if (chain_len == 1) {
		return graph_buf[0];
	}
	else {
		for (i = 1; i < chain_len; ++i) {
			graph_buf[i - 1]->right_add = graph_buf[i];
			graph_buf[i]->left_add = graph_buf[i - 1];
		}
	}
	return graph_buf[0];
}

//优化:0
//in_graph:当前图
//direct:数据流方向
//获得当前图相邻的图
GraphStr *graph_next(GraphStr *in_grpah, uint8_t direct)
{
	switch (direct) {
	case _direct_left:
		if (in_grpah->right_add) return in_grpah->right_add;
		break;
	case _direct_up:
		if (in_grpah->right_add) return in_grpah->down_add;
		break;
	case _direct_right:
		if (in_grpah->right_add) return in_grpah->left_add;
		break;
	case _direct_down:
		if (in_grpah->right_add) return in_grpah->up_add;
		break;
	default:return false; break;
	}
	return false;
}



//优化次数:0
//graph:输入图
//tensor:输入张量
//前向传播图操作选择
bool graph_forward_switch(TensorStr *tensor, struct GraphStr *graph, uint8_t direct, uint16_t nums)
{
	switch (graph->graph_type) {
		//dnn节点
	case _mlp:
		mlp_one_op((MlpStr*)graph->graph_data, tensor, nums);
		break;
		//cnn节点
	case _cnn:
		break;
		//tensor_arch节点
	case _tensorarch:
		tensorarch_op((TensorArch*)graph->graph_data, tensor, direct);
		break;
	default:return false; break;
	}
	return true;
}

//l_graph:左图
//now_graph:当前图
//反向传播图操作选择
bool graph_back_switch(struct GraphStr *l_graph, struct GraphStr *now_graph)
{
	switch (now_graph->graph_type){
	//now_graph为dnn
	case _mlp:
		switch (l_graph->graph_type) {
		//当前图的左图为dnn
		case _mlp:
			mlp_gr(((MlpStr*)l_graph->graph_data)->outmat, (MlpStr*)now_graph->graph_data);
			mlp_error_pass((MlpStr*)now_graph->left_add->graph_data, (MlpStr*)now_graph->graph_data);
			break;
		//当前图的左图为tensorarch
		case _tensorarch:

			break;
		default:
			return false;
			break;
		}
		break;
	//now_graph为cnn
	case _cnn:
		return false;//未实现
		break;
	//now_graph为tensorarch
	case _tensorarch:
		break;
	default:
		return false; 
		break;
	}
	return true;
}

//tensor:输入张量
//now_graph:当前图
//针对开始节点的反向传播图操作选择的函数重载
bool graph_back_switch(struct TensorStr *tensor, struct GraphStr *now_graph, uint16_t nums)
{
	switch (now_graph->graph_type) {
		//now_graph为dnn
	case _mlp:
		mlp_gr(tensor, (MlpStr*)now_graph->graph_data);
		break;
		//now_graph为cnn
	case _cnn:
		return false;//未实现
		break;
	default:
		return false;
		break;
	}
	return true;
}

//graph:输入图
//learmspeed:学习速率
//图更新
bool graph_update(GraphStr *graph, float learmspeed)
{
	switch (graph->graph_type){
	case _mlp:
		mlp_update((MlpStr*)graph->graph_data, learmspeed);
		break;
	case _tensorarch:
		return true;
		break;
	case _cnn:
		return false;
		break;
	default:
		return false;
		break;
	}
	return true;
}

