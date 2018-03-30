#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

#define signmoid_active 0x01
#define tanh_active		0x02
#define relu_active     0x04
#define softmax_active  0x08

#define train_size 72

#define error_scope 0.05f

#define leardpeed 0.01f

#define bias0 0.2f
#define bias1 0.2f

extern uint8_t train_buf[train_size];

typedef struct TrainStruct {
	struct MatrixStr *mat;
	struct MatrixStr *layer[2];
	struct MatrixStr *outmat[2];
	struct MatrixStr *target;
	struct MatrixStr **target_set;
	struct MatrixStr *error_mat[2];
	float *tr_message;
	bool (*active_fi[2]) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
	bool (*active_fid[2]) (const struct MatrixStr *mat , struct MatrixStr *loadmat, const struct MatrixStr *target);
}TrStr;

//���򴫲�
bool back_propaga(TrStr *tr);
//������
bool error_analysis(float error_value);
//ǰ�򴫲�
float forward_propaga(TrStr *tr);
//��ʼѵ��
bool Train_start(const char *simaple_file, const uint32_t i, TrStr *tr);
//ѵ����ʼ��
bool Train_init(TrStr *tr, struct MatrixStr *hide_mat, struct MatrixStr *end_mat, struct MatrixStr **target_set, float *tr_message, uint8_t ac_fi0, uint8_t ac_fi1);
//���Է���
bool train_test(const char *simaple_file, const uint32_t i, TrStr *tr);

#endif // !_network_h_

