#include "xxwsL.h"
#include "sample.h"

bool main(void)									
{
	int32_t i = NULL;
	uint16_t s0 = NULL, s1 = NULL, s2 = NULL;
	long time_start = NULL, time_end = NULL;
	/*network*/

	//����mlpͼ
	read_bmp_init(128);
	new_graph_mlp(mlp_t0, 0.1f, _relu_active, 12, 1024);
	new_graph_mlp(mlp_t1, 0.1f, _softmax_active, 10, 12);
	//����ͼ�� ��˵�:��ʼ�ڵ�,�Ҷ˵�:��β�ڵ�
	GraphStr *graph_buf[] = { mlp_t0,mlp_t1 };

	//ģ����������
	TensorStr *in_tensor = tensor_create(1024, 1, 1);
	tensor_assignment(in_tensor, 1.0f);


	//��������Ϊ��,����Ϊ10������ 
	TensorStr *target_tensor = tensor_create(0, 0, 10);
	//����ǩ����Ϊ10�ľ���bufװ�ص��ոմ����õ�������
	load_tensor(target_tensor, target_set);

	//����network_l��,�����ù��캯��
	network_l net(tr_message, new_graph_chain(graph_buf), target_tensor, in_tensor);

	//ι����
	net.feed_data("D:\\work\\ML\\ML_project\\simaple\\guiyi\\0\\0_", 1, 0);

	//ѵ��
	for (i = 0; i < 10; ++i) {
		net.train();
	}
	//������֤
	net.output(_tr_all_graph, _mlp_outmat);

	//time_end = clock();
	//time_end -= time_start;
	//printf("time = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	while (1);
	return true;
}

