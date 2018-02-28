#include "matrix_ot.h"

MatStr status;
//���float�;���
//mat:����
uint8_t output(MatStr* mat)		
{
	uint16_t i = 0, j = 0;							//�к��е�ַƫ����
	float* f32add;									//float���;���ָ��
	int16_t* i16add;								//int16_t����ָ��
	switch (mat->flag&MatTypeFlag){
		case i16Flag:
			i16add = (int16_t*)mat->SaveAddr;			//����ָ���׵�ַ
			for (i = 0; i < mat->line; i++) {
				for (j = 0; j < mat->row; j++) {
#ifdef Simulation										//����ģʽ
					printf("%d\t", *(i16add + j));		//�Ʊ�ʽ�������
#else
//�˴��Ӳ��Ƿ����ִ�д���
#endif
				}
				i16add += mat->row;
#ifdef Simulation										//����ģʽ
				printf("\n\n");
#else
//�˴��Ӳ��Ƿ����ִ�д���
#endif
			}
		break;
		case f32Flag:	
			f32add = (float*)mat->SaveAddr;				//����ָ���׵�ַ
			for (i = 0; i < mat->line; i++) {
				for (j = 0; j < mat->row; j++) {
#ifdef Simulation										//����ģʽ
					printf("%f\t", *(f32add + j));		//�Ʊ�ʽ�������
#else
//�˴��Ӳ��Ƿ����ִ�д���
#endif
				}
				f32add += mat->row;
#ifdef Simulation										//����ģʽ
				printf("\n\n");
#else
//�˴��Ӳ��Ƿ����ִ�д���
#endif
			}
		break;
	}
	return true;
}

//matrix_a:���и����a
//matrix_b:�и������
//cut_line_szie:�и��г�
//cut_row_size :�и��г�
//number:�и�Ŀ��λ��
MatStr matrix_cut(MatStr* mat,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type)
{
	uint16_t  i = 0,j=0;
	uint16_t  rows_max;
	int16_t   *i16mat_add, *i16remat;
	float	  *f32mat_add, *f32remat;
	MatStr remat;
	if (cut_line_size <= mat->line || cut_row_size <= mat->row) {
		remat.line = cut_line_size;
		remat.row = cut_row_size;
		rows_max = mat->row / cut_row_size;
		switch (mat->flag&MatTypeFlag) {
		case i16Flag:					//�и�int16_t����
			i16mat_add = (int16_t*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//��ʼ�и��ַ
			switch (remat_type)
			{
			case i16Flag:			//����int16_t����
#ifdef Simulation					//����ģʽ
				i16remat = (int16_t*)malloc(cut_line_size*cut_row_size * 2);
#else
//��̬�ڴ�����
#endif
				remat.SaveAddr = (int16_t*)i16remat;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(i16remat++) = (int16_t)(*(i16mat_add + j));
					}
					i16mat_add += mat->row;
				}
				remat.flag = i16Flag;
				break;
			case f32Flag:			//����float����
#ifdef Simulation						//����ģʽ
				f32remat = (float*)malloc(cut_line_size*cut_row_size * 4);
#else
//��̬�ڴ�����
#endif
				remat.SaveAddr = (float*)f32remat;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(f32remat++) = (float)(*(i16mat_add + j));
					}
					i16mat_add += mat->row;
				}
				remat.flag = f32Flag;
				break;
				break;
			default:break;
			}
			break;
		case f32Flag:					//�и�float����
			f32mat_add = (float*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//��ʼ�и��ַ
			switch (remat_type)
			{
			case i16Flag:				//����int16_t����
#ifdef Simulation						//����ģʽ
				i16remat = (int16_t*)malloc(cut_line_size*cut_row_size * 2);
#else
//��̬�ڴ�����
#endif
				remat.SaveAddr = (int16_t*)i16remat;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(i16remat++) = (int16_t)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat.flag = i16Flag;
				break;					//����float����
			case f32Flag:
#ifdef Simulation						//����ģʽ
				f32remat = (float*)malloc(cut_line_size*cut_row_size * 4);
#else
				//��̬�ڴ�����
#endif
				remat.SaveAddr = (float*)f32remat;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(f32remat++) = (float)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat.flag = f32Flag;
				break;
				break;
			default:break;
			}
			break;
		default:break;
		}
	}
	return remat;
}

