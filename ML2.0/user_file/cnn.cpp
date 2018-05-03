#include "inc\cnn.h"

//cnn_convĬ�Ϲ��캯��
cnn_conv::cnn_conv() {
}

//cnn_conv��������
cnn_conv::~cnn_conv()
{
	tensor_delete(kernel);
	tensor_delete(out);
}

//kernel_buf:�������Ϣbuf
//out:���������Ϣbuf
//stride:����&����־buf
//op_value:ƫ��
//fi:�����
//cnn_conv�û����캯��
cnn_conv::cnn_conv(array<uint16_t,4>kernel_buf, array<uint16_t,4>out_buf, array<uint8_t,4>stride_buf, float op_value, active_fi_str(fi))
{
	//�����&�ݶ�������ʼ��
	kernel = tensor_create(kernel_buf[0], kernel_buf[1], kernel_buf[2], kernel_buf[3]);
	kernel_gr = tensor_create(kernel_buf[0], kernel_buf[1], kernel_buf[2], kernel_buf[3]);
	//������ʼ��
	out = tensor_create(out_buf[0], out_buf[1], out_buf[2], out_buf[3]);
	//����&����־buf��ʼ��
	stride = stride_buf;
	//ƫ�ó�ʼ��
	op[0] = op_value;
	//�������ʼ��
	active_fi = fi;
	//������󵼺���װ��
	if ((void*)active_fi == (void*)mat_signmoid_par)
		//signmoid
		active_fid = _signmoid_fd;
	else if ((void*)active_fi == (void*)mat_tanh_par)
		//tanh
		active_fid = _tanh_fd;
	else if ((void*)active_fi == (void*)mat_relu_par)
		//relu
		active_fid = _relu_fd;
	else if ((void*)active_fi == (void*)mat_softmax_par)
		//softmax
		active_fid = _softmax_fd;
	else
		active_fid = NULL;
}

//content:�������
//�������
bool cnn_conv::output(const uint8_t content)
{
	uint16_t i = NULL;
	//������������
	if (content&_cnn_conv_kernel) {
		cout << "��������� :\n";
		for (i = 0; i < kernel->deep; ++i) {
			//�������������
			tensor_output(kernel, i);
			cout << "\n";
		}
	}
	//�����ǰ������ݶ�����
	if (content&_cnn_conv_kernel_gr) {
		cout << "������ݶ����� :\n";
		for (i = 0; i < kernel_gr->deep;++i) {
			tensor_output(kernel_gr, i);
			cout << "\n";
		}
	}
	//��������������Ϣ
	if (content&_cnn_conv_stride) {
		cout << "�в��� = " << (uint16_t)stride[0] << "\n�в��� = " << (uint16_t)stride[1] << "\n�߲��� = " << (uint16_t)stride[2];
		if (stride[3]) {
			cout << "\n����������\n\n";
		}
		else {
			cout << "\n������������\n\n";
		}
	}
	//���ƫ����Ϣ
	if (content&_cnn_conv_op) {
		cout << "op = " << op[0] << "\nop_gr = " << op[1] << "\n\n";
	}
	//�������������
	if (content&_cnn_conv_out) {
		cout << "���������� :\n";
		for (i = 0; i < out->deep; ++i) {
			tensor_output(out, i);
			cout << "\n";
		}
	}
	//����������Ϣ
	if (content&_cnn_conv_fi){
		if ((void*)active_fi == (void*)mat_signmoid_par)
			//signmoid
			cout<<"����� = signmoid\n";
		else if ((void*)active_fi == (void*)mat_tanh_par)
			//tanh
			cout << "����� = tanh\n";
		else if ((void*)active_fi == (void*)mat_relu_par)
			//relu
			cout << "����� = relu\n";
		else if ((void*)active_fi == (void*)mat_softmax_par)
			//softmax
			cout << "����� = softmax\n";
		else
			cout << "����� = NULL";
		cout << "\n";
	}
	return true;
}

//tensor:����
//deep:���
//cnn_conv�������
bool cnn_conv::conv_ot(const struct TensorStr *tensor, uint16_t deep) {
	uint16_t i = NULL, j = NULL;
	uint16_t num0 = tensor->height, num1 = kernel->height;
	uint16_t offset0 = deep*tensor->height, offset1 = deep*out->height, offset2 = 0;
	//������ֻ�����
	for (j = 0; j < num1; ++j) {
		//���������ֻ�����
		for (i = 0; i < num0; ++i) {
			//���ǰ�����������0
			mat_zero(out->mat[offset2 + offset1 + i]);
			//������
				(tensor->mat[offset0 + i], kernel->mat[j], out->mat[offset2 + offset1 + i], stride[0], stride[1], stride[3]);
			//����������ƫ��
			if (op[0]) {
				mat_addto_value(out->mat[offset2 + offset1 + i],op[0]);
			}
			//ʹ�ü��������
			active_fi(out->mat[offset2 + offset1 + i], out->mat[offset2 + offset1 + i]);
		}
		offset2 += num0;
	}
	return true;
}

//conv������󼤻���㵼
bool cnn_conv::conv_fd(void)
{
	uint16_t i = NULL, num0 = out->height;
	for (i = 0; i < num0; ++i) {
		active_fid(out->mat[i], out->mat[i], NULL);
	}
	return true;
}

bool cnn_conv::conv_gr(const TensorStr *tensor)
{
	uint16_t i = 0, j = 0;
	uint16_t u16_offset0 = 0;
	//�����������
	for (i = 0; i < out->height; ) {
		//������������
		for (j = 0; j < tensor->height; ++j) {
			mat_conv_gr(out->mat[i],tensor->mat[j],kernel_gr->mat[u16_offset0],stride[0],stride[1]);
			++i;
		}
		//���¾���ݶ���������ƫ��
		u16_offset0++;
	}
	return true;
}




//cnn_poolingĬ�Ϲ��캯��
cnn_pooling::cnn_pooling(){}

//cnn_pooling��������
cnn_pooling::~cnn_pooling()
{
	if (ot_type) {
		tensor_delete(coor_x);
	}
}

//line_v:�ػ��г�
//row_v:�ػ��г�
//out_v:���������Ϣ
//type:�ػ�����
//cnn_pooling�û����캯��
cnn_pooling::cnn_pooling(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type)
{
	//��ʼ���ػ�����ߴ�
	line = line_v;
	row = row_v;
	//�����������
	out = tensor_create(out_v[0], out_v[1], out_v[2], out_v[3]);
	//�ػ�����(��ֵ�ػ�or���ֵ�ػ�)
	ot_type = type;
	switch(type){
	case _cnn_pooling_aver:
		break;
	case _cnn_pooling_max:
		coor_x = tensor_create(out_v[0], out_v[1], out_v[2], out_v[3]);
		coor_y = tensor_create(out_v[0], out_v[1], out_v[2], out_v[3]);
		break;
	default:break;
	}

}

//tensor:��������
//deep:���
//�ػ�����
bool cnn_pooling::pooling_ot(const struct TensorStr *tensor, const uint16_t deep)
{
	uint16_t i = NULL;
	uint16_t num0 = out->height;
	uint32_t offset0 = deep*tensor->height;
	switch (ot_type) {
		//��ֵ�ػ�
	case _cnn_pooling_aver:
		for (i = 0; i < num0;++i) {
			mat_pooling(tensor->mat[i], line, row, out->mat[i]);
		}
		break;
		//���ֵ�ػ�
	case _cnn_pooling_max:
		break;
	default:return false; break;
	}
	return true;
}

//content:����
//deep:���
//��ӡcnn_pooling
bool cnn_pooling::output(const uint8_t content, const uint16_t deep)
{
	//��ӡ��Ϣ
	if (content&_cnn_pooling_mes){
		cout << "cnn_pooling_message :\n";
		//��ӡ�ػ�����
		switch (ot_type) {
		case _cnn_pooling_aver:cout << "type = aver_pooling\n"; break;
		case _cnn_pooling_max:cout << "type = max_poolinf\n"; break;
		default:cout << "type is error\n"; break;
		}
		//��ӡ�ػ��ߴ�
		cout << "pooling_line = " << line << "	pooling_row = " << row << "\n\n";
	}
	//��ӡ�ػ����
	if (content&_cnn_pooling_out) {
		tensor_output(out, deep);
	}
	//��ӡ���ֵ�ػ����¼��ԭ�������ֵ����
	if (content&_cnn_pooling_coor) {
		if (!coor_x) {
			cout << "NO coor\n";
			return false;
		}
		cout << "coor_x :\n";
		tensor_output(coor_x, deep);
		cout << "coor_y :\n";
		tensor_output(coor_y, deep);
	}
	return true;
}

//cnn�ػ������򴫲�
bool cnn_pooling::error_pass(TensorStr *tensor, uint16_t deep)
{
	uint16_t i = NULL, num0 = tensor->height;
	switch (ot_type){
		//��ֵ�ػ�ģʽ
	case _cnn_pooling_aver:
		for (i = 0; i < num0; ++i) {
			mat_pooling_redu(out->mat[i], line, row, tensor->mat[i]);
		}
		break;
		//���ֵ�ػ�ģʽ
	case _cnn_pooling_max:
		break;
	default:
		return false;
		break;
	}
	return true;
}