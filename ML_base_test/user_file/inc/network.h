#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

#define signmoid_active 0x01
#define tanh_active		0x02
#define relu_active     0x04
#define softmax_active  0x08

#define sqaure_loss	  0x01
#define cross_entropy 0x02

#define train_size 72

#define error_scope 0.05f

#define leardpeed 0.1f

#define bias0 0.2f
#define bias1 0.2f
#define bias2 0.2f

extern uint8_t train_buf[train_size];

typedef struct TrainStruct {
	struct MatrixStr *train_mat;
	struct MatrixStr *layer[3];
	struct MatrixStr *outmat[3];
	struct MatrixStr *der_mat[3];
	struct MatrixStr *target_load;
	struct MatrixStr **target_set;
	float *tr_message;
	bool (*active_fi[3]) (const MatrixStr *mat, MatrixStr *loadmat);
	bool (*active_fid[3]) (const MatrixStr *mat , MatrixStr *loadmat, const MatrixStr *target);
	float (*loss_fi) (const struct MatrixStr *mat, const MatrixStr *target);
}TrStr;

//反向传播
bool back_propaga(TrStr *tr);
//误差分析
bool error_analysis(float error_value);
//前向传播
float forward_propaga(TrStr *tr);
//开始训练
bool Train_start(const char *simaple_file, const uint32_t i, TrStr *tr);
//训练初始化
bool Train_init(TrStr *tr, MatrixStr **layer, MatrixStr **target_set, float *tr_message, const uint8_t *tr_fi);
//测试泛化
bool train_test(const char *simaple_file, const uint32_t i, TrStr *tr);
//各个连接层微分
bool mlp_der(TrStr *tr);
//更新全部连接层权重
bool update_all_layer(TrStr *tr);
//更新连接层权重
bool update_layer(MatrixStr *update_mat, const MatrixStr *der_mat, const MatrixStr *o_mat, TrStr *tr);

#endif // !_network_h_

