#include "xxwsL.h"
#include "sample.h"

//matrix_ot test date

float TempMatr[3][3] = {
	11,12,13,
	4,5,6,
	7,8,9
};

float MultMat[3][2] = {
	1,2,
	1,2,
	1,2
};

StatusStr TestStatus;									//��־��		
MatStr tempmat = f32MatInit(TempMatr);
MatStr multmat = f32MatInit(MultMat);
MatStr *voidmat0 = NULL;
MatStr *voidmat1 = NULL;

int main(void)
{
	int32_t i = NULL;	
	uint16_t s0 = NULL, s1 = NULL, s2 = NULL;
	long time_start = NULL, time_end = NULL;
	/*matrix_ot test module*/
	voidmat0 = mat_create(10000, 1000, f32Flag);
	voidmat1 = mat_create(3, 2, f32Flag);

	//printf("Test����\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat����");
	//mat_message(&tempmat);
	//output(&tempmat);

	/*tensor_ot test module*/

	/*network*/

	//����mlpͼ
	new_graph_mlp(mlp_t0, 0.0f, relu_active, 12, 576);
	new_graph_mlp(mlp_t1, 0.0f, softmax_active, 10, 12);
	//����ͼ�� ��˵�:��ʼ�ڵ�,�Ҷ˵�:��β�ڵ�
	GraphStr *graph_buf[] = {mlp_t0,mlp_t1};

	//ģ����������
	TensorStr *in_tensor = tensor_create(576, 1, 1);
	tensor_assignment(in_tensor, 1.0f);


	//��������Ϊ��,����Ϊ10������ 
	TensorStr *target_tensor=tensor_create(0,0,10);
	//����ǩ����Ϊ10�ľ���bufװ�ص��ոմ����õ�������
	load_tensor(target_tensor, target_set);
	
	//����network_l��,�����ù��캯��
	network_l net(tr_message, new_graph_chain(graph_buf), target_tensor, in_tensor);
	//network.output(tr_target_mes+tr_target_data,NULL);

	graph_output(mlp_t0, _mlp_layer);
	graph_output(mlp_t1, _mlp_layer);
	//ǰ�򴫲�
	net.forward_propaga();
	graph_output(mlp_t0, _mlp_outmat);
	graph_output(mlp_t1, _mlp_outmat);

	//���򴫲�
	net.back_propaga(0);
	//����������
	net.update();
	graph_output(mlp_t0, _mlp_layer);
	graph_output(mlp_t1, _mlp_layer);
	net.forward_propaga();
	graph_output(mlp_t0, _mlp_outmat);
	graph_output(mlp_t1, _mlp_outmat);
	
	//������֤


	time_end = clock();
	time_end -= time_start;
	//printf("time = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	while (1);
	return true;
}