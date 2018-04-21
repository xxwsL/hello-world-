#ifndef _tensor_h_
#define _tensor_h_
#include "xxwsL.h"

//张量某一层的矩阵
#define get_tensor_mat(name,nums) ((struct TensorStr*)name)->mat[nums] 
//装载张量宏
#define load_tensor(tensor_name,vetor_name) tensor_load(tensor_name,vetor_name,sizeof(vetor_name)/sizeof(struct MatrixStr*))

typedef struct TensorStr {
	uint16_t height;
	struct MatrixStr **mat;
}tensorstr;

typedef struct TensorArch {
	struct TensorStr *l_u_tensor;
	struct TensorStr *r_d_tensor;
}t_arch;

//创建张量
TensorStr *tensor_create(const uint16_t line, const uint16_t row, const uint16_t height);
//装载张量
int tensor_load(void *tensor_add, MatrixStr **vetor,const uint16_t vetor_len);
//张量转移图运算
int tensorarch_op(void *tensorarch_add, TensorStr *in_tensor, const uint8_t direct);
//张量的大小
uint32_t tensor_size(TensorStr *tensor);
//打印张量
int tensor_output(void *tensor_add);
//张量转移图装载
int tensor_arch_load(TensorArch *load, TensorStr *l_tensor, TensorStr *r_tensor);
//打印张量信息
int tensor_message(TensorStr *tensor);
//释放张量内存
int tensor_delete(TensorStr *tensor);
//创建张量转移结构
TensorArch *tensorarch_create(uint16_t l_u_line, uint16_t l_u_row, uint16_t l_u_height, uint16_t r_d_line, uint16_t r_d_row, uint16_t r_d_height);
//释放张量转移结构内存
int tensorarch_delete(TensorArch *tenasorarch);
//打印tensorarch图
int tensorarch_output(void *tensoarch_add, uint8_t direct);
//张量赋值
int tensor_assignment(TensorStr *tensor, float value);



#endif 











