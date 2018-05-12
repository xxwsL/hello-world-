#include "network.h"

//�Ż�����:0
//re_message:ѵ������Ϣ
//statr_graph:ѵ��ͼ��ʼ�ڵ�
//end_graph:ѵ��ͼ��β�ڵ�
//target_set:��ǩ��
//�������๹�캯��(�����β�)
network_l::network_l(float *tr_message, struct GraphStr *start_graph, TensorStr *target_set, TensorStr *in_tensor)
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
	case (uint16_t)_sqaure_loss:
		//ƽ������ʧ����
		tr.loss_fi = mat_square_loss;
		break;
	case (uint16_t)_cross_entropy:
		//��������ʧ����
		tr.loss_fi = mat_cross_entropy;
		break;
	default:tr.loss_fi=NULL;
		break;
	}
	//װ��ѵ����������
	tr.in_train = in_tensor;
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
bool network_l::output(uint16_t content_0, uint8_t content_1)
{
	char key = NULL;
	int16_t i = NULL;
	GraphStr *graph_p = NULL;
	//��ӡ��Ϣ
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
bool network_l::forward_propaga_step(struct GraphStr *graph,uint8_t direct)
{
	//װ����Ϊ��ǰ�ڵ����������
	graph_forward_switch(get_graph_tensor( graph, direct), graph, direct);
	return true;
}

//nums:�����ݵ�ǰ����
//������ǰ�򴫲�
bool network_l::forward_propaga(void)
{
	float error_total = NULL;
	GraphStr *graph_p = tr.strat_graph;
	//��һ��ǰ�򴫲�
	graph_forward_switch(tr.in_train, graph_p, _direct_left);
	//������һ��ͼ
	graph_p = tr.strat_graph->right_add;
	while (graph_p){
		//ǰ�򴫲�һ��
		graph_forward_switch(get_graph_tensor(graph_p, _direct_left), graph_p, _direct_left);
		graph_p = graph_p->right_add;
	}
	return true;
}

//����������
//label:��ǩ
float network_l::total_error(void)
{
	return tr.loss_fi(get_graph_tensor(tr.end_graph, _direct_now)->mat[0],tr.target_set->mat[tr.label]);
}

//�����練�򴫲�
//label:��ǩ
bool network_l::back_propaga(void)
{
	MlpStr *mlp_0=NULL;
	GraphStr *graph_p = tr.end_graph;
	//�ж�����Ƿ����Ҫ��
	if (total_error() < tr.tr_message[3]) {
		cout << "ģ��Ч������\n";
		cout << "_______________________________________________________________________________\n";
		return false;
	}
	else {
		mlp_0 = (MlpStr*)graph_p->graph_data;
		//�����һ��΢��(���һ��ֻ����Ϊmlp��)
		mlp_0->active_fid(mlp_0->outmat->mat[0], mlp_0->outmat->mat[0],tr.target_set->mat[tr.label]);
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
bool network_l::update(void)
{
	GraphStr *graph_p = tr.end_graph;
	//����������
	while (graph_p) {
		graph_update(graph_p, tr.tr_message[4]);
		graph_p = graph_p->left_add;
	}
	return true;
}

//ι����
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


//ѵ��
int network_l::train(void)
{
	uint16_t i = NULL;
	//ǰ�򴫲�+���򴫲�
	forward_propaga();
	cout << "�������� = " << test() << "\n";
	output(_tr_end_graph, _mlp_outmat);
	back_propaga();
	//����������
	update();
	return true;
}

//����
float network_l::test(void)
{
	//ǰ�򴫲�
	forward_propaga();
	//������������
	return total_error();
}
















