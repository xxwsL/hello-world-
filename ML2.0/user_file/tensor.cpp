#include "tensor.h"

//�Ż�����:1
//��������
//line:�г�
//row:�г�
//height:������ά��
//return:TensorStrָ����־λ
TensorStr *tensor_create(const uint16_t line, const uint16_t row, const uint16_t height, uint16_t deep)
{
	uint32_t i = NULL, nums_0 = height * deep;
	TensorStr *tensor = new TensorStr;
	//�����߲���Ϊ0
	if (height!=NULL) {
		//�����ڴ�ɹ�
		if (tensor) {
			//��ʼ�������ĸ�
			tensor->height = height;
			tensor->deep = deep;
			//��ʼ����������
			if (tensor->mat = mat_vetor_create(height)) {
				//����к��ж���Ϊ0
				if (line != NULL&&row != NULL) {
					for (i = NULL; i < nums_0; ++i) {
						tensor->mat[i] = mat_create(line, row, f32Flag);
					}
				}
				return tensor;
			}
			else {
				delete tensor;
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
//return:����bool��־λ
bool tensor_load(void *tensor_add, MatrixStr **vetor,const uint16_t vetor_len, const uint16_t deep)
{
	TensorStr *tensor = NULL;
	tensor = (TensorStr*)tensor_add;
	tensor->height = vetor_len;
	tensor->deep = deep;
	tensor->mat = vetor;
	return true;
}

//�Ż�����:0
//����ת��ͼ����
//load_tensor:װ������
//in_tensor:��������
//direct:ת�Ʒ���
//return:����bool��־λ
bool tensorarch_op(TensorArch *tensorarch,TensorStr *in_tensor,const uint8_t direct,const uint16_t deep)
{
	uint8_t *buf = NULL, *flag_add0 = NULL;
	uint32_t i = NULL;
	uint32_t temp_size = NULL,u32num0=NULL;
	TensorStr *tensor_p = NULL;
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
	temp_size = tensor_element_size(tensor_p); 
	u32num0 = tensor_element_size(in_tensor);
	//�ж��Ƿ����װ������
	if (temp_size != u32num0) {
		return false;
	}
	//��������buf
	buf = new uint8_t[u32num0 * 4];
	flag_add0 = buf;
	u32num0 = in_tensor->deep * in_tensor->height;
	//����������������ݿ���������buf��
	for (i = NULL; i < u32num0;++i) {
		temp_size = mat_size(in_tensor->mat[i]) * 4;
		//��׼���ڴ濽������
		memcpy(flag_add0,in_tensor->mat[i]->SaveAddr,temp_size);
		flag_add0 += temp_size;
	}
	//�ѻ���buf�����ݿ�����װ��������
	flag_add0 = buf; 
	u32num0 = tensor_p->deep * tensor_p->height;
	for (i = NULL; i < u32num0; ++i) {
		temp_size = mat_size(tensor_p->mat[i]) * 4; 
		memcpy(tensor_p->mat[i]->SaveAddr, flag_add0, temp_size);
		flag_add0 += temp_size;
	}
	//�������,�ͷŻ����ڴ�
	delete[]buf;
	return true;
}

//�Ż�����:0
//��������ߴ�
//tensor:��������
//return:���������ߴ�
uint32_t tensor_element_size(TensorStr *tensor)
{
	uint16_t i = NULL;
	uint32_t size = NULL;
	uint32_t nums_0 = tensor->deep*tensor->height;
	for (; i < nums_0; ++i){
		size += mat_size(tensor->mat[i]);
	}
	return size;
}

//�Ż�����:0
//��ӡ����
//tensor:��������
//return:bool��־λ
bool tensor_output(void *tensor_add, uint16_t deep)
{
	TensorStr *tensor = NULL;
	tensor = (TensorStr*)tensor_add;
	uint16_t i = NULL, height = tensor->height;
	uint32_t offset = tensor->deep * deep;

		for (i = NULL; i < height; ++i) {
			printf("layer : %d\n", i);
			output(tensor->mat[i+offset]);
		}
	return true;
}

//�Ż�����:0
//����ת��ͼװ��
//load:����ת��ͼ
//l_tensor;������
//r_tensor:������
bool tensor_arch_load(TensorArch *load,TensorStr *l_tensor,TensorStr *r_tensor)
{
	load->l_u_tensor = l_tensor;
	load->r_d_tensor = r_tensor;
	return true;
}

//�Ż�����:0
//��ӡ������Ϣ
//tensor:��������
//return:boo��־
bool tensor_message(TensorStr *tensor, uint16_t deep)
{
	uint16_t i = NULL;
	uint32_t offset = tensor->deep * deep;
	if (tensor == 0) {
		return false;
	}
	//��ӡ�����߶���Ϣ
	cout << "�����߶� = "<<tensor->height<<endl<<endl;
	for (i = NULL; i < tensor->height; ++i) {
		cout << "mat_" << i << endl;
		mat_message(tensor->mat[i+offset]);
	}
	return true;
}

//�Ż�����:0
//�ͷ������ڴ�
//tensor:��������
//return:bool��־
bool tensor_delete(TensorStr *tensor)
{
	uint32_t i = NULL;
	uint32_t nums_0 = tensor_element_size(tensor);
	if (tensor == 0){
		return false;
	}
	for (i = NULL; i < nums_0; ++i) {
		mat_delete(tensor->mat[i]);
	}
	delete tensor;
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
TensorArch *tensorarch_create(array<uint16_t,4>l_u_buf, array<uint16_t, 4>r_d_buf)
{
	TensorArch *tensorarch = new TensorArch;

	if (tensorarch) {

		if ((tensorarch->l_u_tensor = tensor_create(l_u_buf[0], l_u_buf[1], l_u_buf[2], l_u_buf[3])) &&
			(tensorarch->r_d_tensor = tensor_create(r_d_buf[0], r_d_buf[1], r_d_buf[2], r_d_buf[3]))) {
			return tensorarch;
		}
		else {
			tensor_delete(tensorarch->l_u_tensor);
			tensor_delete(tensorarch->r_d_tensor);
			delete tensorarch;
		}
	}
	return false;
}

//tensorarch:����ת�ƽṹ
//return:bool��־
//�ͷ�����ת�ƽṹ�ڴ�
bool tensorarch_delete(TensorArch *tenasorarch)
{
	tensor_delete(tenasorarch->l_u_tensor);
	tensor_delete(tenasorarch->r_d_tensor);
	delete tenasorarch;
	return true;
}

//�Ż�:0
//tensorarch_add:tensorarch��ַ
//direct:ָ��
//��ӡtensorarchͼ
bool tensorarch_output(TensorArch *tensorarch,uint8_t direct, uint16_t deep)
{
	if ((direct&_direct_left) || (direct&_direct_up)) {
		cout << "l_u_tensor = " << endl;
		tensor_output(tensorarch->l_u_tensor, deep);
	}

	if ((direct&_direct_right) || (direct&_direct_down)) {
		cout << "r_d_tensor = " << endl;
		tensor_output(tensorarch->r_d_tensor, deep);
	}
	return true;
}

//�Ż�:0
//tensor:��������
//value:��Ч������ֵ
//������ֵ
bool tensor_assignment(TensorStr *tensor, float value)
{
	uint32_t i = NULL, nums_0 = tensor->height * tensor->deep;
	for (; i < nums_0;++i) {
		mat_assignment(tensor->mat[i],value);
	}
	return true;
}

//��������
bool tensor_copy(const TensorStr *tensor, TensorStr *loadtensor)
{
	uint32_t num0 = tensor->height*tensor->deep;
	uint32_t i = NULL;
	for (i = 0; i < num0; ++i) {
		mat_copy(tensor->mat[i], loadtensor->mat[i], mat_size(tensor->mat[i]));
	}
	return true;
}

//��������ֵ
bool tensor_up_assign(TensorStr *tensor, const float value)
{
	uint32_t i = 0, u32num0 = tensor->deep*tensor->height;
	for (; i < u32num0; ++i) {
		mat_up_assign(tensor->mat[i], value);
	}
	return true;
}

//����������������
uint32_t tensor_mat_size(const TensorStr *tensor)
{
	return uint32_t(tensor->deep*tensor->height);
}