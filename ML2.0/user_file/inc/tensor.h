#ifndef _tensor_h_
#define _tensor_h_
#include "xxwsL.h"

//����ĳһ��ľ���
#define get_tensor_mat(name,nums) ((struct TensorStr*)name)->mat[nums] 
//װ��������
#define load_tensor(tensor_name,vetor_name) tensor_load(tensor_name,vetor_name,sizeof(vetor_name)/sizeof(struct MatrixStr*))

typedef struct TensorStr {
	uint16_t height;
	struct MatrixStr **mat;
}tensorstr;

typedef struct TensorArch {
	struct TensorStr *l_u_tensor;
	struct TensorStr *r_d_tensor;
}t_arch;

//��������
TensorStr *tensor_create(const uint16_t line, const uint16_t row, const uint16_t height);
//װ������
bool tensor_load(void *tensor_add, MatrixStr **vetor,const uint16_t vetor_len);
//����ת��ͼ����
bool tensorarch_op(void *tensorarch_add, TensorStr *in_tensor, const uint8_t direct);
//�����Ĵ�С
uint32_t tensor_size(TensorStr *tensor);
//��ӡ����
bool tensor_output(void *tensor_add);
//����ת��ͼװ��
bool tensor_arch_load(TensorArch *load, TensorStr *l_tensor, TensorStr *r_tensor);
//��ӡ������Ϣ
bool tensor_message(TensorStr *tensor);
//�ͷ������ڴ�
bool tensor_delete(TensorStr *tensor);
//��������ת�ƽṹ
TensorArch *tensorarch_create(uint16_t l_u_line, uint16_t l_u_row, uint16_t l_u_height, uint16_t r_d_line, uint16_t r_d_row, uint16_t r_d_height);
//�ͷ�����ת�ƽṹ�ڴ�
bool tensorarch_delete(TensorArch *tenasorarch);
//��ӡtensorarchͼ
bool tensorarch_output(void *tensoarch_add, uint8_t direct);
//������ֵ
bool tensor_assignment(TensorStr *tensor, float value);



#endif 











