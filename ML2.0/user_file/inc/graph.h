#ifndef _graph_h_
#define _graph_h_
#include "xxwsL.h"

//图操作方向
#define _direct_left  0x01
#define _direct_up	  0x02
#define _direct_right 0x04
#define _direct_down  0x08
#define _direct_now   0x10

//图类型宏
#define _mlp		0x01
#define _cnn	    0x02
#define _tensorarch 0x03

//图生成宏
//mlp图
#define new_graph_mlp(name,op,fi,line,row) struct GraphStr* name=graph_mlp_create(op,fi,line,row)
//tensorarch图
#define new_graph_tensorarch(name,line0,row0,height0,line1,row1,height1) struct GraphStr *name=\
			graph_tensorarch_create(line0, row0, height0, line1, row1, height1)

#define new_graph_chain(name)  graph_chain_init(name,sizeof(name)/sizeof(struct GraphStr*))

//计算图类
typedef struct GraphStr {
	//图的类型
	uint8_t graph_type;
	//图内容地址
	void *graph_data;
	//左图地址
	struct GraphStr *left_add;
	//上图地址
	struct GraphStr *up_add;
	//右图地址
	struct GraphStr *right_add;
	//下图地址
	struct GraphStr *down_add;

}graphstr;

//提取上一层节点的张量
struct TensorStr *get_graph_tensor(struct GraphStr *graph, uint8_t direct);
//前向传播图操作选择
bool graph_forward_switch(struct TensorStr *tensor, struct GraphStr *graph, uint8_t direct, uint16_t nums = 0);
//创建mlp图
GraphStr *graph_mlp_create(float op, bool (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat), uint16_t line, uint16_t row);
//创建tensorarch图
GraphStr *graph_tensorarch_create(uint16_t l_u_line, uint16_t l_u_row, uint16_t l_u_height, uint16_t r_d_line, uint16_t r_d_row, uint16_t r_d_height);
//打印图
bool graph_output(void *graph_add, uint8_t content);
//tensorarch图运算
bool graph_tensorarch_op(GraphStr *tensorarch_add, const uint8_t direct);
//图链初始化
GraphStr *graph_chain_init(GraphStr **graph_buf, uint16_t chain_len);
//获得当前图相邻的图
GraphStr *graph_next(GraphStr *in_grpah, uint8_t direct);
//反向传播图操作选择
bool graph_back_switch(struct GraphStr *l_graph, struct GraphStr *now_graph);
//针对开始节点的反向传播图操作选择的函数重载
bool graph_back_switch(struct TensorStr *tensor, struct GraphStr *now_graph, uint16_t nums = 0);
//更新图
bool graph_update(GraphStr *graph, float learmspeed);

#endif 
#pragma once


