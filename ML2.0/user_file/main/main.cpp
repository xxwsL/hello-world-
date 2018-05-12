#include "xxwsL.h"
#include "sample.h"

bool main(void)									
{
	int32_t i = NULL;
	uint16_t s0 = NULL, s1 = NULL, s2 = NULL;
	array<uint16_t, 4> b0;
	array<uint16_t, 4> b1;
	array<uint8_t, 4>  b2;
	long time_start = NULL, time_end = NULL;
	
	rand_init();
	read_bmp_init(128);

	time_start = clock();
	/*network*/

	////����mlpͼ
	//GraphStr *mlp_t0 = graph_mlp_create(12, 1024, 0.1f, _relu_active);
	//GraphStr *mlp_t1 = graph_mlp_create(10, 12, 0.1f, _softmax_active);
	////����ͼ�� ��˵�:��ʼ�ڵ�,�Ҷ˵�:��β�ڵ�
	//GraphStr *graph_buf[] = { mlp_t0,mlp_t1 };

	////ģ����������
	//TensorStr *in_tensor = tensor_create(1024, 1, 1);
	//tensor_assign(in_tensor, 1.0f);


	//��������Ϊ��,����Ϊ10������ 
	TensorStr *target_tensor = tensor_create(0, 0, 10);
	//����ǩ����Ϊ10�ľ���bufװ�ص��ոմ����õ�������
	load_tensor(target_tensor, target_set);

	////����network_l��,�����ù��캯��
	//network_l net(tr_message, new_graph_chain(graph_buf), target_tensor, in_tensor);

	////ι����
	//net.feed_data("D:\\work\\ML\\ML_project\\simaple\\guiyi\\0\\0_", 1, 0);

	////ѵ��
	//for (i = 0; i < 5; ++i) {
	//	net.train();
	//}
	////������֤
	//net.output(_tr_all_graph, _mlp_gr_op);

	//while (1);

	/*network_l*/
	//����ģ����������0
	TensorStr *tensor0 = tensor_create(32, 32, 1, 1);		//����6x6x1x3������
	tensor_rand_normal_mat(tensor0);						
	//tensor_output(tensor0);								//��ӡtensor0

	//����cnn_conv0
	b0 = { 3,3,3,1 };			//����������ߴ�
	b1 = { 15,15,3,1 };			//�����������ߴ�
	b2 = { 2,2,0,0 };			//���������Ϣ
	GraphStr *cnn_conv0 = graph_cnn_conv_create(b0, b1, b2, 0.0f, _relu_active);			
	//tensor_assign(_graph_get_conv(cnn_conv0)->kernel, 1.0f);
	//_graph_get_conv(cnn_conv0)->conv_ot(tensor0);
	//graph_output(cnn_conv0, _graph_all);

	//����cnn_conv1
	b0 = { 2,2,6,1 };			//����������ߴ�
	b1 = { 14,14,6,1 };		//�����������ߴ�
	b2 = { 1,1,0,0 };			//���������Ϣ
	GraphStr *cnn_conv1 = graph_cnn_conv_create(b0, b1, b2, 0.0f, _relu_active);			
	//tensor_assign(_graph_get_conv(cnn_conv1)->kernel, 1.0f);
	//_graph_get_conv(cnn_conv1)->conv_ot(_graph_get_conv(cnn_conv0)->out);
	//graph_output(cnn_conv1, _graph_all);

	//����pool��
	b0 = { 7,7,6,1 };
	GraphStr *cnn_pool0 = graph_cnn_pool_create(2,2,b0,_cnn_pooling_aver);

	//����tensorarch0
	b0 = { 7,7,6,1 };
	b1 = { 294,1,1,1 };
	GraphStr *arch0 = graph_tensorarch_create(b0, b1);
	//tensorarch_op(_graph_get_arch(arch0),_graph_get_pool(cnn_pool0)->out,_direct_left);
	//graph_output(arch0, _graph_all);

	//����mlp0
	GraphStr *mlp0 = graph_mlp_create(12, 294, 0.0f, _relu_active);
	//graph_output(mlp0,_graph_all);

	//����mlp1
	GraphStr *mlp1 = graph_mlp_create(10, 12, 0.0f, _softmax_active);
	//graph_output(mlp1, _graph_all);

	//����ǩ����Ϊ10�ľ���bufװ�ص��ոմ����õ�������
	load_tensor(target_tensor, target_set);

	//����������
	GraphStr *chain0[] = { cnn_conv0,cnn_conv1, cnn_pool0, arch0, mlp0, mlp1 };
	network_l *net0 = new network_l(tr_message, new_graph_chain(chain0), target_tensor, tensor0);
	
	net0->feed_data("D:\\work\\ML\\ML_project\\simaple\\guiyi\\0\\0_", 1, 0);
	for (i = 0; i < 2; ++i) {
		//net0->forward_propaga();
		net0->train();
	}

	net0->feed_data("D:\\work\\ML\\ML_project\\simaple\\guiyi\\1\\1_", 1, 1);
	for (i = 0; i < 2; ++i) {
		//net0->forward_propaga();
		net0->train();
	}

	net0->output(_tr_all_graph,_cnn_conv_kernel);

	net0->feed_data("D:\\work\\ML\\ML_project\\simaple\\guiyi\\0\\0_", 1, 0);
	net0->train();

	time_end = clock();
	time_end -= time_start;
	printf("time = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	while (1);
	return true;
}

