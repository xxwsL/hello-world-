#include "inc\cnn.h"

//cnn_conv默认构造函数
cnn_conv::cnn_conv() {
}

//cnn_conv析构函数
cnn_conv::~cnn_conv()
{
	tensor_delete(kernel);
	tensor_delete(out);
}

//kernel_buf:卷积核信息buf
//out:输出张量信息buf
//stride:步伐&填充标志buf
//op_value:偏置
//fi:激活函数
//cnn_conv用户构造函数
cnn_conv::cnn_conv(array<uint16_t,4>kernel_buf, array<uint16_t,4>out_buf, array<uint8_t,4>stride_buf, float op_value, active_fi_str(fi))
{
	//卷积核&梯度张量初始化
	kernel = tensor_create(kernel_buf[0], kernel_buf[1], kernel_buf[2], kernel_buf[3]);
	kernel_gr = tensor_create(kernel_buf[0], kernel_buf[1], kernel_buf[2], kernel_buf[3]);
	//输出层初始化
	out = tensor_create(out_buf[0], out_buf[1], out_buf[2], out_buf[3]);
	//步长&填充标志buf初始化
	stride = stride_buf;
	//偏置初始化
	op[0] = op_value;
	//激活函数初始化
	active_fi = fi;
	//激活函数求导函数装载
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

//content:输出内容
//输出函数
bool cnn_conv::output(const uint8_t content)
{
	uint16_t i = NULL;
	//输出卷积核张量
	if (content&_cnn_conv_kernel) {
		cout << "卷积核张量 :\n";
		for (i = 0; i < kernel->deep; ++i) {
			//按张量深度排序
			tensor_output(kernel, i);
			cout << "\n";
		}
	}
	//输出当前卷积核梯度张量
	if (content&_cnn_conv_kernel_gr) {
		cout << "卷积核梯度张量 :\n";
		for (i = 0; i < kernel_gr->deep;++i) {
			tensor_output(kernel_gr, i);
			cout << "\n";
		}
	}
	//输出步伐和填充信息
	if (content&_cnn_conv_stride) {
		cout << "行步伐 = " << (uint16_t)stride[0] << "\n列步伐 = " << (uint16_t)stride[1] << "\n高步伐 = " << (uint16_t)stride[2];
		if (stride[3]) {
			cout << "\n进行填充操作\n\n";
		}
		else {
			cout << "\n不进行填充操作\n\n";
		}
	}
	//输出偏置信息
	if (content&_cnn_conv_op) {
		cout << "op = " << op[0] << "\nop_gr = " << op[1] << "\n\n";
	}
	//输出卷积结果张量
	if (content&_cnn_conv_out) {
		cout << "卷积结果张量 :\n";
		for (i = 0; i < out->deep; ++i) {
			tensor_output(out, i);
			cout << "\n";
		}
	}
	//输出激活函数信息
	if (content&_cnn_conv_fi){
		if ((void*)active_fi == (void*)mat_signmoid_par)
			//signmoid
			cout<<"激活函数 = signmoid\n";
		else if ((void*)active_fi == (void*)mat_tanh_par)
			//tanh
			cout << "激活函数 = tanh\n";
		else if ((void*)active_fi == (void*)mat_relu_par)
			//relu
			cout << "激活函数 = relu\n";
		else if ((void*)active_fi == (void*)mat_softmax_par)
			//softmax
			cout << "激活函数 = softmax\n";
		else
			cout << "激活函数 = NULL";
		cout << "\n";
	}
	return true;
}

//tensor:张量
//deep:深度
//cnn_conv卷积操作
bool cnn_conv::conv_ot(const struct TensorStr *tensor, uint16_t deep) {
	uint16_t i = NULL, j = NULL;
	uint16_t num0 = tensor->height, num1 = kernel->height;
	uint16_t offset0 = deep*tensor->height, offset1 = deep*out->height, offset2 = 0;
	//卷积核轮换次数
	for (j = 0; j < num1; ++j) {
		//输入张量轮换次数
		for (i = 0; i < num0; ++i) {
			//卷积前对输出矩阵清0
			mat_zero(out->mat[offset2 + offset1 + i]);
			//矩阵卷积
				(tensor->mat[offset0 + i], kernel->mat[j], out->mat[offset2 + offset1 + i], stride[0], stride[1], stride[3]);
			//卷积结果加上偏置
			if (op[0]) {
				mat_addto_value(out->mat[offset2 + offset1 + i],op[0]);
			}
			//使用激活函数激活
			active_fi(out->mat[offset2 + offset1 + i], out->mat[offset2 + offset1 + i]);
		}
		offset2 += num0;
	}
	return true;
}

//conv层输出求激活函数便导
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
	//误差张量长度
	for (i = 0; i < out->height; ) {
		//输入张量长度
		for (j = 0; j < tensor->height; ++j) {
			mat_conv_gr(out->mat[i],tensor->mat[j],kernel_gr->mat[u16_offset0],stride[0],stride[1]);
			++i;
		}
		//更新卷积梯度张量长度偏置
		u16_offset0++;
	}
	return true;
}




//cnn_pooling默认构造函数
cnn_pooling::cnn_pooling(){}

//cnn_pooling析构函数
cnn_pooling::~cnn_pooling()
{
	if (ot_type) {
		tensor_delete(coor_x);
	}
}

//line_v:池化行长
//row_v:池化列长
//out_v:输出张量信息
//type:池化类型
//cnn_pooling用户构造函数
cnn_pooling::cnn_pooling(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type)
{
	//初始化池化区域尺寸
	line = line_v;
	row = row_v;
	//创建输出张量
	out = tensor_create(out_v[0], out_v[1], out_v[2], out_v[3]);
	//池化类型(均值池化or最大值池化)
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

//tensor:输入张量
//deep:深度
//池化操作
bool cnn_pooling::pooling_ot(const struct TensorStr *tensor, const uint16_t deep)
{
	uint16_t i = NULL;
	uint16_t num0 = out->height;
	uint32_t offset0 = deep*tensor->height;
	switch (ot_type) {
		//均值池化
	case _cnn_pooling_aver:
		for (i = 0; i < num0;++i) {
			mat_pooling(tensor->mat[i], line, row, out->mat[i]);
		}
		break;
		//最大值池化
	case _cnn_pooling_max:
		break;
	default:return false; break;
	}
	return true;
}

//content:内容
//deep:深度
//打印cnn_pooling
bool cnn_pooling::output(const uint8_t content, const uint16_t deep)
{
	//打印信息
	if (content&_cnn_pooling_mes){
		cout << "cnn_pooling_message :\n";
		//打印池化类型
		switch (ot_type) {
		case _cnn_pooling_aver:cout << "type = aver_pooling\n"; break;
		case _cnn_pooling_max:cout << "type = max_poolinf\n"; break;
		default:cout << "type is error\n"; break;
		}
		//打印池化尺寸
		cout << "pooling_line = " << line << "	pooling_row = " << row << "\n\n";
	}
	//打印池化结果
	if (content&_cnn_pooling_out) {
		tensor_output(out, deep);
	}
	//打印最大值池化后记录的原张量最大值坐标
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

//cnn池化层误差反向传播
bool cnn_pooling::error_pass(TensorStr *tensor, uint16_t deep)
{
	uint16_t i = NULL, num0 = tensor->height;
	switch (ot_type){
		//均值池化模式
	case _cnn_pooling_aver:
		for (i = 0; i < num0; ++i) {
			mat_pooling_redu(out->mat[i], line, row, tensor->mat[i]);
		}
		break;
		//最大值池化模式
	case _cnn_pooling_max:
		break;
	default:
		return false;
		break;
	}
	return true;
}