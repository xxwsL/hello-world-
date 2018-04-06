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
	//ѵ���������
	struct MatrixStr *train_mat;
	//ȫ���Ӳ㼯��
	struct MatrixStr **layer;
	//����㼯��
	struct MatrixStr **outmat;
	//΢�ֲ㼯
	struct MatrixStr **der_mat;
	//װ�����������ָ��
	struct MatrixStr *target_load;
	//�������󼯺�
	struct MatrixStr **target_set;
	//���Ӽ���
	float *op_set;
	//ȫ����������Ϣ
	uint16_t *mlp_message;
	//���������
	bool (**active_fi) (const MatrixStr *mat, MatrixStr *loadmat);
	//�󵼺�������
	bool (*active_fid) (const MatrixStr *mat , MatrixStr *loadmat, const MatrixStr *target);
	//��ʧ����
	float (*loss_fi) (const struct MatrixStr *mat, const MatrixStr *target);
}ms;

//���򴫲�
bool back_propaga(ms *tr);
//������
bool error_analysis(float error_value);
//ǰ�򴫲�
float forward_propaga(ms *tr);
//��ʼѵ��
bool Train_start(const char *simaple_file, const uint32_t i, ms *tr);
//ѵ����ʼ��
bool Train_init(ms *tr, MatrixStr **layer, MatrixStr **target_set, float *op_set, uint16_t *mlp_message_buf,bool (**fi) (const MatrixStr *mat, MatrixStr *loadmat));
//���Է���
bool train_test(const char *simaple_file, const uint32_t i, ms *tr);
//�������Ӳ�΢��
bool mlp_der(ms *tr);
//����ȫ�����Ӳ�Ȩ��
bool update_all_layer(ms *tr);
//�������Ӳ�Ȩ��
bool update_layer(MatrixStr *update_mat, const MatrixStr *der_mat, const MatrixStr *o_mat, ms *tr);
//�Զ�ѡ���󵼺���
bool auto_load_active_fd(uint16_t i, ms *tr);

#endif // !_network_h_

