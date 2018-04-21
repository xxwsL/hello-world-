#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

//�������
#define signmoid_active mat_signmoid_par
#define tanh_active		mat_tanh_par
#define relu_active     mat_relu_par
#define softmax_active  mat_softmax_par

//������󵼺�����
#define signmoid_fd mat_signmoid_der
#define tanh_fd		mat_tanh_der
#define relu_fd     mat_relu_der
#define softmax_fd  mat_softmax_der

//��ʧ������
#define sqaure_loss	  1.0f
#define cross_entropy 2.0f

//network_l���ݱ�־
#define _tr_mes 0x01
#define _tr_strat_graph 0x02 
#define _tr_end_graph   0x04 
#define _tr_all_graph   0x08
#define _tr_target_mes  0x10
#define _tr_target_data 0x20
#define _tr_train_mes   0x40
#define _tr_train_data  0x80

//��������buf�ߴ��
#define train_size 72

extern uint8_t train_buf[train_size];


//ѵ����
typedef struct Train {
	//tr��Ϣ
	float *tr_message;
	//����ͼ��ʼ�ڵ�
	struct GraphStr *strat_graph;
	//����ͼ��β�ڵ�
	struct GraphStr *end_graph;
	//�������󼯺�
	struct TensorStr *target_set;
	//�������
	struct TensorStr *in_train;
	//��ʧ����
	float (*loss_fi) (const struct MatrixStr *mat, const struct MatrixStr *target);
}train;

//���������
class network_l {
public:
	//���캯��
	network_l(float *tr_message, struct GraphStr *start_graph, struct TensorStr *target_set, struct TensorStr *in_train);
	network_l();
	//��������
	~network_l();
	//��ӡ�������������
	int output(uint16_t content_0, uint8_t content_1);
	//ι��������
	//feed_in()
	//������ǰ�򵥲�����
	int forward_propaga_step(struct GraphStr *graph, uint8_t direct);
	//������ǰ�򴫲�
	int forward_propaga(void);
	//������������
	float total_error(uint16_t label);
	//�����練�򴫲�
	int back_propaga(uint16_t label);
	//����������
	int network_l::update(void);
private:
	train tr;
};


#endif 



