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
		//cnn�ڵ�
	case _cnn:
		//tensor_add = ((cnn*)temp_add->graph_data);
		return false;
		break;
		//tensor_c�ڵ�
	case _tensorarch:
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

//�Ż�����:0
//l_u_line:�������г�
//l_u_row:�������г�
//l_u_height:��������
//r_d_lin:�������г�
//r_d_row:�������г�
//r_d_height:��������
//return:GraphStrָ��
//����tensorarchͼ
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

//�Ż�:0
//graph_add:ͼ��ַ
//content:����
//��ӡͼ
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

//�Ż�����:0
//����ת��ͼ����
//load_tensor:װ������
//in_tensor:��������
//direct:������������
//tensorarchͼ����
bool graph_tensorarch_op(GraphStr *tensorarch_add, const uint8_t direct)
{
	if (tensorarch_op(tensorarch_add->graph_data, get_graph_tensor(tensorarch_add,direct), direct))
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
bool graph_forward_switch(TensorStr *tensor, struct GraphStr *graph, uint8_t direct, uint16_t nums)
{
	switch (graph->graph_type) {
		//dnn�ڵ�
	case _mlp:
		mlp_one_op((MlpStr*)graph->graph_data, tensor, nums);
		break;
		//cnn�ڵ�
	case _cnn:
		break;
		//tensor_arch�ڵ�
	case _tensorarch:
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
			mlp_gr(((MlpStr*)l_graph->graph_data)->outmat, (MlpStr*)now_graph->graph_data);
			mlp_error_pass((MlpStr*)now_graph->left_add->graph_data, (MlpStr*)now_graph->graph_data);
			break;
		//��ǰͼ����ͼΪtensorarch
		case _tensorarch:

			break;
		default:
			return false;
			break;
		}
		break;
	//now_graphΪcnn
	case _cnn:
		return false;//δʵ��
		break;
	//now_graphΪtensorarch
	case _tensorarch:
		break;
	default:
		return false; 
		break;
	}
	return true;
}

//tensor:��������
//now_graph:��ǰͼ
//��Կ�ʼ�ڵ�ķ��򴫲�ͼ����ѡ��ĺ�������
bool graph_back_switch(struct TensorStr *tensor, struct GraphStr *now_graph, uint16_t nums)
{
	switch (now_graph->graph_type) {
		//now_graphΪdnn
	case _mlp:
		mlp_gr(tensor, (MlpStr*)now_graph->graph_data);
		break;
		//now_graphΪcnn
	case _cnn:
		return false;//δʵ��
		break;
	default:
		return false;
		break;
	}
	return true;
}

//graph:����ͼ
//learmspeed:ѧϰ����
//ͼ����
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

