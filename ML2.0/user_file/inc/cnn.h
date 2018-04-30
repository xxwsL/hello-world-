#ifndef _cnn_h_
#define _cnn_h_
#include "xxwsL.h"

//cnn_conv输出内容宏
#define _cnn_conv_kernel	0x01
#define _cnn_conv_kernel_gr 0x02
#define _cnn_conv_stride	0x04
#define _cnn_conv_op		0x08
#define _cnn_conv_out		0x10
#define _cnn_conv_fi		0x20 
#define _cnn_conv_all       0x3f

//cnn_pooling类型宏
#define _cnn_pooling_aver 0x01
#define _cnn_pooling_max  0x02

//cnn_pooling类打印内容宏
#define _cnn_pooling_mes  0x01
#define _cnn_pooling_out  0x02
#define _cnn_pooling_coor 0x04
#define _cnn_pooling_all  0x07

//卷积层类
class cnn_conv {
public:
	//卷积张量
	struct TensorStr *kernel;
	//梯度
	struct TensorStr *kernel_gr;
	//步伐&填充
	array<uint8_t, 4> stride;
	//偏置&偏置梯度
	array<float, 2> op;
	//输出张量
	struct TensorStr *out;
	//激活函数
	bool(*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
	//求导函数
	bool(*active_fid) (const struct MatrixStr *mat, struct MatrixStr *loadmat, const struct MatrixStr *target);
	//默认构造函数
	cnn_conv();
	//析构函数
	~cnn_conv();
	//用户构造
	cnn_conv(array<uint16_t, 4>kernel_buf, array<uint16_t, 4>out_buf, array<uint8_t, 4>stride_buf, \
		     float op_value, bool(*fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat));
	//打印函数
	bool output(const uint8_t content = _cnn_conv_all);
	//卷积操作
	bool conv_ot(const struct TensorStr *tensor, uint16_t deep = 0);
};

class cnn_pooling {
public:
	//输出张量
	struct TensorStr *out;
	struct TensorStr *coor_x;
	struct TensorStr *coor_y;
public:
	//构造函数
	cnn_pooling();
	//析构函数
	~cnn_pooling();
	//用户构造函数
	cnn_pooling(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type);
	//池化操作函数
	bool pooling_ot(const struct TensorStr *tensor, const uint16_t deep = 0);
	//打印函数
	bool output(const uint8_t content, const uint16_t deep = 0);
private:
	uint16_t line;
	uint16_t row;
	uint8_t ot_type;
};

#endif
