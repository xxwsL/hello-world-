#include "matrix_ot.h"

MatFistr matfi = { MarFiInit };

//�Ż�����:1
//���float�;���
//mat:����
uint8_t output(MatStr *mat)		
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

//�Ż�����:1
//�Ѿ����и�ɶ�Ӧ��С
//matrix_a:���и����a
//matrix_b:�и������
//cut_line_szie:�и��г�
//cut_row_size :�и��г�
//number:�и�Ŀ��λ��
MatStr mat_cut(MatStr *mat,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type)
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
��̬�ڴ�����
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
��̬�ڴ�����
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
��̬�ڴ�����
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
				��̬�ڴ�����
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

//�Ż�����:0
//�����Э����		
//����:��������(������������1),����:����ά��
//mat:�������
MatStr mat_cov(MatStr *mat)
{
	uint16_t i = 0, j = 0,k=0;
	uint32_t line_offset=0,diff_mat_line=0;
	MatStr remat = {};		//��׼c����������ʼ��
	int16_t *i16mat_add;
	float *aver_mat,*cov_mat,*f32mat_add,*diff_mat;
#ifdef Simulation		//����ģʽ��
	cov_mat  = (float*)malloc(mat->row*mat->row*4);		//�����ڴ��ע���С����
	aver_mat = (float*)malloc(mat->row * 4);			//ע�⣬ע�⣬ע��
	diff_mat = (float*)malloc(mat->line*mat->row*4);
	for (i = 0; i < mat->row; i++) {
		*(aver_mat + i) = 0;
	}
	for (i = 0; i < mat->row*mat->row; i++) {
		*(cov_mat + i) = 0;
	}
#else
//�ڴ������
#endif
	switch (mat->flag&MatTypeFlag){	
		case i16Flag:										//����int16_t����
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//������ͬά���ܺ�
				for (j = 0; j < mat->row; j++) {
					*(aver_mat + j) +=(float)(*(i16mat_add++));		
				}
			}
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//������ͬά�Ⱦ�ֵ
				*(aver_mat + j) /= mat->line;
			}
			for (i = 0; i < mat->line; i++) {				//��������
				for (j = 0; j < mat->row; j++) {
					*(diff_mat + line_offset + j) = (*(i16mat_add++)) - (*(aver_mat + j));
				}
				line_offset += mat->row;
			}
			break;
		case f32Flag:										//����float����
			f32mat_add = (float*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//������ͬά���ܺ�
				for (j = 0; j < mat->row; j++) {
					*(aver_mat + j) = (*(aver_mat + j)) + (float)(*(f32mat_add++));
				}
			}
			f32mat_add = (float*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//������ͬά�Ⱦ�ֵ
				*(aver_mat + j) /= mat->line;;
			}
			for (i = 0; i < mat->line; i++) {				//��������
				for (j = 0; j < mat->row; j++) {
					*(diff_mat+ line_offset + j) = (*(f32mat_add++)) - (*(aver_mat + j));
				}
				line_offset += mat->row;
			}
	default:break;
	}
	line_offset = 0;
	for (i = 0; i < mat->row;i++) {							//�����ά��֮��Э����		
		for (j = i; j < mat->row; j++) {
			for (k = 0; k < mat->line; k++) {
				*(cov_mat + line_offset + j) += (*(diff_mat+i+ diff_mat_line))*(*(diff_mat+j+ diff_mat_line));
				diff_mat_line += mat->row;
			}
			diff_mat_line = 0;
			(*(cov_mat + line_offset + j)) /= (mat->line - 1);
			if (i != j) {
				*(cov_mat + j*mat->row + i) = (*(cov_mat + line_offset + j));
			}
		}
		line_offset += mat->row;
	}
	remat.flag = f32Flag;
	remat.line = mat->row;
	remat.row = mat->row;
	remat.SaveAddr = (float*)cov_mat;
#ifdef Simulation		//����ģʽ��
	free(aver_mat);		//�ͷ��ڴ�
	free(diff_mat);
	aver_mat = NULL;	//ָ�����
	diff_mat = NULL;
#else
//�ڴ������
	aver_mat = NULL;
	diff_mat = NULL;
#endif
	return remat;
}


