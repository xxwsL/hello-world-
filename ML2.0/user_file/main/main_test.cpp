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

StatusStr TestStatus;									//标志类		
MatStr tempmat = f32MatInit(TempMatr);
MatStr multmat = f32MatInit(MultMat);

int main(void)
{
	int32_t i = NULL, j = NULL;
	uint16_t s0 = NULL, s1 = NULL, s2 = NULL;
	long time_start = NULL, time_end = NULL;
	array<uint16_t, 4> b0;
	array<uint16_t, 4> b1;
	array<uint8_t, 4>  b2;
	/*matrix_ot test module*/

	MatrixStr *voidmat0 = mat_create(2, 2, f32Flag);
	MatrixStr *voidmat1 = mat_create(2, 2, f32Flag);
	MatrixStr *voidmat2 = mat_create(3, 3, f32Flag);

	mat_up_assign(voidmat0, 0.0f);
	output(voidmat0);
	mat_up_assign(voidmat1, 0.0f);

	mat_conv_back(voidmat0, voidmat1, voidmat2, 1, 1);
	output(voidmat2);

	//printf("Test矩阵\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat矩阵");
	//mat_message(&tempmat);
	//output(&tempmat);

	/*tensor_ot test module*/

	/*cnn*/

	//创建模拟输入张量
	TensorStr *tensor0 = tensor_create(8, 8, 1);
	tensor_assignment(tensor0, 2.0f);

	//创建cnn卷积图
	//b0 = { 2,2,2,1 };
	//b1 = { 7,7,2,1 };
	//b2 = { 1,1,0,0 };
	//time_start = clock();
	//GraphStr *conv0 = graph_cnn_conv_create(b0, b1, b2, 0.1f, _relu_active);
	//tensor_assignment(((cnn_conv*)conv0->graph_data)->kernel, 1.25f);
	////((cnn_conv*)conv0->graph_data)->conv_ot(tensor0);

	//b0 = { 2,2,2,1 };
	//b1 = { 6,6,4,1 };
	//b2 = { 1,1,0,0 };
	//GraphStr *conv1 = graph_cnn_conv_create(b0, b1, b2, 0.1f, _relu_active);
	//tensor_assignment(((cnn_conv*)conv1->graph_data)->kernel, 1.25f);

	////创建cnn池化图
	//b0 = { 3,3,4,1 };
	//GraphStr *pooling0 = graph_cnn_pooling_create(2,2,b0,_cnn_pooling_aver);
	//
	////创建tensorarch图
	//b0 = { 3,3,4,1 };
	//b1 = { 36,1,1,1 };
	//GraphStr *tensorarch0 = graph_tensorarch_create(b0, b1);

	////创建mlp图
	//GraphStr *mlp0 = graph_mlp_create(10, 36, 0.0f, _relu_active);
	//GraphStr *mlp1 = graph_mlp_create(3, 10, 0.0f, _softmax_active);

	////创建内容为空,容量为10的张量 
	//TensorStr *target_tensor = tensor_create(0, 0, 2);
	////将标签集长为10的矩阵buf装载到刚刚创建好的张量中
	//load_tensor(target_tensor, target_set);

	////创建神经网络
	//GraphStr *chain0[] = { conv0,conv1, pooling0, tensorarch0, mlp0, mlp1 };
	//network_l *net0 = new network_l(tr_message, new_graph_chain(chain0), target_tensor, tensor0);
	//net0->forward_propaga();

	//net0->output(_tr_all_graph, _graph_all);

	

	time_end  = clock();
	time_end -= time_start;
	printf("time = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	while (1);
	return true;
}