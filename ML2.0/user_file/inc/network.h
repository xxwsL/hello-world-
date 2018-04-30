#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

//�������
#define _signmoid_active mat_signmoid_par
#define _tanh_active	 mat_tanh_par
#define _relu_active     mat_relu_par
#define _softmax_active  mat_softmax_par

//������󵼺�����
#define _signmoid_fd mat_signmoid_der
#define _tanh_fd	 mat_tanh_der
#define _relu_fd     mat_relu_der
#define _softmax_fd  mat_softmax_der

//��ʧ������
#define _sqaure_loss   1.0f
#define _cross_entropy 2.0f

//network_l���ݱ�־
#define _tr_mes 0x01
#define _tr_strat_graph 0x02 
#define _tr_end_graph   0x04 
#define _tr_all_graph   0x08
#define _tr_target_mes  0x10
#define _tr_target_data 0x20
#define _tr_train_mes   0x40
#define _tr_train_data  0x80


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
	//label
	uint16_t *label;
	//�������
	struct TensorStr *in_train;
	//��ʧ����
	float (*loss_fi) (const struct MatrixStr *mat, const struct MatrixStr *target);
}train;

//���������
class network_l {
public:
	train tr;
	//���캯��
	network_l(float *tr_message, struct GraphStr *start_graph, struct TensorStr *target_set, struct TensorStr *in_train);
	network_l();
	//��������
	~network_l();
	//��ӡ�������������
	bool output(uint16_t content_0 = 0, uint8_t content_1 = 0);
	//ι����
	bool feed_data(const char *simaple_file, const uint32_t i, uint16_t label);
	//����ι����
	bool batch_feed_data(const char *simaple_file, const uint32_t *i, uint16_t label);
	//������ǰ�򵥲�����
	bool forward_propaga_step(struct GraphStr *graph, uint8_t direct);
	//������ǰ�򴫲�
	bool forward_propaga(uint16_t nums = 0);
	//������������
	float total_error(uint16_t label);
	//�����練�򴫲�
	bool back_propaga(uint16_t label, uint16_t nums = 0);
	//����������
	bool network_l::update(void);
	//ѵ��
	int train(void);
	//����
	float test(uint16_t label = 0);
private:
};

#endif 



