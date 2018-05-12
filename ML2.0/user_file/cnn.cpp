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
	tensor_rand_normal_mat(kernel);
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
	}
	cout << "_______________________________________________________________________________";
	cout << "\n\n";
	return true;
}

//tensor:张量
//deep:深度
//cnn_conv卷积操作
bool cnn_conv::conv_ot(const struct TensorStr *tensor) {
	uint16_t i, j;
	MatrixStr *mat0 = mat_create(out->mat[0]->line, out->mat[0]->row, f32Flag);
	tensor_assign(out);
	//卷积核轮换次数
	for (j = 0; j < kernel->height; ++j) {
		//输入张量轮换次数
		for (i = 0; i < tensor->height; ++i) {
			//矩阵卷积
			mat_conv(tensor->mat[i], kernel->mat[j], mat0, stride[0], stride[1], stride[3]);
			//卷积结果加上偏置
			if (op[0]) {
				mat_addto_value(mat0,op[0]);
			}
			mat_add(out->mat[j], mat0, out->mat[j]);
		}
		//使用激活函数激活
		active_fi(out->mat[j], out->mat[j]);
	}
	mat_delete(mat0);
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

//tensor:输入张量
//更新当前conv层卷积核梯度
bool cnn_conv::conv_gr(const TensorStr *tensor)
{
	uint16_t i = 0, j = 0;
	MatrixStr *mat0 = mat_create(kernel_gr->mat[0]->line, kernel_gr->mat[0]->row, f32Flag);	
	//误差张量长度
	for (i = 0; i < out->height; ++i) {
		mat_conv_gr(out->mat[i], tensor->mat[0], kernel_gr->mat[i], stride[0], stride[1]);
		//输入张量长度
		for (j = 1; j < tensor->height; ++j) {
			mat_conv_gr(out->mat[i],tensor->mat[j], mat0,stride[0],stride[1]);
			mat_add(kernel_gr->mat[i], mat0, kernel_gr->mat[i]);
		}
		//更新卷积梯度张量长度偏置
	}
	//释放申请的内存
	mat_delete(mat0);
	return true;
}

//tensor:输入张量
//误差传递到前conv层
bool cnn_conv::error_pass_conv(TensorStr *tensor)
{
	uint16_t i = 0;
	MatrixStr *mat0 = mat_create(tensor->mat[0]->line, tensor->mat[0]->row, f32Flag);
	//误差张量长度
	for (i = 0; i < out->height; ++i) {
		mat_conv_pass(out->mat[i], kernel->mat[i], mat0, stride[0], stride[1]);
	}
	//输入张量长度
	for (i = 0; i < tensor->height; ++i) {
		f32mat_dotmult_par(mat0, tensor->mat[i], tensor->mat[i]);
	}
	mat_delete(mat0);
	return true;
}

//tensor:输入张量
//误差传递到pool层
bool cnn_conv::error_pass_pool(TensorStr *tensor)
{
	uint16_t i = 0;
	MatrixStr *mat0 = mat_create(tensor->mat[0]->line, tensor->mat[0]->row, f32Flag);
	uint32_t num0 = mat_size(mat0);
	//误差张量长度
	for (i = 0; i < out->height; ++i) {
		mat_conv_pass(out->mat[i], kernel->mat[i], mat0, stride[0], stride[1]);
	}
	//输入张量长度
	for (i = 0; i < tensor->height; ++i) {
		mat_copy(mat0, tensor->mat[i], num0);
	}
	mat_delete(mat0);
	return true;
}

//learmspeed:学习速率
//更新卷积核
bool cnn_conv::update(const float &learmspeed)
{
	uint16_t i;
	for (i = 0; i < kernel->height; ++i) {
		mat_mult_element(kernel_gr->mat[i], learmspeed, kernel_gr->mat[i]);
		mat_sub_par(kernel->mat[i], kernel_gr->mat[i], kernel->mat[i]);
	}
	return true;
}

//cnn_pooling默认构造函数
cnn_pool::cnn_pool(){}

//cnn_pooling析构函数
cnn_pool::~cnn_pool()
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
cnn_pool::cnn_pool(uint16_t line_v, uint16_t row_v, array<uint16_t, 4> out_v, uint8_t type)
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
bool cnn_pool::pooling_ot(const struct TensorStr *tensor)
{
	uint16_t i = NULL;
	switch (ot_type) {
		//均值池化
	case _cnn_pooling_aver:
		for (i = 0; i < out->height;++i) {
			mat_aver_pooling(tensor->mat[i], line, row, out->mat[i]);
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
bool cnn_pool::output(const uint8_t content)
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
		cout << "out_layer :\n";
		tensor_output(out);
	}
	//打印最大值池化后记录的原张量最大值坐标
	if (content&_cnn_pooling_coor) {
		if (!coor_x) {
			cout << "NO coor\n";
			goto loop0;
		}
		cout << "coor_x :\n";
		tensor_output(coor_x);
		cout << "coor_y :\n";
		tensor_output(coor_y);
	}
	loop0:cout << "_______________________________________________________________________________";
	cout << "\n\n";
	return true;
}

//cnn池化层误差反向传播
bool cnn_pool::error_pass(TensorStr *tensor, uint16_t deep)
{
	uint16_t i = NULL, num0 = tensor->height;
	switch (ot_type){
		//均值池化模式
	case _cnn_pooling_aver:
		for (i = 0; i < num0; ++i) {
			mat_aver_pooling_redu(out->mat[i], line, row, tensor->mat[i]);
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