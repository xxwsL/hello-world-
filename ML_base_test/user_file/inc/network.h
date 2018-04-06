#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

#define signmoid_active mat_signmoid_par
#define tanh_active		mat_tanh_par
#define relu_active     mat_relu_par
#define softmax_active  mat_softmax_par

#define signmoid_fd mat_signmoid_der
#define tanh_fd		mat_tanh_der
#define relu_fd     mat_relu_der
#define softmax_fd  mat_softmax_der

#define sqaure_loss	  0x01
#define cross_entropy 0x02

#define train_size 72

#define error_scope 0.05f

#define learmspeed 0.1f

#define bias0 0.2f
#define bias1 0.2f
#define bias2 0.2f

extern uint8_t train_buf[train_size];

typedef struct MLPStruct {
	//训练输入矩阵
	struct MatrixStr *train_mat;
	//全链接层集合
	struct MatrixStr **layer;
	//输出层集合
	struct MatrixStr **outmat;
	//微分层集
	struct MatrixStr **der_mat;
	//装载期望矩阵的指针
	struct MatrixStr *target_load;
	//期望矩阵集合
	struct MatrixStr **target_set;
	//算子集合
	float *op_set;
	//全链接网络信息
	uint16_t *mlp_message;
	//激活函数集合
	bool (**active_fi) (const MatrixStr *mat, MatrixStr *loadmat);
	//求导函数集合
	bool (*active_fid) (const MatrixStr *mat , MatrixStr *loadmat, const MatrixStr *target);
	//损失函数
	float (*loss_fi) (const struct MatrixStr *mat, const MatrixStr *target);
}ms;

//反向传播
bool back_propaga(ms *tr);
//误差分析
bool error_analysis(float error_value);
//前向传播
float forward_propaga(ms *tr);
//开始训练
bool Train_start(const char *simaple_file, const uint32_t i, ms *tr);
//训练初始化
bool Train_init(ms *tr, MatrixStr **layer, MatrixStr **target_set, float *op_set, uint16_t *mlp_message_buf,bool (**fi) (const MatrixStr *mat, MatrixStr *loadmat));
//测试泛化
bool train_test(const char *simaple_file, const uint32_t i, ms *tr);
//各个连接层微分
bool mlp_der(ms *tr);
//更新全部连接层权重
bool update_all_layer(ms *tr);
//更新连接层权重
bool update_layer(MatrixStr *update_mat, const MatrixStr *der_mat, const MatrixStr *o_mat, ms *tr);
//自动选择求导函数
bool auto_load_active_fd(uint16_t i, ms *tr);

#endif // !_network_h_

