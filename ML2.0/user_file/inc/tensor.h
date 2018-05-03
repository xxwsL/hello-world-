#ifndef _tensor_h_
#define _tensor_h_
#include "xxwsL.h"

//����ĳһ��ľ���
#define get_tensor_mat(name,nums) ((struct TensorStr*)name)->mat[nums] 
//װ��������
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

//��������
TensorStr *tensor_create(const uint16_t line, const uint16_t row, const uint16_t height, uint16_t deep = 1);
//װ������
bool tensor_load(void *tensor_add, MatrixStr **vetor,const uint16_t vetor_len, const uint16_t deep = 1);
//����ת��ͼ����
bool tensorarch_op(TensorArch *tensorarch_add, TensorStr *in_tensor, const uint8_t direct,const uint16_t deep = 0);
//�����Ĵ�С
uint32_t tensor_element_size(TensorStr *tensor);
//��ӡ����
bool tensor_output(void *tensor_add, uint16_t deep = 0);
//����ת��ͼװ��
bool tensor_arch_load(TensorArch *load, TensorStr *l_tensor, TensorStr *r_tensor);
//��ӡ������Ϣ
bool tensor_message(TensorStr *tensor, uint16_t deep = 0);
//�ͷ������ڴ�
bool tensor_delete(TensorStr *tensor);
//��������ת�ƽṹ
TensorArch *tensorarch_create(array<uint16_t, 4>l_u_buf, array<uint16_t, 4>r_d_buf);
//�ͷ�����ת�ƽṹ�ڴ�
bool tensorarch_delete(TensorArch *tenasorarch);
//��ӡtensorarchͼ
bool tensorarch_output(TensorArch *tensorarch, uint8_t direct, uint16_t deep = 0);
//������ֵ
bool tensor_assignment(TensorStr *tensor, float value = 0.0f);
//��������
bool tensor_copy(const TensorStr *tensor, TensorStr *loadtensor);
//��������ֵ
bool tensor_up_assign(TensorStr *tensor, const float value);
//����������������
uint32_t tensor_mat_size(const TensorStr *tensor);



#endif 











