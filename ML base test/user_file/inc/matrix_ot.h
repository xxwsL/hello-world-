#ifndef  _matrix_ot_h_
#define  _matrix_ot_h_
#include "xxwsL.h"

//get�����ַ
#define get(mat) &mat

//��������flag
#define MatTypeFlag 0x0003
#define i16Flag		0x0001
#define f32Flag		0x0002

//�����ŵ�ַ
#define i16MatrixAdd(MatName) (int16_t*)MatName
#define f32MatrixAdd(MatName) (float*)MatName

//����ά��
#define MatLine(MatName)   sizeof(MatName)/sizeof(MatName[0])
#define i16MatRow(MatName) sizeof(MatName[0])/2
#define f32MatRow(MatName) sizeof(MatName[0])/4

//������Ϣ
#define i16MatrixMessage(MatName) i16Flag,MatLine(MatName),i16MatRow(MatName) 
#define f32MatrixMessage(MatName) f32Flag,MatLine(MatName),f32MatRow(MatName)

//�����ִ�к���
#define MatInit mat_create,mat_delete
#define MatDeal output,mat_cut,mat_assignment,mat_zero,mat_size,mat_message
#define MatMath mat_cov,mat_norm2,mat_mult	
#define MatFiInit {MatInit,MatDeal,MatMath}

//�����ʼ����
#define i16MatInit(MatName) {i16MatrixAdd(MatName),i16MatrixMessage(MatName)}
#define f32MatInit(MatName) {f32MatrixAdd(MatName),f32MatrixMessage(MatName)}

typedef struct MatFunction {

	struct MatrixStr* (*mat_create) (uint16_t mat_line, uint16_t mat_row, uint16_t mat_type);
    bool (*mat_delete) (struct MatrixStr *mat);
	//��������
	bool (*output) (const struct MatrixStr *mat);
	struct MatrixStr* (*mat_cut) (const struct MatrixStr *mat_a, uint16_t cut_line_size, uint16_t cut_row_size, uint16_t number, uint16_t remat_type);
	bool (*mat_assignment) (struct MatrixStr *mat, float value);
	bool (*mat_zero) (struct MatrixStr *mat);
	uint32_t (*mat_size) (const struct MatrixStr *mat);
	bool (*mat_message) (const struct MatrixStr *mat);
	//�������㺯��
	struct MatrixStr* (*mat_cov) (const struct MatrixStr *mat);
	float (*mat_norm2) (const struct MatrixStr *mat);
	struct MatrixStr* (*mat_mult) (const struct MatrixStr *mat_l, const struct MatrixStr *mat_r);	//�����ʼ������
}MatFistr;

//һ�����
typedef struct MatrixStr {
	// ������Ϣ
	void *SaveAddr;	
	uint16_t flag;
	uint16_t line;
	uint16_t row;
	//uint16_t height;
	//MatFistr function;
}MatStr;

extern MatFistr mat_tf;

//��������
MatStr* mat_create(uint16_t mat_line, uint16_t mat_row, uint16_t mat_type);
//�ͷž���
bool mat_delete(MatStr *mat);

//�������Ʊ���ʽ���
bool output(const MatStr *mat);
//�и����
MatStr* mat_cut(const MatStr *mat_a, uint16_t cut_line_size, uint16_t cut_row_size, uint16_t number, uint16_t remat_type);
//����ֵ
bool mat_assignment(MatStr *mat, float value);
//����0
bool mat_zero(MatStr *mat);
//�����С
uint32_t mat_size(const MatStr *mat);
//��ӡ������Ϣ
bool mat_message(const MatStr *mat);
//��������ת��
MatStr* mat_change(const MatStr *mat);
//����װ��
bool mat_load(MatStr *mat, uint16_t line, uint16_t row, uint16_t mattype, void *saveadd);
//��������У��
bool mat_proofread(const MatStr *mat_a, const MatStr *mat_b);
//�����Ӧλת�����Ӧ����
bool mat_tovector(const uint8_t *buf, MatStr *loadmat);
//����ֵ����̬���ֵ
bool mat_rand_normal(MatStr *mat);

//�����Э����
MatStr* mat_cov(const MatStr *mat);
//���������������
float mat_norm2(const MatStr *mat);
//�������
MatStr* mat_mult(const MatStr *mat_l, const MatStr *mat_r);
bool mat_mult_par(const MatStr *mat_l, const MatStr *mat_r, MatStr *loadmat);
//����qr�ֽ�
bool mat_qr(const MatStr *mat, MatStr *q_mat, MatStr *s_mat);
//����ӷ�
MatStr* mat_add(const MatStr *mat_a, const MatStr *mat_b);
//�������
MatStr* mat_sub(const MatStr *mat_a, const MatStr *mat_b);
bool mat_sub_par(const MatStr *mat_a, const MatStr *mat_b, MatStr *loadmat);
//����signmoid������
MatStr* mat_signmoid(const MatStr *mat);
bool mat_signmoid_par(const MatStr *mat, MatStr *loadmat);
//������and���
float f32mat_dotmult_par(const MatStr *mat_l,const MatStr *mat_r, MatStr *loadmat);
//����tanh������
bool mat_tanh_par(const MatStr *mat, MatStr *loadmat);
//����relu������
bool mat_relu_par(const MatStr *mat, MatStr *loadmat);
//��������Ԫ�ؼ���һ��ֵ
bool mat_addto_value(MatStr *mat, const float value);
//����softmax��
bool mat_softmax_par(const MatStr *mat, MatStr *loadmat);
//��������Ԫ�����
double mat_element_sum(const MatStr *mat);
//����softmax��
bool mat_softmax_der(const MatStr *mat, MatStr *loadmat, const MatStr *target);
//����signmoid��
bool mat_signmoid_der(const MatStr *mat, MatStr *loadmat, const MatStr *target);
//����tanh��
bool mat_tanh_der(const MatStr *mat, MatStr *loadmat, const MatStr *target);
//����relu��
bool mat_relu_der(const MatStr *mat, MatStr *loadmat, const MatStr *target);

#endif // ! _matrix_ot_h_
