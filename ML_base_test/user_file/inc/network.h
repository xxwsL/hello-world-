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

//���򴫲�
bool back_propaga(TrStr *tr);
//������
bool error_analysis(float error_value);
//ǰ�򴫲�
float forward_propaga(TrStr *tr);
//��ʼѵ��
bool Train_start(const char *simaple_file, const uint32_t i, TrStr *tr);
//ѵ����ʼ��
bool Train_init(TrStr *tr, MatrixStr **layer, MatrixStr **target_set, float *tr_message, const uint8_t *tr_fi);
//���Է���
bool train_test(const char *simaple_file, const uint32_t i, TrStr *tr);
//�������Ӳ�΢��
bool mlp_der(TrStr *tr);
//����ȫ�����Ӳ�Ȩ��
bool update_all_layer(TrStr *tr);
//�������Ӳ�Ȩ��
bool update_layer(MatrixStr *update_mat, const MatrixStr *der_mat, const MatrixStr *o_mat, TrStr *tr);

#endif // !_network_h_

