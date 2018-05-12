#ifndef _tensor_h_
#define _tensor_h_
#include "xxwsL.h"

#define _get_tensor(name) ((struct TensorStr*)name)
#define _get_arch(name)   ((struct TensorArch*)name)

//装载张量宏
#define load_tensor(tensor_name,vetor_name) tensor_load(tensor_name,vetor_name,sizeof(vetor_name)/sizeof(struct MatrixStr*))

typedef struct TensorStr {
	uint16_t height;
	uint16_t deep;
	struct MatrixStr **mat;
}tensorstr;

typedef struct TensorArch {
	struct TensorStr *l_u_tensor;
	struct TensorStr *r_d_tensor;
}t_arch;

//创建张量
TensorStr *tensor_create(const uint16_t line, const uint16_t row, const uint16_t height, uint16_t deep = 1);
//装载张量
bool tensor_load(void *tensor_add, MatrixStr **vetor,const uint16_t vetor_len, const uint16_t deep = 1);
//张量转移图运算
bool tensorarch_op(TensorArch *tensorarch_add, const TensorStr *in_tensor, const uint8_t direct);
//张量的大小
uint32_t tensor_element_size(const TensorStr *tensor);
//打印张量
bool tensor_output(const TensorStr  *tensor, uint16_t deep);
bool tensor_output(const TensorStr *tensor);
//张量转移图装载
bool tensor_arch_load(TensorArch *load, TensorStr *l_tensor, TensorStr *r_tensor);
//打印张量信息
bool tensor_message(TensorStr *tensor, uint16_t deep = 0);
//释放张量内存(更安全版本)
bool tensor_delete(TensorStr* &tensor);
//创建张量转移结构
TensorArch *tensorarch_create(array<uint16_t, 4>l_u_buf, array<uint16_t, 4>r_d_buf);
//释放张量转移结构内存
bool tensorarch_delete(TensorArch* &tenasorarch);
//打印tensorarch图
bool tensorarch_output(const TensorArch *tensorarch);
//张量赋值
bool tensor_assign(TensorStr* &tensor, const float value = 0.0f);
//张量拷贝
bool tensor_copy(const TensorStr *tensor, TensorStr *loadtensor);
//张量升序赋值
bool tensor_up_assign(TensorStr* &tensor, const float value = 0.0f);
//返回张量矩阵数量
uint32_t tensor_mat_size(const TensorStr *tensor);
//张量点乘
bool tensor_dotmult(TensorStr *& l_tensor, TensorStr *& r_tensor, TensorStr* loadtensor);
//张量矩阵元素似正态随机赋值
bool tensor_rand_normal_mat(TensorStr* &tensor);


#endif 











