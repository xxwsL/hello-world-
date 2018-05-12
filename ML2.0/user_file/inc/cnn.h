#ifndef _cnn_h_
#define _cnn_h_
#include "xxwsL.h"

//cnn_conv������ݺ�
#define _cnn_conv_kernel	0x01
#define _cnn_conv_kernel_gr 0x02
#define _cnn_conv_stride	0x04
#define _cnn_conv_op		0x08
#define _cnn_conv_out		0x10
#define _cnn_conv_fi		0x20 
#define _cnn_conv_all       0x3f

//cnn_pooling���ͺ�
#define _cnn_pooling_aver 0x01
#define _cnn_pooling_max  0x02

//cnn_pooling���ӡ���ݺ�
#define _cnn_pooling_mes  0x01
#define _cnn_pooling_out  0x02
#define _cnn_pooling_coor 0x04
#define _cnn_pooling_all  0x07

#define _get_cnn_conv(name) ((cnn_conv*)name)
#define _get_cnn_pool(name) ((cnn_pool*)name)

//�������
class cnn_conv {
public:
	//�������
	struct TensorStr *kernel;
	//�ݶ�
	struct TensorStr *kernel_gr;
	//����&���
	array<uint8_t, 4> stride;
	//ƫ��&ƫ���ݶ�
	array<float, 2> op;
	//�������
	struct TensorStr *out;
	//�����
	bool(*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
	//�󵼺���
	bool(*active_fid) (const struct MatrixStr *mat, struct MatrixStr *loadmat, const struct MatrixStr *target);
	//Ĭ�Ϲ��캯��
	cnn_conv();
	//��������
	~cnn_conv();
	//�û�����
	cnn_conv(array<uint16_t, 4>kernel_buf, array<uint16_t, 4>out_buf, array<uint8_t, 4>stride_buf, \
		     float op_value, bool(*fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat));
	//��ӡ����
	bool output(const uint8_t content = _cnn_conv_all);
	//�������
	bool conv_ot(const struct TensorStr *tensor);
	//cnn_conv����󼤻���㵼
	bool conv_fd(void);
	//�������ݶ�
	bool conv_gr(const struct TensorStr *tensor);
	//���ݵ���һ��conv
	bool error_pass_conv(struct TensorStr *tensor);
	//���ݵ���һ��pool
	bool error_pass_pool(struct TensorStr *tensor);
	//���¾����
	bool update(const float &learmspeed);
};

class cnn_pool {
public:
	//�������
	struct TensorStr *out;
	struct TensorStr *coor_x;
	struct TensorStr *coor_y;
public:
	//���캯��
	cnn_pool();
	//��������
	~cnn_pool();
	//�û����캯��
	cnn_pool(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type);
	//�ػ���������
	bool pooling_ot(const struct TensorStr *tensor);
	//��ӡ����
	bool output(const uint8_t content = _cnn_pooling_all);
	//���򴫲�
	bool error_pass(TensorStr *tensor, uint16_t deep = 0);
private:
	uint16_t line;
	uint16_t row;
	uint8_t ot_type;
};

#endif
