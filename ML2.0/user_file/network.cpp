#include "network.h"

uint8_t train_buf[train_size];


//�Ż�����:3
//ǰ�򴫲�
//tr:ѵ����
//return:int��־λ
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
	////��ӡ����
	//output(mlp_add->outmat);													
	//error_total = tr->loss_fi(mlp_add->outmat, tr->target_load);
	//printf("��� = %f\n", error_total);
	return error_total;
}

//�Ż�����:0
//������
//error_value:���ֵ
//return:int��־λ
int error_analysis(float error_value)
{
	//if (error_value < error_scope)
	//	return true;
	//else
		return false;
}

//�Ż�����:1
//ѵ����ʼ
//simaple_file:�����ļ�·��
//simaples:��������
//train_buf:ѵ����������buf
//train_size:������С
//tr:ѵ����
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
	//	printf("ѵ����� = %d\n", i);
	return true;
}

//�Ż�����:1
//���Է���
//simaple_file:���������ļ���ַ
//i:�������
//tr:ѵ����
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

//�Ż�����:0
//�������Ӳ�΢������
//tr:ѵ��ģ����
//rreturn:int��־λ
int mlp_der(MlpStr *train) 
{
	//uint16_t i = NULL, mlps = NULL,mlp_l=NULL,mlp_r=NULL;
	//uint16_t j = NULL, k = NULL, mlps_temp0 = NULL, mlps_temp1 = NULL;
	//uint32_t line_offset = NULL;
	//float *der_mataddr = NULL, *r_mlpaddr = NULL,*mlp_waddr=NULL;
	//float temp_sum = NULL;
	//mlps = (uint16_t)tr->mlp_message[0];
	////��������΢������
	//auto_load_active_fd(mlps, tr);
	//tr->active_fid(tr->outmat[mlps], tr->der_mat[mlps], tr->target_load);
	////�����һ�㻹��΢�ֵĲ���
	//for (i=1; i <= mlps;++i) {
	//	//ȷ��΢�ֲ��Ԫ�ظ��������ݵ�ַ��ֵ
	//	mlp_l = mlps - i;
	//	mlps_temp0 = tr->outmat[mlp_l]->line;
	//	//�Ը����������
	//	auto_load_active_fd(mlp_l, tr);
	//	tr->active_fid(tr->outmat[mlp_l],tr->der_mat[mlp_l],NULL);
	//	der_mataddr = (float*)tr->der_mat[mlp_l]->SaveAddr;
	//	//ȷ��΢�����Ӳ�Ԫ�ظ�������ַ��ֵ
	//	mlp_r = mlps - i + 1;
	//	mlps_temp1 = tr->outmat[mlp_r]->line;
	//	r_mlpaddr = (float*)tr->der_mat[mlp_r]->SaveAddr;
	//	mlp_waddr = (float*)tr->layer[mlp_r]->SaveAddr;
	//	//΢�ֲ�Ԫ�ظ��¸���
	//	for (j=0; j < mlps_temp0; ++j) {
	//		//Ӱ���ʹ��Ԫ�ظ���
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

//�Ż�����:0
//����ȫ�����Ӳ�Ȩ��
//tr:ѵ��ģ����
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

//�Ż�����:0
//�������Ӳ�Ȩ��
//update_mat:����Ȩ�ض���
//der_mat:����Ȩ�ض����Ӧ��΢�ֲ�
//o_mat:����Ȩ�ض����Ӧ��Ӱ���
//tr:ѵ��ģ����
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

//�Ż�����:0
//�Զ�װ���󵼺���
//i:������Ӧ����
//tr:ȫ����������
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

//�Ż�����:0
//re_message:ѵ������Ϣ
//statr_graph:ѵ��ͼ��ʼ�ڵ�
//end_graph:ѵ��ͼ��β�ڵ�
//target_set:��ǩ��
//�������๹�캯��(�����β�)
network_l::network_l(float *tr_message, struct GraphStr *start_graph, TensorStr *target_set, TensorStr *in_train)
{
	GraphStr *p=NULL;
	//ѵ��ģ����Ϣ��ʼ��
	tr.tr_message = tr_message;
	//ѵ��ͼ��ʼ�ڵ��ʼ��
	tr.strat_graph = start_graph;
	//ѵ��ͼ��β�ڵ��ʼ��
	p = tr.strat_graph;
	while (p->right_add) {
		p = p->right_add;
	}
	tr.end_graph = p;
	//ѵ����ǩ���ϳ�ʼ��
	tr.target_set = target_set;
	//��ʼ����ʧ����
	switch ((uint16_t)tr.tr_message[0]) {
	case (uint16_t)sqaure_loss:
		//ƽ������ʧ����
		tr.loss_fi = mat_square_loss;
		break;
	case (uint16_t)cross_entropy:
		//��������ʧ����
		tr.loss_fi = mat_cross_entropy;
		break;
	default:tr.loss_fi=NULL;
		break;
	}
	tr.in_train = in_train;
}

//�Ż�����:0
//������Ĭ�Ϲ��캯��
network_l::network_l()
{
	//ѵ��ģ����Ϣ��ʼ��
	tr.tr_message = NULL;
	//ѵ��ͼ��ʼ�ڵ��ʼ��
	tr.strat_graph = NULL;
	//ѵ��ͼ��β�ڵ��ʼ��
	tr.end_graph = NULL;
	//ѵ����ǩ���ϳ�ʼ��
	tr.target_set = NULL;
	//��ʼ����ʧ����
	tr.loss_fi = NULL;
}

//�Ż�����:0
//network_l����������
network_l::~network_l()
{

}

//�Ż�:0
//��ӡnetwork_l��
//content0:����0
//content1:����1
int network_l::output(uint16_t content_0, uint8_t content_1)
{
	uint16_t i = NULL;
	GraphStr *graph_p = NULL;
	//��ӡ��Ϣ
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
	//��ӡ��ʼͼ
	if (content_0&_tr_strat_graph) {
		cout << "tr_strat_graph :" << endl << "addr = " << tr.strat_graph << endl << "graph_type = ";
		graph_output(tr.strat_graph, content_1);
		cout << endl;
	}
	//��ӡ��βͼ
	if (content_0&_tr_end_graph) {
		cout << "tr_end_graph :" << endl << "addr = " << tr.end_graph << endl << "graph_type = ";
		graph_output(tr.end_graph, content_1);
		cout << endl;
	}
	//��ӡȫ��ͼ
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
	//��ӡ��ǩ����Ϣ
	if (content_0&_tr_target_mes) {
		cout << "target_set_mes : ";
		tensor_message(tr.target_set);
	}
	//��ӡ��ǩ������
	if (content_0&_tr_target_data) {
		cout << "target_set_data : " << endl;
		tensor_output(tr.target_set);
	}
	//��ӡѵ������������Ϣ
	if (content_0&_tr_train_mes) {
		cout << "tr_train_mes : " << endl;
		tensor_message(tr.in_train);
	}
	//��ӡѵ����������
	if (content_0&_tr_train_data) {
		cout << "tr_train_data : " << endl;
		tensor_output(tr.in_train);
	}
	return true;
}

//�Ż�����:0
//����ǰ�򴫲�
int network_l::forward_propaga_step(struct GraphStr *graph,uint8_t direct)
{
	//װ����Ϊ��ǰ�ڵ����������
	graph_forward_switch(get_graph_tensor( graph, direct), graph, direct);
	return true;
}

//������ǰ�򴫲�
int network_l::forward_propaga(void)
{
	float error_total = NULL;
	GraphStr *graph_p = tr.strat_graph;
	//��һ��ǰ�򴫲�
	graph_forward_switch(tr.in_train, graph_p, _direct_left);
	//�м��ǰ�򴫲�
	graph_p = tr.strat_graph->right_add;
	while (graph_p){
		//ǰ�򴫲�һ��
		forward_propaga_step(graph_p, _direct_left);
		graph_p = graph_p->right_add;
	}
	return true;
}

//����������
//label:��ǩ
float network_l::total_error(uint16_t label)
{
	return tr.loss_fi(get_graph_tensor(tr.end_graph, _direct_now)->mat[0],tr.target_set->mat[label]);
}

//�����練�򴫲�
//label:��ǩ
int network_l::back_propaga(uint16_t label)
{
	MlpStr *mlp_0=NULL;
	GraphStr *graph_p = tr.end_graph;
	//�ж�����Ƿ����Ҫ��
	if (total_error(label) < tr.tr_message[3]) {
		cout << "ģ��Ч������" << endl;
		return false;
	}
	else {
		mlp_0 = (MlpStr*)graph_p->graph_data;
		//�����һ��΢��(���һ��ֻ����Ϊmlp��)
		mlp_0->active_fid(mlp_0->outmat->mat[0], mlp_0->outmat->mat[0],tr.target_set->mat[label]);
		//��������ݶ�(���˿�ʼ��)
		while (graph_p!=tr.strat_graph) {
			//��ǰͼ���򴫲�
			graph_back_switch(graph_p->left_add, graph_p);
			//��ǰ��һ��ͼ
			graph_p = graph_p->left_add;
		}
		//��ʼ�㷴�򴫲�(�˴�ʹ���˺�������)
		graph_back_switch(tr.in_train, graph_p);
	}
	return true;
}

//����������
int network_l::update(void)
{
	GraphStr *graph_p = tr.end_graph;
	//����������
	while (graph_p) {
		graph_update(graph_p, tr.tr_message[4]);
		graph_p = graph_p->left_add;
	}
	return true;
}


















