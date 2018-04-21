#ifndef _mlp_h_
#define _mlp_h_
#include "xxwsL.h"

//创建mlp宏
#define new_mlp(name,op,fi,line,row) struct MlpStr *name=mlp_create(op,fi,line,row) 

//mlp的内容宏
#define _mlp_layer  0x01
#define _mlp_outmat 0x02
#define _mlp_gr_mat 0x04
#define _mlp_tensor 0x07
#define _mlp_op	   0x08	
#define _mlp_fi	   0x10 	
#define _mlp_fid    0x20
#define _mlp_fi_all   0x30
#define _mlp_all    0x3f

//mlp类
typedef struct MlpStr {
	//连接层
	struct TensorStr *layer;
	//输出层
	struct TensorStr *outmat;
	//梯度层
	struct TensorStr *gr_mat;
	//偏置
	float op;
	//偏置提督
	float op_gr;
	//激活函数
	int (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
	//求导函数
	int (*active_fid) (const struct MatrixStr *mat, struct MatrixStr *loadmat, const struct MatrixStr *target);
}mlpstr;

//mlp节点初始化
int mlp_init(mlpstr *mlp, float op, int (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat), struct TensorStr *layer);
//单节点mlp前向过程
int mlp_one_op(void *mlp_add, struct TensorStr *inmat);
//创建mlp数据域
MlpStr *mlp_create(float op, int (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat), uint16_t line, uint16_t row);
//打印mlp
int mlp_output(void *mlp_add, uint8_t content);
//各个连接层梯度
int mlp_gr(struct TensorStr *tensor, MlpStr *r_mlp);
//输出误差传递
int mlp_error_pass(MlpStr *l_mlp, MlpStr* r_mlp);
//更新mlp网络权重
int mlp_update(MlpStr *mlp, float learmspeed);

#endif 

