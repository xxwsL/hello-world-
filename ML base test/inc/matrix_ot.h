#ifndef  _matrix_ot_h_
#define  _matrix_ot_h_
#include "xxwsL.h"

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
	//�����ʼ������
	struct MatrixStr(*mat_create) (uint16_t mat_line, uint16_t mat_row, uint16_t mat_type);
	uint8_t (*mat_delete) (struct MatrixStr *mat);
	//��������
	uint8_t (*output) (const struct MatrixStr *mat);
	struct MatrixStr (*mat_cut) (struct MatrixStr *mat_a, uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number, uint8_t remat_type);
	uint8_t (*mat_assignment) (struct MatrixStr *mat, float value);
	uint8_t (*mat_zero) (struct MatrixStr *mat);
	uint32_t (*mat_size) (const struct MatrixStr *mat);
	uint8_t (*mat_message) (const struct MatrixStr *mat);
	//�������㺯��
	struct MatrixStr (*mat_cov) (const struct MatrixStr *mat);
	float (*mat_norm2) (const struct MatrixStr *mat);
	struct MatrixStr (*mat_mult) (const struct MatrixStr *mat_l, const struct MatrixStr *mat_r);
}MatFistr;

//һ�����
typedef struct MatrixStr {
	// ������Ϣ
	void* SaveAddr;	
	uint16_t flag;
	uint16_t line;
	uint16_t row;
	//uint16_t height;
	//MatFistr function;
}MatStr;

extern MatFistr matfi;

//��������
MatStr mat_create(uint16_t mat_line, uint16_t mat_row, uint16_t mat_type);
//�ͷž���
uint8_t mat_delete(MatStr *mat);

//�������Ʊ���ʽ���
uint8_t output(const MatStr *mat);
//�и����
MatStr mat_cut(MatStr *mat_a,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type);
//����ֵ
uint8_t mat_assignment(MatStr *mat, float value);
//����0
uint8_t mat_zero(MatStr *mat);
//�����С
uint32_t mat_size(const MatStr *mat);
//��ӡ������Ϣ
uint8_t mat_message(const MatStr *mat);

//�����Э����
MatStr mat_cov(const MatStr *mat);
//���������������
float mat_norm2(const MatStr *mat);
//�������
MatStr mat_mult(const MatStr *mat_l, const MatStr *mat_r);

#endif // ! _matrix_ot_h_
