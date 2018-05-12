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
#define _mlp	  0x01
#define _cnn_conv 0x02
#define _cnn_pool 0x04
#define _arch     0x08

//�������ݶ�ȡ��
#define _graph_get_conv(name)   _get_cnn_conv(name->graph_data)
#define _graph_get_pool(name)   _get_cnn_pool(name->graph_data)
#define _graph_get_tensor(name) _get_tensor(name->graph_data)
#define _graph_get_arch(name)   _get_arch(name->graph_data)
#define _graph_get_mlp(name)    _get_mlp(name->graph_data)

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
bool graph_forward_switch(struct TensorStr *tensor, struct GraphStr *graph, const uint8_t direct);
//����mlpͼ
GraphStr *graph_mlp_create(uint16_t line, uint16_t row, float op, bool (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat));
//����tensorarchͼ
GraphStr *graph_tensorarch_create(array<uint16_t, 4>l_u_buf, array<uint16_t, 4>r_d_buf);
//��ӡͼ
bool graph_output(const GraphStr *graph, uint8_t content);
//tensorarchͼ����
bool graph_tensorarch_op(GraphStr *tensorarch_add, const uint8_t direct);
//ͼ����ʼ��
GraphStr *graph_chain_init(GraphStr **graph_buf, uint16_t chain_len);
//��õ�ǰͼ���ڵ�ͼ
GraphStr *graph_next(GraphStr *in_grpah, uint8_t direct);
//���򴫲�ͼ����ѡ��
bool graph_back_switch(struct GraphStr *l_graph, struct GraphStr *now_graph);
//��Կ�ʼ�ڵ�ķ��򴫲�ͼ����ѡ��ĺ�������
bool graph_back_switch(struct TensorStr *tensor, struct GraphStr *now_graph);
//����ͼ
bool graph_update(GraphStr *graph, const float learmspeed);
//����cnn_vconvͼ
GraphStr *graph_cnn_conv_create(const array<uint16_t, 4>kernel_buf,const array<uint16_t, 4>out_buf,const array<uint8_t, 4>stride_buf, \
								const float op_value, bool(*fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat));
//���������ػ�ͼ
GraphStr *graph_cnn_pool_create(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type);


#endif 
#pragma once


