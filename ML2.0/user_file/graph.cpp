#include "graph.h"

//�Ż�����:0
//graph:��ǰͼ
//direct:����
//load_tensor:װ������
//return:bool��־
//��ȡ��һ��ڵ������
TensorStr* get_graph_tensor(struct GraphStr *graph, uint8_t direct)
{
	GraphStr *temp_add = NULL;
	switch (direct) {
	case _direct_left:
		//��ȡ�������ͼ�ĵ�ַ
		temp_add = graph->left_add;
		break;
	case _direct_up:
		//��ȡ�����ϵ�ͼ�ĵ�ַ
		temp_add = graph->up_add;
		break;
	case _direct_right:
		//��ȡ�����ҵ�ͼ�ĵ�ַ
		temp_add = graph->right_add;
		break;
	case _direct_down:
		//��ȡ�����µ�ͼ�ĵ�ַ
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
		//dnn�ڵ�
	case _mlp:
		return ((mlpstr*)temp_add->graph_data)->outmat;
		break;
		//cnn_conv�ڵ�
	case _cnn_conv:
		return ((cnn_conv*)temp_add->graph_data)->out;
		break;
		//cnn_pooling�ڵ�
	case _cnn_pool:
		return ((cnn_pool*)temp_add->graph_data)->out;
		break;
		//tensor_c�ڵ�
	case _arch:
		//�����������,��ȡtensor_c��r_tensor
		if ((direct&_direct_left) || (direct&_direct_up)) {
			return ((TensorArch*)temp_add->graph_data)->r_d_tensor;
		}
		//�����һ�����,��ȡtensor_c��l_tensor
		else if (direct == _direct_right || direct == _direct_down) {
			return ((TensorArch*)temp_add->graph_data)->l_u_tensor;
		}
		break;
	default:return false; break;
	}
	return false;
}

//�Ż�����:0
//op:mlpƫ������
//fi:�����
//line:�г�
//row:�г�
//return:GraphStrָ��
//����mlpͼ
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

//�Ż�����:0
//l_u_line:�������г�
//l_u_row:�������г�
//l_u_height:��������
//r_d_lin:�������г�
//r_d_row:�������г�
//r_d_height:��������
//return:GraphStrָ��
//����tensorarchͼ
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

//�Ż�:0
//graph_add:ͼ��ַ
//content:����
//��ӡͼ
bool graph_output(const GraphStr *graph, uint8_t content) 
{
	switch(graph->graph_type){
		//mlpͼ
	case _mlp:
		cout << "mlp_graph : " << endl;
		mlp_output((MlpStr*)graph->graph_data,content);
		break;
		//cnn_convͼ
	case _cnn_conv:
		cout << "cnn_conv_graph :\n";
		((cnn_conv*)graph->graph_data)->output(content);
		break;
		//cnn_poolingͼ
	case _cnn_pool:
		cout << "cnn_pooling_graph :\n";
		((cnn_pool*)graph->graph_data)->output(content);
		break;
		//tensorarchͼ
	case _arch:
		cout << "tensorarchraph : " << endl;
		tensorarch_output((TensorArch*)graph->graph_data);
		break;
	default:return false; break;
	}
	return true;
}

//�Ż�����:0
//����ת��ͼ����
//load_tensor:װ������
//in_tensor:��������
//direct:������������
//tensorarchͼ����
bool graph_tensorarch_op(GraphStr *tensorarch_add, const uint8_t direct)
{
	if (tensorarch_op((TensorArch*)tensorarch_add->graph_data, get_graph_tensor(tensorarch_add,direct), direct))
		return true;
	else
		return false;
}

//�Ż�:0
//graph_buf:graph��buf
//chain:����
//ͼ����ʼ��
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

//�Ż�:0
//in_graph:��ǰͼ
//direct:����������
//��õ�ǰͼ���ڵ�ͼ
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

//�Ż�����:0
//graph:����ͼ
//tensor:��������
//ǰ�򴫲�ͼ����ѡ��
bool graph_forward_switch(struct TensorStr *tensor, struct GraphStr *graph, const uint8_t direct)
{
	switch (graph->graph_type) {
		//dnn�ڵ�
	case _mlp:
		mlp_one_op((MlpStr*)graph->graph_data, tensor);
		break;
		//cnn�ڵ�
	case _cnn_conv:
		((cnn_conv*)graph->graph_data)->conv_ot(tensor);
		break;
		//�ػ���
	case _cnn_pool:
		((cnn_pool*)graph->graph_data)->pooling_ot(tensor);
		//tensor_arch�ڵ�
		break;
	case _arch:
		tensorarch_op((TensorArch*)graph->graph_data, tensor, direct);
		break;
	default:return false; break;
	}
	return true;
}

//l_graph:��ͼ
//now_graph:��ǰͼ
//���򴫲�ͼ����ѡ��
bool graph_back_switch(struct GraphStr *l_graph, struct GraphStr *now_graph)
{
	switch (now_graph->graph_type){
	//now_graphΪdnn
	case _mlp:
		switch (l_graph->graph_type) {
		//��ǰͼ����ͼΪdnn
		case _mlp:
			mlp_gr(_graph_get_mlp(l_graph)->outmat, _graph_get_mlp(now_graph));
			mlp_error_pass(_graph_get_mlp(l_graph), _graph_get_mlp(now_graph));
			break;
		//��ǰͼ����ͼΪtensorarch
		case _arch:
			mlp_gr(_graph_get_arch(l_graph)->r_d_tensor, _graph_get_mlp(now_graph));
			mlp_error_pass(_graph_get_arch(l_graph)->r_d_tensor, _graph_get_mlp(now_graph));
			tensorarch_op(_graph_get_arch(l_graph), _graph_get_arch(l_graph)->r_d_tensor,_direct_right);
			break;
		default:return false;break;
		}
		break;
	//now_graphΪcnn_conv
	case _cnn_conv:
		switch (l_graph->graph_type) {
		//��ǰ��ͼΪconvͼ
		case _cnn_conv:
			_graph_get_conv(now_graph)->conv_gr(_graph_get_conv(l_graph)->out);
			_graph_get_conv(l_graph)->conv_fd();
			_graph_get_conv(now_graph)->error_pass_conv(_graph_get_conv(l_graph)->out);
			break;
		//��ǰ��ͼΪpoolͼ
		case _cnn_pool:
			_graph_get_conv(now_graph)->conv_gr(_graph_get_pool(l_graph)->out);
			_graph_get_conv(now_graph)->error_pass_pool(_graph_get_pool(l_graph)->out);
			break;
		default:return false; break;
		}
		return false;break;
	//now_graphΪcnn_pooling
	case _cnn_pool:
		switch (l_graph->graph_type) {
		//��ǰͼ��ͼΪcnn_conv
		case _cnn_conv:
			_graph_get_conv(l_graph)->conv_fd();
			_graph_get_pool(now_graph)->error_pass(_graph_get_conv(l_graph)->out);
			break;
		default:return false;break;
		}
		break;
	//now_graphΪtensorarch
	case _arch:
		switch (l_graph->graph_type) {
		//��ǰ��ͼΪconvͼ
		case _cnn_conv:
			_graph_get_conv(l_graph)->conv_fd();
			tensor_dotmult(_graph_get_conv(l_graph)->out, _graph_get_arch(now_graph)->l_u_tensor, _graph_get_conv(l_graph)->out);
			break;
		//��ǰ��ͼΪpoolͼ
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

//tensor:��������
//now_graph:��ǰͼ
//��Կ�ʼ�ڵ�ķ��򴫲�ͼ����ѡ��ĺ�������
bool graph_back_switch(struct TensorStr *tensor, struct GraphStr *now_graph)
{
	switch (now_graph->graph_type) {
	//now_graphΪdnn
	case _mlp:
		mlp_gr(tensor, (MlpStr*)now_graph->graph_data);
		break;
	//now_graphΪcnn
	case _cnn_conv:
		_graph_get_conv(now_graph)->conv_gr(tensor);
		break;
	default:return false;break;
	}
	return true;
}

//graph:����ͼ
//learmspeed:ѧϰ����
//ͼ����
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
//op_value:ƫ��ֵ
//active_fi_str:�����
//����cnn_conv��
GraphStr *graph_cnn_conv_create(const array<uint16_t, 4>kernel_buf,const array<uint16_t, 4>out_buf,const array<uint8_t, 4>stride_buf,const float op_value, active_fi_str(fi))
{
	//����һ��ͼ
	GraphStr *graph = new GraphStr();
	//����һ��cnn_conv
	cnn_conv *cnn_conv_ = new cnn_conv(kernel_buf, out_buf, stride_buf, op_value, fi);
	//��cnn_convװ�ص�ͼ
	graph->graph_data = cnn_conv_;
	graph->graph_type = _cnn_conv;
	return graph;
}

//line_v:�г�
//row_v:�г�
//out_v:��������ߴ���Ϣ
//type:�ػ���������
//���������ػ�ͼ
GraphStr *graph_cnn_pool_create(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type)
{
	GraphStr *graph = new GraphStr();
	cnn_pool *pooling = new cnn_pool(line_v, row_v, out_v, type);
	graph->graph_data = pooling;
	graph->graph_type = _cnn_pool;
	return graph;
}

