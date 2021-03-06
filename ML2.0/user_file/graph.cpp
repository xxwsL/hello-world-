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
		//cnn_conv节点
	case _cnn_conv:
		return ((cnn_conv*)temp_add->graph_data)->out;
		break;
		//cnn_pooling节点
	case _cnn_pool:
		return ((cnn_pool*)temp_add->graph_data)->out;
		break;
		//tensor_c节点
	case _arch:
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
GraphStr *graph_mlp_create(uint16_t line, uint16_t row, float op, active_fi_str(fi))
{
	GraphStr *re_graph = new GraphStr;
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
GraphStr *graph_tensorarch_create(array<uint16_t, 4>l_u_buf, array<uint16_t, 4>r_d_buf)
{
	GraphStr *re_graph = new GraphStr;
	re_graph->graph_type = _arch;
	re_graph->graph_data = tensorarch_create(l_u_buf, r_d_buf);
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
bool graph_output(const GraphStr *graph, uint8_t content) 
{
	switch(graph->graph_type){
		//mlp图
	case _mlp:
		cout << "mlp_graph : " << endl;
		mlp_output((MlpStr*)graph->graph_data,content);
		break;
		//cnn_conv图
	case _cnn_conv:
		cout << "cnn_conv_graph :\n";
		((cnn_conv*)graph->graph_data)->output(content);
		break;
		//cnn_pooling图
	case _cnn_pool:
		cout << "cnn_pooling_graph :\n";
		((cnn_pool*)graph->graph_data)->output(content);
		break;
		//tensorarch图
	case _arch:
		cout << "tensorarchraph : " << endl;
		tensorarch_output((TensorArch*)graph->graph_data);
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
	if (tensorarch_op((TensorArch*)tensorarch_add->graph_data, get_graph_tensor(tensorarch_add,direct), direct))
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
bool graph_forward_switch(struct TensorStr *tensor, struct GraphStr *graph, const uint8_t direct)
{
	switch (graph->graph_type) {
		//dnn节点
	case _mlp:
		mlp_one_op((MlpStr*)graph->graph_data, tensor);
		break;
		//cnn节点
	case _cnn_conv:
		((cnn_conv*)graph->graph_data)->conv_ot(tensor);
		break;
		//池化层
	case _cnn_pool:
		((cnn_pool*)graph->graph_data)->pooling_ot(tensor);
		//tensor_arch节点
		break;
	case _arch:
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
			mlp_gr(_graph_get_mlp(l_graph)->outmat, _graph_get_mlp(now_graph));
			mlp_error_pass(_graph_get_mlp(l_graph), _graph_get_mlp(now_graph));
			break;
		//当前图的左图为tensorarch
		case _arch:
			mlp_gr(_graph_get_arch(l_graph)->r_d_tensor, _graph_get_mlp(now_graph));
			mlp_error_pass(_graph_get_arch(l_graph)->r_d_tensor, _graph_get_mlp(now_graph));
			tensorarch_op(_graph_get_arch(l_graph), _graph_get_arch(l_graph)->r_d_tensor,_direct_right);
			break;
		default:return false;break;
		}
		break;
	//now_graph为cnn_conv
	case _cnn_conv:
		switch (l_graph->graph_type) {
		//当前左图为conv图
		case _cnn_conv:
			_graph_get_conv(now_graph)->conv_gr(_graph_get_conv(l_graph)->out);
			_graph_get_conv(l_graph)->conv_fd();
			_graph_get_conv(now_graph)->error_pass_conv(_graph_get_conv(l_graph)->out);
			break;
		//当前左图为pool图
		case _cnn_pool:
			_graph_get_conv(now_graph)->conv_gr(_graph_get_pool(l_graph)->out);
			_graph_get_conv(now_graph)->error_pass_pool(_graph_get_pool(l_graph)->out);
			break;
		default:return false; break;
		}
		return false;break;
	//now_graph为cnn_pooling
	case _cnn_pool:
		switch (l_graph->graph_type) {
		//当前图左图为cnn_conv
		case _cnn_conv:
			_graph_get_conv(l_graph)->conv_fd();
			_graph_get_pool(now_graph)->error_pass(_graph_get_conv(l_graph)->out);
			break;
		default:return false;break;
		}
		break;
	//now_graph为tensorarch
	case _arch:
		switch (l_graph->graph_type) {
		//当前左图为conv图
		case _cnn_conv:
			_graph_get_conv(l_graph)->conv_fd();
			tensor_dotmult(_graph_get_conv(l_graph)->out, _graph_get_arch(now_graph)->l_u_tensor, _graph_get_conv(l_graph)->out);
			break;
		//当前左图为pool图
		case _cnn_pool:
			tensor_copy(_graph_get_arch(now_graph)->l_u_tensor, _graph_get_pool(l_graph)->out);
			break;
		default:return false; break;
		}
		break;
	default:return false; break;
	}
	return true;
}

//tensor:输入张量
//now_graph:当前图
//针对开始节点的反向传播图操作选择的函数重载
bool graph_back_switch(struct TensorStr *tensor, struct GraphStr *now_graph)
{
	switch (now_graph->graph_type) {
	//now_graph为dnn
	case _mlp:
		mlp_gr(tensor, (MlpStr*)now_graph->graph_data);
		break;
	//now_graph为cnn
	case _cnn_conv:
		_graph_get_conv(now_graph)->conv_gr(tensor);
		break;
	default:return false;break;
	}
	return true;
}

//graph:输入图
//learmspeed:学习速率
//图更新
bool graph_update(GraphStr *graph, const float learmspeed)
{
	switch (graph->graph_type){
	case _mlp:
		mlp_update((MlpStr*)graph->graph_data, learmspeed);
		break;
	case _cnn_conv:
		_graph_get_conv(graph)->update(learmspeed);
		return false;
		break;
	default:return false;break;
	}
	return true;
}

//kernel_buf:(0)line (1)row (2)height (3)deep
//out_buf:(0)line (1)row (2)height (3)deep
//stride_buf:(0)line (1)row (2)height (3)deep
//op_value:偏置值
//active_fi_str:激活函数
//创建cnn_conv核
GraphStr *graph_cnn_conv_create(const array<uint16_t, 4>kernel_buf,const array<uint16_t, 4>out_buf,const array<uint8_t, 4>stride_buf,const float op_value, active_fi_str(fi))
{
	//创建一个图
	GraphStr *graph = new GraphStr();
	//创建一个cnn_conv
	cnn_conv *cnn_conv_ = new cnn_conv(kernel_buf, out_buf, stride_buf, op_value, fi);
	//把cnn_conv装载到图
	graph->graph_data = cnn_conv_;
	graph->graph_type = _cnn_conv;
	return graph;
}

//line_v:行长
//row_v:列长
//out_v:输出张量尺寸信息
//type:池化操作类型
//创建卷积层池化图
GraphStr *graph_cnn_pool_create(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type)
{
	GraphStr *graph = new GraphStr();
	cnn_pool *pooling = new cnn_pool(line_v, row_v, out_v, type);
	graph->graph_data = pooling;
	graph->graph_type = _cnn_pool;
	return graph;
}

