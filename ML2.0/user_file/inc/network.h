#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

//激活函数宏
#define _signmoid_active mat_signmoid_par
#define _tanh_active	 mat_tanh_par
#define _relu_active     mat_relu_par
#define _softmax_active  mat_softmax_par

//激活函数求导函数宏
#define _signmoid_fd mat_signmoid_der
#define _tanh_fd	 mat_tanh_der
#define _relu_fd     mat_relu_der
#define _softmax_fd  mat_softmax_der

//损失函数宏
#define _sqaure_loss   1.0f
#define _cross_entropy 2.0f

//network_l内容标志
#define _tr_mes 0x01
#define _tr_strat_graph 0x02 
#define _tr_end_graph   0x04 
#define _tr_all_graph   0x08
#define _tr_target_mes  0x10
#define _tr_target_data 0x20
#define _tr_train_mes   0x40
#define _tr_train_data  0x80


//训练类
typedef struct Train {
	//tr信息
	float *tr_message;
	//计算图开始节点
	struct GraphStr *strat_graph;
	//计算图结尾节点
	struct GraphStr *end_graph;
	//期望矩阵集合
	struct TensorStr *target_set;
	//label
	uint16_t *label;
	//输入矩阵
	struct TensorStr *in_train;
	//损失函数
	float (*loss_fi) (const struct MatrixStr *mat, const struct MatrixStr *target);
}train;

//神经网络的类
class network_l {
public:
	train tr;
	//构造函数
	network_l(float *tr_message, struct GraphStr *start_graph, struct TensorStr *target_set, struct TensorStr *in_train);
	network_l();
	//析构函数
	~network_l();
	//打印神经网络类的内容
	bool output(uint16_t content_0 = 0, uint8_t content_1 = 0);
	//喂数据
	bool feed_data(const char *simaple_file, const uint32_t i, uint16_t label);
	//批量喂数据
	bool batch_feed_data(const char *simaple_file, const uint32_t *i, uint16_t label);
	//神经网络前向单步操作
	bool forward_propaga_step(struct GraphStr *graph, uint8_t direct);
	//神经网络前向传播
	bool forward_propaga(uint16_t nums = 0);
	//计算输出总误差
	float total_error(uint16_t label);
	//神经网络反向传播
	bool back_propaga(uint16_t label, uint16_t nums = 0);
	//更新神经网络
	bool network_l::update(void);
	//训练
	int train(void);
	//测试
	float test(uint16_t label = 0);
private:
};

#endif 



