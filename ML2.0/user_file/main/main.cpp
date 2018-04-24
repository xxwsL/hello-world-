#include "xxwsL.h"
#include "sample.h"

bool main(void)									
{
	int32_t i = NULL;
	uint16_t s0 = NULL, s1 = NULL, s2 = NULL;
	long time_start = NULL, time_end = NULL;
	/*network*/

	//创建mlp图
	read_bmp_init(128);
	new_graph_mlp(mlp_t0, 0.1f, _relu_active, 12, 1024);
	new_graph_mlp(mlp_t1, 0.1f, _softmax_active, 10, 12);
	//创建图表 左端点:开始节点,右端点:结尾节点
	GraphStr *graph_buf[] = { mlp_t0,mlp_t1 };

	//模拟输入张量
	TensorStr *in_tensor = tensor_create(1024, 1, 1);
	tensor_assignment(in_tensor, 1.0f);


	//创建内容为空,容量为10的张量 
	TensorStr *target_tensor = tensor_create(0, 0, 10);
	//将标签集长为10的矩阵buf装载到刚刚创建好的张量中
	load_tensor(target_tensor, target_set);

	//创建network_l类,并调用构造函数
	network_l net(tr_message, new_graph_chain(graph_buf), target_tensor, in_tensor);

	//喂数据
	net.feed_data("D:\\work\\ML\\ML_project\\simaple\\guiyi\\0\\0_", 1, 0);

	//训练
	for (i = 0; i < 10; ++i) {
		net.train();
	}
	//测试验证
	net.output(_tr_all_graph, _mlp_outmat);

	//time_end = clock();
	//time_end -= time_start;
	//printf("time = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	while (1);
	return true;
}

