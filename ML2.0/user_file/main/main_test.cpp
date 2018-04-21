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

	//printf("Test矩阵\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat矩阵");
	//mat_message(&tempmat);
	//output(&tempmat);

	/*tensor_ot test module*/

	/*network*/

	//创建mlp图
	new_graph_mlp(mlp_t0, 0.0f, relu_active, 12, 576);
	new_graph_mlp(mlp_t1, 0.0f, softmax_active, 10, 12);
	//创建图表 左端点:开始节点,右端点:结尾节点
	GraphStr *graph_buf[] = {mlp_t0,mlp_t1};

	//模拟输入张量
	TensorStr *in_tensor = tensor_create(576, 1, 1);
	tensor_assignment(in_tensor, 1.0f);


	//创建内容为空,容量为10的张量 
	TensorStr *target_tensor=tensor_create(0,0,10);
	//将标签集长为10的矩阵buf装载到刚刚创建好的张量中
	load_tensor(target_tensor, target_set);
	
	//窗口network_l类,并调用构造函数
	network_l net(tr_message, new_graph_chain(graph_buf), target_tensor, in_tensor);
	//network.output(tr_target_mes+tr_target_data,NULL);

	graph_output(mlp_t0, _mlp_layer);
	graph_output(mlp_t1, _mlp_layer);
	//前向传播
	net.forward_propaga();
	graph_output(mlp_t0, _mlp_outmat);
	graph_output(mlp_t1, _mlp_outmat);

	//反向传播
	net.back_propaga(0);
	//更新神经网络
	net.update();
	graph_output(mlp_t0, _mlp_layer);
	graph_output(mlp_t1, _mlp_layer);
	net.forward_propaga();
	graph_output(mlp_t0, _mlp_outmat);
	graph_output(mlp_t1, _mlp_outmat);
	
	//测试验证


	time_end = clock();
	time_end -= time_start;
	//printf("time = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	while (1);
	return true;
}