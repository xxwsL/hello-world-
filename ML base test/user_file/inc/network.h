#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

#define signmoid_active 0x01
#define tanh_active		0x02
#define relu_active     0x04
#define softmax_active  0x08

#define events	 1.0f
#define unevents 0.0f

#define events_sample 10

#define error_scope 0.01f

#define leardpeed 0.1f

#define bias0 0.1f
#define bias1 0.1f

typedef struct TrainStruct {
	struct MatrixStr *mat;
	struct MatrixStr *layer[2];
	struct MatrixStr *outmat[2];
	struct MatrixStr *target;
	struct MatrixStr *error_mat[2];
	float *bias_speed;
	bool (*active_fi[2]) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
	bool (*active_fid[2]) (const struct MatrixStr *mat , struct MatrixStr *loadmat, const struct MatrixStr *target);
}TrStr;

//反向传播
bool back_propaga(TrStr *tr);
//误差分析
bool error_analysis(float error_value);
//前向传播
float forward_propaga(TrStr *tr);
//开始训练
bool Train_start(const char *simaple_file, const uint16_t simaples, uint8_t *train_buf, const uint32_t train_size, TrStr *tr);
//训练初始化
bool Train_init(TrStr *tr, struct MatrixStr *mat, struct MatrixStr *hide_mat, struct MatrixStr *end_mat, float *bias_Lspeed, uint8_t ac_fi0, uint8_t ac_fi1);

#endif // !_network_h_

