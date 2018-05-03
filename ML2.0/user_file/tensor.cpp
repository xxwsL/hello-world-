#include "tensor.h"

//优化次数:1
//创建张量
//line:行长
//row:列长
//height:张量的维数
//return:TensorStr指针或标志位
TensorStr *tensor_create(const uint16_t line, const uint16_t row, const uint16_t height, uint16_t deep)
{
	uint32_t i = NULL, nums_0 = height * deep;
	TensorStr *tensor = new TensorStr;
	//张量高不能为0
	if (height!=NULL) {
		//申请内存成功
		if (tensor) {
			//初始化张量的高
			tensor->height = height;
			tensor->deep = deep;
			//初始化张量容器
			if (tensor->mat = mat_vetor_create(height)) {
				//如果行和列都不为0
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

//优化次数:0
//张量装载
//tensor:待装载张量
//vettor:矩阵容器
//vetor_len:容器长度
//return:返回bool标志位
bool tensor_load(void *tensor_add, MatrixStr **vetor,const uint16_t vetor_len, const uint16_t deep)
{
	TensorStr *tensor = NULL;
	tensor = (TensorStr*)tensor_add;
	tensor->height = vetor_len;
	tensor->deep = deep;
	tensor->mat = vetor;
	return true;
}

//优化次数:0
//张量转移图运算
//load_tensor:装载张量
//in_tensor:输入张量
//direct:转移方向
//return:返回bool标志位
bool tensorarch_op(TensorArch *tensorarch,TensorStr *in_tensor,const uint8_t direct,const uint16_t deep)
{
	uint8_t *buf = NULL, *flag_add0 = NULL;
	uint32_t i = NULL;
	uint32_t temp_size = NULL,u32num0=NULL;
	TensorStr *tensor_p = NULL;
	//数据流方向判决
	switch (direct){
		//转换方向左
		case _direct_left:
			tensor_p = tensorarch->r_d_tensor;
			break;
		//转换方向上
		case _direct_up:
			tensor_p = tensorarch->r_d_tensor;
			break;
		//转换方向右
		case _direct_right:
			tensor_p = tensorarch->l_u_tensor;
			break;
		//转换方向下
		case _direct_down:
			tensor_p = tensorarch->l_u_tensor;
			break;
		default:
			return false;break;
	}
	//获得装载张量和输入张量的尺寸
	temp_size = tensor_element_size(tensor_p); 
	u32num0 = tensor_element_size(in_tensor);
	//判断是否符合装载条件
	if (temp_size != u32num0) {
		return false;
	}
	//创建缓存buf
	buf = new uint8_t[u32num0 * 4];
	flag_add0 = buf;
	u32num0 = in_tensor->deep * in_tensor->height;
	//把输入张量里的数据拷贝到缓存buf里
	for (i = NULL; i < u32num0;++i) {
		temp_size = mat_size(in_tensor->mat[i]) * 4;
		//标准库内存拷贝函数
		memcpy(flag_add0,in_tensor->mat[i]->SaveAddr,temp_size);
		flag_add0 += temp_size;
	}
	//把缓存buf的数据拷贝到装载张量里
	flag_add0 = buf; 
	u32num0 = tensor_p->deep * tensor_p->height;
	for (i = NULL; i < u32num0; ++i) {
		temp_size = mat_size(tensor_p->mat[i]) * 4; 
		memcpy(tensor_p->mat[i]->SaveAddr, flag_add0, temp_size);
		flag_add0 += temp_size;
	}
	//拷贝完成,释放缓存内存
	delete[]buf;
	return true;
}

//优化次数:0
//获得张量尺寸
//tensor:输入张量
//return:返回张量尺寸
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

//优化次数:0
//打印张量
//tensor:输入张量
//return:bool标志位
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

//优化次数:0
//张量转移图装载
//load:张量转移图
//l_tensor;左张量
//r_tensor:右张量
bool tensor_arch_load(TensorArch *load,TensorStr *l_tensor,TensorStr *r_tensor)
{
	load->l_u_tensor = l_tensor;
	load->r_d_tensor = r_tensor;
	return true;
}

//优化次数:0
//打印张量信息
//tensor:输入张量
//return:boo标志
bool tensor_message(TensorStr *tensor, uint16_t deep)
{
	uint16_t i = NULL;
	uint32_t offset = tensor->deep * deep;
	if (tensor == 0) {
		return false;
	}
	//打印张量高度信息
	cout << "张量高度 = "<<tensor->height<<endl<<endl;
	for (i = NULL; i < tensor->height; ++i) {
		cout << "mat_" << i << endl;
		mat_message(tensor->mat[i+offset]);
	}
	return true;
}

//优化次数:0
//释放张量内存
//tensor:输入张量
//return:bool标志
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

//优化次数:0
//l_u_line:左张量行长
//l_u_row:左张量列长
//l_u_height:左张量高
//r_d_lin:右张量行长
//r_d_row:右张量列长
//r_d_height:右张量高
//return:TensorArch指针
//创建张量转移结构
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

//tensorarch:张量转移结构
//return:bool标志
//释放张量转移结构内存
bool tensorarch_delete(TensorArch *tenasorarch)
{
	tensor_delete(tenasorarch->l_u_tensor);
	tensor_delete(tenasorarch->r_d_tensor);
	delete tenasorarch;
	return true;
}

//优化:0
//tensorarch_add:tensorarch地址
//direct:指向
//打印tensorarch图
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

//优化:0
//tensor:输入张量
//value:有效浮点数值
//张量赋值
bool tensor_assignment(TensorStr *tensor, float value)
{
	uint32_t i = NULL, nums_0 = tensor->height * tensor->deep;
	for (; i < nums_0;++i) {
		mat_assignment(tensor->mat[i],value);
	}
	return true;
}

//张量拷贝
bool tensor_copy(const TensorStr *tensor, TensorStr *loadtensor)
{
	uint32_t num0 = tensor->height*tensor->deep;
	uint32_t i = NULL;
	for (i = 0; i < num0; ++i) {
		mat_copy(tensor->mat[i], loadtensor->mat[i], mat_size(tensor->mat[i]));
	}
	return true;
}

//张量升序赋值
bool tensor_up_assign(TensorStr *tensor, const float value)
{
	uint32_t i = 0, u32num0 = tensor->deep*tensor->height;
	for (; i < u32num0; ++i) {
		mat_up_assign(tensor->mat[i], value);
	}
	return true;
}

//返回张量矩阵数量
uint32_t tensor_mat_size(const TensorStr *tensor)
{
	return uint32_t(tensor->deep*tensor->height);
}