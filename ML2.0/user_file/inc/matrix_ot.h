#ifndef  _matrix_ot_h_
#define  _matrix_ot_h_
#include "xxwsL.h"

//get矩阵地址
#define get(mat) &mat

//矩阵类型flag
#define MatTypeFlag 0x0003
#define i16Flag		0x0001
#define f32Flag		0x0002

//矩阵存放地址
#define i16MatrixAdd(MatName) (int16_t*)MatName
#define f32MatrixAdd(MatName) (float*)MatName

//矩阵维度
#define MatLine(MatName)   sizeof(MatName)/sizeof(MatName[0])
#define i16MatRow(MatName) sizeof(MatName[0])/2
#define f32MatRow(MatName) sizeof(MatName[0])/4

//矩阵信息
#define i16MatrixMessage(MatName) i16Flag,MatLine(MatName),i16MatRow(MatName) 
#define f32MatrixMessage(MatName) f32Flag,MatLine(MatName),f32MatRow(MatName)

//矩阵可执行函数
#define MatInit mat_create,mat_delete
#define MatDeal output,mat_cut,mat_assignment,mat_zero,mat_size,mat_message
#define MatMath mat_covar,mat_norm2,mat_mult	
#define MatFiInit {MatInit,MatDeal,MatMath}

//矩阵初始化宏
#define i16MatInit(MatName) {i16MatrixAdd(MatName),i16MatrixMessage(MatName)}
#define f32MatInit(MatName) {f32MatrixAdd(MatName),f32MatrixMessage(MatName)}

//激活函数buf宏
#define active_fi_str(active_fi) bool (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat)
#define active_fi_buf(active_fi,n) bool (*active_fi[n]) (const struct MatrixStr *mat, struct MatrixStr *loadmat)

typedef struct MatFunction {

	struct MatrixStr* (*mat_create) (uint16_t mat_line, uint16_t mat_row, uint16_t mat_type);
    bool (*mat_delete) (struct MatrixStr *mat);
	//矩阵处理函数
	bool (*output) (const struct MatrixStr *mat);
	struct MatrixStr* (*mat_cut) (const struct MatrixStr *mat_a, uint16_t cut_line_size, uint16_t cut_row_size, uint16_t number, uint16_t remat_type);
	bool (*mat_assignment) (struct MatrixStr *mat, float value);
	bool (*mat_zero) (struct MatrixStr *mat);
	uint32_t (*mat_size) (const struct MatrixStr *mat);
	bool (*mat_message) (const struct MatrixStr *mat);
	//矩阵运算函数
	struct MatrixStr* (*mat_covar) (const struct MatrixStr *mat);
	float (*mat_norm2) (const struct MatrixStr *mat);
	struct MatrixStr* (*mat_mult) (const struct MatrixStr *mat_l, const struct MatrixStr *mat_r);	//矩阵初始化函数
}MatFistr;

//一类矩阵
typedef struct MatrixStr {
	// 矩阵信息
	void *SaveAddr;	
	uint16_t flag;
	uint16_t line;
	uint16_t row;
	//uint16_t height;
	//MatFistr function;
}MatStr;

extern MatFistr mat_tf;

//创建矩阵
MatStr* mat_create(uint16_t mat_line, uint16_t mat_row, uint16_t mat_type);
//释放矩阵
bool mat_delete(MatStr *mat);
//创建张量
MatStr** mat_vetor_create(uint16_t vetor_len);

//矩阵已制表形式输出
bool output(const MatStr *mat);
//切割矩阵
MatStr* mat_cut(const MatStr *mat_a, uint16_t cut_line_size, uint16_t cut_row_size, uint16_t number, uint16_t remat_type);
//矩阵赋值
bool mat_assignment(MatStr *mat, float value =0.0f);
//矩阵赋0
bool mat_zero(MatStr *mat);
//矩阵大小
uint32_t mat_size(const MatStr *mat);
//打印矩阵信息
bool mat_message(const MatStr *mat);
//矩阵类型转换
MatStr* mat_change(const MatStr *mat);
//矩阵装载
bool mat_load(MatStr *mat, uint16_t line, uint16_t row, uint16_t mattype, void *saveadd);
//两个矩阵校对
bool mat_proofread(const MatStr *mat_a, const MatStr *mat_b);
//数组对应位转换相对应向量
bool mat_tovector(const uint8_t *buf, MatStr *loadmat, float r_value = 0.1f);
//矩阵赋值似正态随机值
bool mat_rand_normal(MatStr *mat);
//矩阵上下翻转
bool f32mat_up_down_change(MatStr *mat);
//复制矩阵到另一个矩阵
bool mat_copy(MatrixStr *inmat, MatrixStr *loadmat, uint32_t nums);
//释放矩阵容器内存(不释放容器里数据)
bool mat_vetor_delete(MatrixStr **vetor);
//矩阵升序赋值
bool mat_up_assign(MatrixStr *mat, const float value = 0);

//求矩阵协方差
MatStr* mat_covar(const MatStr *mat);
//求向量矩阵二范数
float mat_norm2(const MatStr *mat);
//矩阵相乘
MatStr* mat_mult(const MatStr *mat_l, const MatStr *mat_r);
bool mat_mult_par(const MatStr *mat_l, const MatStr *mat_r, MatStr *loadmat);
//矩阵qr分解
bool mat_qr(const MatStr *mat, MatStr *q_mat, MatStr *s_mat);
//矩阵加法
MatStr* mat_add(const MatStr *mat_a, const MatStr *mat_b);
//矩阵减法
MatStr* mat_sub(const MatStr *mat_a, const MatStr *mat_b);
bool mat_sub_par(const MatStr *mat_a, const MatStr *mat_b, MatStr *loadmat);
//矩阵signmoid函数化
MatStr* mat_signmoid(const MatStr *mat);
bool mat_signmoid_par(const MatStr *mat, MatStr *loadmat);
//矩阵点乘and叉乘
float f32mat_dotmult_par(const MatStr *mat_l,const MatStr *mat_r, MatStr *loadmat);
//矩阵tanh函数化
bool mat_tanh_par(const MatStr *mat, MatStr *loadmat);
//矩阵relu函数化
bool mat_relu_par(const MatStr *mat, MatStr *loadmat);
//矩阵所有元素加上一个值
bool mat_addto_value(MatStr *mat, const float value);
//矩阵softmax化
bool mat_softmax_par(const MatStr *mat, MatStr *loadmat);
//矩阵所有元素求和
double mat_element_sum(const MatStr *mat);
//矩阵softmax求导
bool mat_softmax_der(const MatStr *mat, MatStr *loadmat, const MatStr *target);
//矩阵signmoid求导
bool mat_signmoid_der(const MatStr *mat, MatStr *loadmat, const MatStr *target);
//矩阵tanh求导
bool mat_tanh_der(const MatStr *mat, MatStr *loadmat, const MatStr *target);
//矩阵relu求导
bool mat_relu_der(const MatStr *mat, MatStr *loadmat, const MatStr *target);
//矩阵交叉熵
float mat_cross_entropy(const MatStr *l_mat, const MatStr *r_mat);
//矩阵最大值元素
float mat_maxelement(const MatStr *mat);
//偏置矩阵max元素的softmax
bool mat_softmax_submax_par(const MatStr *mat, MatStr *loadmat);
//平方损失函数
float mat_square_loss(const MatStr *mat, const MatStr *target);
//矩阵卷积
bool mat_conv(const MatrixStr *in_mat, MatrixStr *kernel, MatrixStr *load_mat, uint8_t line_stride, uint8_t row_stride, uint8_t padding);
//矩阵均值池化
bool mat_pooling(const MatrixStr *mat, uint16_t pool_line, uint16_t pool_row, MatrixStr *loadmat);
//矩阵所有元素成一个数
bool mat_mult_element(const MatrixStr *mat, float value, MatrixStr *loadmat);
//均值池化还原
bool mat_pooling_redu(const MatrixStr *mat, const uint16_t pool_line, const uint16_t pool_row, MatrixStr *loadmat);
//卷积矩阵求梯度
bool mat_conv_gr(const MatrixStr *error_mat, const MatrixStr *in_mat, MatrixStr *loadmat, const uint16_t line_stride, const uint16_t row_stride);
//卷积均值误差传递
bool mat_conv_back(const MatrixStr *error_mat, const MatrixStr *kernel_mat, MatrixStr *loadmat, const uint16_t stride_line, const uint16_t stride_row);

#endif // ! _matrix_ot_h_
