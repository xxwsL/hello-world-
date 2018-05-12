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

	////创建mlp图
	//GraphStr *mlp_t0 = graph_mlp_create(12, 1024, 0.1f, _relu_active);
	//GraphStr *mlp_t1 = graph_mlp_create(10, 12, 0.1f, _softmax_active);
	////创建图表 左端点:开始节点,右端点:结尾节点
	//GraphStr *graph_buf[] = { mlp_t0,mlp_t1 };

	////模拟输入张量
	//TensorStr *in_tensor = tensor_create(1024, 1, 1);
	//tensor_assign(in_tensor, 1.0f);


	//创建内容为空,容量为10的张量 
	TensorStr *target_tensor = tensor_create(0, 0, 10);
	//将标签集长为10的矩阵buf装载到刚刚创建好的张量中
	load_tensor(target_tensor, target_set);

	////创建network_l类,并调用构造函数
	//network_l net(tr_message, new_graph_chain(graph_buf), target_tensor, in_tensor);

	////喂数据
	//net.feed_data("D:\\work\\ML\\ML_project\\simaple\\guiyi\\0\\0_", 1, 0);

	////训练
	//for (i = 0; i < 5; ++i) {
	//	net.train();
	//}
	////测试验证
	//net.output(_tr_all_graph, _mlp_gr_op);

	//while (1);

	/*network_l*/
	//创建模拟输入张量0
	TensorStr *tensor0 = tensor_create(32, 32, 1, 1);		//创建6x6x1x3的张量
	tensor_rand_normal_mat(tensor0);						
	//tensor_output(tensor0);								//打印tensor0

	//创建cnn_conv0
	b0 = { 3,3,3,1 };			//卷积核张量尺寸
	b1 = { 15,15,3,1 };			//卷积输出张量尺寸
	b2 = { 2,2,0,0 };			//卷积步伐信息
	GraphStr *cnn_conv0 = graph_cnn_conv_create(b0, b1, b2, 0.0f, _relu_active);			
	//tensor_assign(_graph_get_conv(cnn_conv0)->kernel, 1.0f);
	//_graph_get_conv(cnn_conv0)->conv_ot(tensor0);
	//graph_output(cnn_conv0, _graph_all);

	//创建cnn_conv1
	b0 = { 2,2,6,1 };			//卷积核张量尺寸
	b1 = { 14,14,6,1 };		//卷积输出张量尺寸
	b2 = { 1,1,0,0 };			//卷积步伐信息
	GraphStr *cnn_conv1 = graph_cnn_conv_create(b0, b1, b2, 0.0f, _relu_active);			
	//tensor_assign(_graph_get_conv(cnn_conv1)->kernel, 1.0f);
	//_graph_get_conv(cnn_conv1)->conv_ot(_graph_get_conv(cnn_conv0)->out);
	//graph_output(cnn_conv1, _graph_all);

	//创建pool层
	b0 = { 7,7,6,1 };
	GraphStr *cnn_pool0 = graph_cnn_pool_create(2,2,b0,_cnn_pooling_aver);

	//创建tensorarch0
	b0 = { 7,7,6,1 };
	b1 = { 294,1,1,1 };
	GraphStr *arch0 = graph_tensorarch_create(b0, b1);
	//tensorarch_op(_graph_get_arch(arch0),_graph_get_pool(cnn_pool0)->out,_direct_left);
	//graph_output(arch0, _graph_all);

	//创建mlp0
	GraphStr *mlp0 = graph_mlp_create(12, 294, 0.0f, _relu_active);
	//graph_output(mlp0,_graph_all);

	//创建mlp1
	GraphStr *mlp1 = graph_mlp_create(10, 12, 0.0f, _softmax_active);
	//graph_output(mlp1, _graph_all);

	//将标签集长为10的矩阵buf装载到刚刚创建好的张量中
	load_tensor(target_tensor, target_set);

	//创建神经网络
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

