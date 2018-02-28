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
#define MatrixFunction //output,matrix_cut

//�����ʼ����
#define i16MatrixInit(MatName) {i16MatrixAdd(MatName),i16MatrixMessage(MatName),MatrixFunction}
#define f32MatrixInit(MatName) {f32MatrixAdd(MatName),f32MatrixMessage(MatName),MatrixFunction}

//һ�����
typedef struct MatrixStr {
	// ������Ϣ
	void* SaveAddr;	
	uint16_t flag;
	uint16_t line;
	uint16_t row;
	//������ú���
	//uint8_t (*output) (struct MatrixStr);
	//struct MatrixStr (*matrix_cut) (struct MatrixStr, uint8_t, uint8_t, uint8_t,uint8_t);
}MatStr;

uint8_t output(MatStr* mat); //�������Ʊ���ʽ���
MatStr matrix_cut(MatStr* mat_a,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type);	//�и����


#endif // ! _matrix_ot_h_
