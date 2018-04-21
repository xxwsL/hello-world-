#include "tensor.h"

//�Ż�����:1
//��������
//line:�г�
//row:�г�
//height:������ά��
//return:TensorStrָ����־λ
TensorStr *tensor_create(const uint16_t line, const uint16_t row, const uint16_t height)
{
	uint16_t i = NULL;
	TensorStr *tensor = NULL;
	//�����߲���Ϊ0
	if (height!=NULL) {
		//�����ڴ�ɹ�
		if (tensor = (TensorStr*)malloc(sizeof(TensorStr))) {
			//��ʼ�������ĸ�
			tensor->height = height;
			//��ʼ����������
			if (tensor->mat = mat_vetor_create(height)) {
				//����к��ж���Ϊ0
				if (line != NULL&&row != NULL) {
					for (i = NULL; i < height; ++i) {
						tensor->mat[i] = mat_create(line, row, f32Flag);
					}
				}
				return tensor;
			}
			else {
				free(tensor);
			}
		}
	}
	return false;
}

//�Ż�����:0
//����װ��
//tensor:��װ������
//vettor:��������
//vetor_len:��������
//return:����int��־λ
int tensor_load(void *tensor_add, MatrixStr **vetor,const uint16_t vetor_len) 
{
	TensorStr *tensor = NULL;
	tensor = (TensorStr*)tensor_add;
	tensor->height = vetor_len;
	tensor->mat = vetor;
	return true;
}

//�Ż�����:0
//����ת��ͼ����
//load_tensor:װ������
//in_tensor:��������
//direct:ת�Ʒ���
//return:����int��־λ
int tensorarch_op(void *tensorarch_add,TensorStr *in_tensor,const uint8_t direct)
{
	uint8_t *buf = NULL, *flag_add0 = NULL;
	uint32_t i = NULL;
	uint32_t temp_size = NULL,in_tensor_size=NULL;
	TensorStr *tensor_p = NULL;
	TensorArch *tensorarch=NULL;
	tensorarch = (TensorArch*)tensorarch_add;
	//�����������о�
	switch (direct){
		//ת��������
		case _direct_left:
			tensor_p = tensorarch->r_d_tensor;
			break;
		//ת��������
		case _direct_up:
			tensor_p = tensorarch->r_d_tensor;
			break;
		//ת��������
		case _direct_right:
			tensor_p = tensorarch->l_u_tensor;
			break;
		//ת��������
		case _direct_down:
			tensor_p = tensorarch->l_u_tensor;
			break;
		default:
			return false;break;
	}
	//���װ�����������������ĳߴ�
	temp_size = tensor_size(tensor_p); 
	in_tensor_size = tensor_size(in_tensor);
	//�ж��Ƿ����װ������
	if (temp_size > in_tensor_size) {
		return false;
	}
	//��������buf
	buf = (uint8_t*)malloc(in_tensor_size*4);
	flag_add0 = buf;
	//����������������ݿ���������buf��
	for (i = NULL; i < in_tensor->height;++i) {
		temp_size = mat_size(in_tensor->mat[i]) * 4;
		memcpy(flag_add0,in_tensor->mat[i]->SaveAddr,temp_size);
		flag_add0 += temp_size;
	}
	//�ѻ���buf�����ݿ�����װ��������
	flag_add0 = buf; 
	for (i = NULL; i < tensor_p->height; ++i) {
		temp_size = mat_size(tensor_p->mat[i]) * 4; 
		memcpy(tensor_p->mat[i]->SaveAddr, flag_add0, temp_size);
		flag_add0 += temp_size;
	}
	//�������,�ͷŻ����ڴ�
	free(buf);
	return true;
}

//�Ż�����:0
//��������ߴ�
//tensor:��������
//return:���������ߴ�
uint32_t tensor_size(TensorStr *tensor)
{
	uint16_t i = NULL;
	uint32_t size = NULL;
	for (; i < tensor->height; ++i){
		size += mat_size(tensor->mat[i]);
	}
	return size;
}

//�Ż�����:0
//��ӡ����
//tensor:��������
//return:int��־λ
int tensor_output(void *tensor_add)
{
	TensorStr *tensor = NULL;
	tensor = (TensorStr*)tensor_add;
	uint16_t i = NULL,height=NULL;
	height = tensor->height;
	for (i = NULL; i < height; ++i) {
		printf("layer : %d\n", i);
		output(tensor->mat[i]);
	}
	return true;
}

//�Ż�����:0
//����ת��ͼװ��
//load:����ת��ͼ
//l_tensor;������
//r_tensor:������
int tensor_arch_load(TensorArch *load,TensorStr *l_tensor,TensorStr *r_tensor)
{
	load->l_u_tensor = l_tensor;
	load->r_d_tensor = r_tensor;
	return true;
}

//�Ż�����:0
//��ӡ������Ϣ
//tensor:��������
//return:boo��־
int tensor_message(TensorStr *tensor)
{
	uint16_t i = NULL;
	if (tensor == 0) {
		return false;
	}
	//��ӡ�����߶���Ϣ
	cout << "�����߶� = "<<tensor->height<<endl<<endl;
	for (i = NULL; i < tensor->height; ++i) {
		cout << "mat_" << i << endl;
		mat_message(tensor->mat[i]);
	}
	return true;
}

//�Ż�����:0
//�ͷ������ڴ�
//tensor:��������
//return:int��־
int tensor_delete(TensorStr *tensor)
{
	uint16_t i = NULL;
	if (tensor == 0){
		return false;
	}
	for (i = NULL; i < tensor->height; ++i) {
		mat_delete(tensor->mat[i]);
	}
	free(tensor);
	tensor = NULL;
	return true;
}

//�Ż�����:0
//l_u_line:�������г�
//l_u_row:�������г�
//l_u_height:��������
//r_d_lin:�������г�
//r_d_row:�������г�
//r_d_height:��������
//return:TensorArchָ��
//��������ת�ƽṹ
TensorArch *tensorarch_create(uint16_t l_u_line, uint16_t l_u_row, uint16_t l_u_height, uint16_t r_d_line, uint16_t r_d_row, uint16_t r_d_height)
{
	TensorArch *tensorarch = NULL;
	if (tensorarch = (TensorArch*)malloc(sizeof(TensorArch))) {

		if ((tensorarch->l_u_tensor = tensor_create(l_u_line, l_u_row, l_u_height)) && (tensorarch->r_d_tensor = tensor_create(r_d_line, r_d_row, r_d_height))) {
			return tensorarch;
		}
		else {
			tensor_delete(tensorarch->l_u_tensor);
			tensor_delete(tensorarch->r_d_tensor);
			free(tensorarch);
		}
	}
	return false;
}

//tensorarch:����ת�ƽṹ
//return:int��־
//�ͷ�����ת�ƽṹ�ڴ�
int tensorarch_delete(TensorArch *tenasorarch)
{
	tensor_delete(tenasorarch->l_u_tensor);
	tensor_delete(tenasorarch->r_d_tensor);
	free(tenasorarch);
	return true;
}

//�Ż�:0
//tensorarch_add:tensorarch��ַ
//direct:ָ��
//��ӡtensorarchͼ
int tensorarch_output(void *tensoarch_add,uint8_t direct)
{
	TensorArch *tensorarch = (TensorArch*)tensoarch_add;
	if (direct&_direct_left) {
		cout << "l_tensor = " << endl;
		tensor_output(tensorarch->l_u_tensor);
	}
	if (direct&_direct_up) {
		cout << "u_tensor = " << endl;
		tensor_output(tensorarch->l_u_tensor);
	}
	if (direct&_direct_right) {
		cout << "r_tensor = " << endl;
		tensor_output(tensorarch->r_d_tensor);
	}
	if (direct&_direct_down) {
		cout << "d_tensor = " << endl;
		tensor_output(tensorarch->r_d_tensor);
	}
	return true;
}

//�Ż�:0
//tensor:��������
//value:��Ч������ֵ
//������ֵ
int tensor_assignment(TensorStr *tensor,float value) 
{
	uint16_t i = NULL;
	for (; i < tensor->height;++i) {
		mat_assignment(tensor->mat[i],value);
	}
	return true;
}