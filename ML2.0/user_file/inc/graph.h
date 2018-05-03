#ifndef _graph_h_
#define _graph_h_
#include "xxwsL.h"

#define _graph_all 0xff

//ͼ��������
#define _direct_left  0x01
#define _direct_up	  0x02
#define _direct_right 0x04
#define _direct_down  0x08
#define _direct_now   0x10

//ͼ���ͺ�
#define _mlp		 0x01
#define _cnn_conv	 0x02
#define _cnn_pooling 0x04
#define _tensorarch  0x08

//ͼ����ʼ��
#define new_graph_chain(name)  graph_chain_init(name,sizeof(name)/sizeof(struct GraphStr*))

//����ͼ��
typedef struct GraphStr {
	//ͼ������
	uint8_t graph_type;
	//ͼ���ݵ�ַ
	void *graph_data;
	//��ͼ��ַ
	struct GraphStr *left_add;
	//��ͼ��ַ
	struct GraphStr *up_add;
	//��ͼ��ַ
	struct GraphStr *right_add;
	//��ͼ��ַ
	struct GraphStr *down_add;

}graphstr;

//��ȡ��һ��ڵ������
struct TensorStr *get_graph_tensor(struct GraphStr *graph, uint8_t direct);
//ǰ�򴫲�ͼ����ѡ��
bool graph_forward_switch(struct TensorStr *tensor, struct GraphStr *graph, uint8_t direct, uint16_t nums = 0, uint16_t deep = 0);
//����mlpͼ
GraphStr *graph_mlp_create(uint16_t line, uint16_t row, float op, bool (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat));
//����tensorarchͼ
GraphStr *graph_tensorarch_create(array<uint16_t, 4>l_u_buf, array<uint16_t, 4>r_d_buf);
//��ӡͼ
bool graph_output(void *graph_add, uint8_t content);
//tensorarchͼ����
bool graph_tensorarch_op(GraphStr *tensorarch_add, const uint8_t direct);
//ͼ����ʼ��
GraphStr *graph_chain_init(GraphStr **graph_buf, uint16_t chain_len);
//��õ�ǰͼ���ڵ�ͼ
GraphStr *graph_next(GraphStr *in_grpah, uint8_t direct);
//���򴫲�ͼ����ѡ��
bool graph_back_switch(struct GraphStr *l_graph, struct GraphStr *now_graph);
//��Կ�ʼ�ڵ�ķ��򴫲�ͼ����ѡ��ĺ�������
bool graph_back_switch(struct TensorStr *tensor, struct GraphStr *now_graph, uint16_t nums = 0);
//����ͼ
bool graph_update(GraphStr *graph, float learmspeed);
//����cnn_vconvͼ
GraphStr *graph_cnn_conv_create(array<uint16_t, 4>kernel_buf, array<uint16_t, 4>out_buf, array<uint8_t, 4>stride_buf, \
								float op_value, bool(*fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat));
//���������ػ�ͼ
GraphStr *graph_cnn_pooling_create(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type);


#endif 
#pragma once


