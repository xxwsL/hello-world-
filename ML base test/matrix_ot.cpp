#include "matrix_ot.h"

MatFistr matfi = MatFiInit;

//�Ż�����:3
//���float�;���
//mat:����
//return:λ��8��־λ
uint8_t output(const MatStr *mat)		
{
	uint16_t i = 0, j = 0;								//�к��е�ַƫ����
	float* f32add;										//float���;���ָ��
	int16_t* i16add;									//int16_t����ָ��
	if ((mat->SaveAddr == NULL) || (mat->flag == 0))
		return false;
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

//�Ż�����:2
//�Ѿ����и�ɶ�Ӧ��С
//matrix_a:���и����a
//matrix_b:�и������
//cut_line_szie:�и��г�
//cut_row_size :�и��г�
//number:�и�Ŀ��λ��
//return:����ṹ��
MatStr mat_cut(MatStr *mat,uint8_t cut_line_size, uint8_t cut_row_size, uint8_t number,uint8_t remat_type)
{
	uint16_t  i = NULL,j=NULL;
	uint16_t  rows_max=NULL;
	int16_t   *i16mat_add=NULL, *i16remat=NULL;
	float	  *f32mat_add=NULL, *f32remat=NULL;
	MatStr remat;
	if (cut_line_size <= mat->line || cut_row_size <= mat->row) {
		rows_max = mat->row / cut_row_size;
		switch (mat->flag&MatTypeFlag) {
		case i16Flag:					//�и�int16_t����
			i16mat_add = (int16_t*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//��ʼ�и��ַ
			switch (remat_type)
			{
				case i16Flag:			//����int16_t����
					remat = mat_create(cut_line_size, cut_row_size,i16Flag);
					i16remat =(int16_t*)remat.SaveAddr;				
					for (i = 0; i < cut_line_size; i++) {
						for (j = 0; j < cut_row_size; j++) {
							*(i16remat++) = (int16_t)(*(i16mat_add + j));
						}
						i16mat_add += mat->row;
					}
					remat.flag = i16Flag;
					break;
				case f32Flag:			//����float����
					remat = mat_create(cut_line_size, cut_row_size, f32Flag);
					f32remat = (float*)remat.SaveAddr;
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
				remat = mat_create(cut_line_size, cut_row_size, i16Flag);
				i16remat = (int16_t*)remat.SaveAddr;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(i16remat++) = (int16_t)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat.flag = i16Flag;
				break;					//����float����
			case f32Flag:
				remat = mat_create(cut_line_size, cut_row_size, f32Flag);
				f32remat = (float*)remat.SaveAddr;
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

//�Ż�����:2
//�����Э����		
//����:��������(������������1),����:����ά��
//mat:�������
//
MatStr mat_cov(const MatStr *mat)
{
	uint16_t i = 0, j = 0,k=0;
	int16_t *i16mat_add;
	uint32_t line_offset=0,diff_mat_line=0;
	MatStr remat,aver_mat,diff_mat;
	float *f32mat_add;
	remat = mat_create(mat->row,mat->row,f32Flag);		//�����ڴ��ע���С����
	mat_zero(&remat);
	aver_mat = mat_create(1, mat->row, f32Flag);			//ע�⣬ע�⣬ע��
	mat_zero(&aver_mat);
	diff_mat = mat_create(mat->line,mat->row,f32Flag);
	switch (mat->flag&MatTypeFlag){	
		case i16Flag:										//����int16_t����
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//������ͬά���ܺ�
				for (j = 0; j < mat->row; j++) {
					*((float*)aver_mat.SaveAddr + j) +=(float)(*(i16mat_add++));		
				}
			}
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//������ͬά�Ⱦ�ֵ
				*((float*)aver_mat.SaveAddr + j) /= mat->line;
			}
			for (i = 0; i < mat->line; i++) {				//��������
				for (j = 0; j < mat->row; j++) {
					*((float*)diff_mat.SaveAddr + line_offset + j) = (*(i16mat_add++)) - (*((float*)aver_mat.SaveAddr + j));
				}
				line_offset += mat->row;
			}
			break;
		case f32Flag:										//����float����
			f32mat_add = (float*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//������ͬά���ܺ�
				for (j = 0; j < mat->row; j++) {
					*((float*)aver_mat.SaveAddr + j) = (*((float*)aver_mat.SaveAddr + j)) + (float)(*(f32mat_add++));
				}
			}
			f32mat_add = (float*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//������ͬά�Ⱦ�ֵ
				*((float*)aver_mat.SaveAddr + j) /= mat->line;;
			}
			for (i = 0; i < mat->line; i++) {				//��������
				for (j = 0; j < mat->row; j++) {
					*((float*)diff_mat.SaveAddr + line_offset + j) = (*(f32mat_add++)) - (*((float*)aver_mat.SaveAddr + j));
				}
				line_offset += mat->row;
			}
	default:break;
	}
	line_offset = 0;
	for (i = 0; i < mat->row;i++) {							//�����ά��֮��Э����		
		for (j = i; j < mat->row; j++) {
			for (k = 0; k < mat->line; k++) {
				*((float*)remat.SaveAddr + line_offset + j) += (*((float*)diff_mat.SaveAddr +i+ diff_mat_line))*(*((float*)diff_mat.SaveAddr +j+ diff_mat_line));
				diff_mat_line += mat->row;
			}
			diff_mat_line = 0;
			(*((float*)remat.SaveAddr + line_offset + j)) /= (mat->line - 1);
			if (i != j) {
				*((float*)remat.SaveAddr + j*mat->row + i) = (*((float*)remat.SaveAddr + line_offset + j));
			}
		}
		line_offset += mat->row;
	}
	mat_delete(&aver_mat);
	mat_delete(&diff_mat);
	return remat;
}

//�Ż�����:0
//��������(�����ڴ�Ƭ���ֵӲ�����ֵ,���ʼ��0)
//mat_line:��������
//mat_row:��������
//mat_type:��������
//return:����ṹ��
MatStr mat_create(uint16_t mat_line, uint16_t mat_row, uint16_t mat_type)
{
	int16_t *i16add;
	float *f32add;
	MatStr create_mat;
	switch (mat_type&MatTypeFlag){
		case i16Flag:
#ifdef Simulation		//����ģʽ
			i16add = (int16_t*)malloc(mat_line*mat_row*2);
#else
//�ڴ����ģ��
#endif 
			if (i16add != NULL) {		//�����ڴ���
				create_mat.SaveAddr = i16add;
				create_mat.flag = i16Flag;
			}
			else {						//�����ڴ�ʧ��
				create_mat.SaveAddr = NULL;
				create_mat.flag = 0;
				create_mat.line = 0;		
				create_mat.row  = 0;
				return create_mat;
			}
			break;
		case f32Flag:
#ifdef Simulation		//����ģʽ
			f32add = (float*)malloc(mat_line*mat_row * 4);
#else
//�ڴ����ģ��
#endif 		
			if (f32add != NULL) {
				create_mat.SaveAddr = f32add;
				create_mat.flag = f32Flag;
			}
			else {
				create_mat.SaveAddr = NULL;
				create_mat.flag = 0;
				create_mat.line = 0;		
				create_mat.row  = 0;
				return create_mat;
			}
			break;
	default:
		create_mat.SaveAddr = NULL;
		create_mat.flag = 0;
		create_mat.line = 0;
		create_mat.row  = 0;
		return create_mat;
		break;
}
	create_mat.line = mat_line;		//�����С��ֵ
	create_mat.row  = mat_row;
	return create_mat;
}

//ɾ�������ͷž����ڴ�
//mat:Ҫ�ͷŵľ���ָ��
//return:λ��8��־λ
uint8_t mat_delete(MatStr *mat)
{
	if (mat->SaveAddr == NULL) {
		return false;
	}
	switch (mat->flag&MatTypeFlag)
	{
		case i16Flag:
#ifdef Simulation		//����ģʽ
			free((int16_t*)mat->SaveAddr);
			mat->SaveAddr = NULL;
#else
//�ڴ����ģ��
#endif // Simulation
			break;
		case f32Flag:
#ifdef Simulation		//����ģʽ
			free((float*)mat->SaveAddr);
			mat->SaveAddr = NULL;
#else
//�ڴ����ģ��
#endif // Simulation
			break;
	default:
		break;
	}
	mat->flag = NULL;
	mat->line = NULL;
	mat->row  = NULL;
	return true;
}

//�Ż�����:0
//����ȫԱ��ֵvalue
//mat:���븳ֵ����
//value:��Чֵ
//return:λ��8��־λ
uint8_t mat_assignment(MatStr *mat,float value)
{
	int16_t *i16add=NULL;
	float *f32add=NULL;
	uint32_t i=0,mat_size=0;
	mat_size = mat->line*mat->row;
	if ((mat->SaveAddr==NULL)||(mat_size==NULL)){			//�����ַ�ʹ�С����Ϊ0
		return false;
	}
	switch (mat->flag&MatTypeFlag){							//���������ж�
	case i16Flag:
		i16add = (int16_t*)mat->SaveAddr;
		for (i = 0; i<mat_size; ++i) {
			*(i16add + i) = (int16_t)value;
		}
		break;
	case f32Flag:
		f32add = (float*)mat->SaveAddr;
		for (i = 0; i<mat_size; ++i) {
			*(f32add + i) = (float)value;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

//�Ż�����:0
//����ȫԱ��ֵ0
//mat:���븳ֵ����
//return:λ��8��־λ
uint8_t mat_zero(MatStr *mat)
{
	if (mat_assignment(mat, 0))
		return true;
	else
		return false;
}

//�Ż�����:0
//��������С
//mat:�������
//return:λ��32��Чֵ
uint32_t mat_size(const MatStr *mat)
{
	return (uint32_t)(mat->line*mat->row);
}

//�Ż�����:0
//�����mat������
//mat:������������
//return:����float��Чֵ
float mat_norm2(const MatStr *mat)
{
	int16_t *i16add;
	uint32_t mat_size=0;
	uint32_t i=0;
	float *f32add,norm2 = 0;
	mat_size=matfi.mat_size(mat);
	if ((mat_size == 0)||(mat->row!=1)) {
		return error;
	}
	switch (MatTypeFlag&mat->flag){
		case i16Flag:
			i16add = (int16_t*)mat->SaveAddr;
			for (i = 0; i < mat_size; ++i){
				norm2 += (float)((*(i16add + i)) * (*(i16add + i)));
			}
			break;
		case f32Flag:
			f32add = (float*)mat->SaveAddr;
			for (i = 0; i < mat_size; ++i) {
				norm2 += (float)((*(f32add + i)) * (*(f32add + i)));
			}
			break;
	default:
		return error;
		break;
	}
	return (float)sqrt(norm2);
}

//�Ż�����:0
//�������
//mat_a:��˾���a
//mat_b:�ҳ˾���b
//return:float�������͵ľ�����
MatStr mat_mult(const MatStr *mat_l,const MatStr *mat_r)
{
	uint16_t l_line = NULL, r_row = NULL, adds = NULL, l_line_offset=NULL,r_row_offset=NULL;
	int16_t *i16mat_l_add=NULL,*i16mat_r_add=NULL;
	float *f32mat_l_add = NULL, *f32mat_r_add = NULL,*remat_add=NULL;
	uint32_t line_offset = NULL;
	MatStr remat;
	if((mat_l->SaveAddr==NULL)||(mat_r->SaveAddr==NULL)||(mat_l->row!=mat_r->line)){		//�վ���and��˾����в������ҳ˾��󷵻ؿվ���
		remat=mat_create(NULL,NULL,NULL);
		return  remat;
	}
	remat = mat_create(mat_l->line,mat_r->row,f32Flag);		//Ϊ���ؾ��󿪱��ڴ�
	mat_zero(&remat);
	remat_add = (float*)remat.SaveAddr;
	switch (mat_l->flag&MatTypeFlag){
		case i16Flag:
			i16mat_l_add = (int16_t*)mat_l->SaveAddr;
			switch (mat_r->flag&MatTypeFlag){
				case i16Flag:
					i16mat_r_add = (int16_t*)mat_r->SaveAddr;
					for (l_line = 0; l_line < mat_l->line; ++l_line) {
						for (r_row = 0; r_row < mat_r->row; ++r_row) {
							for (adds = 0; adds < mat_r->line; ++adds) {
								*(remat_add + line_offset + r_row) += (float)((float)(*(i16mat_l_add+ l_line_offset+adds))*(float)(*(i16mat_r_add+ r_row_offset+r_row)));
								r_row_offset += mat_r->row;
							}
							r_row_offset = NULL;
						}
						line_offset += remat.row;
						l_line_offset += mat_l->row;
					}
					break;
				case f32Flag:
					f32mat_r_add = (float*)mat_r->SaveAddr;
					for (l_line = 0; l_line < mat_l->line; ++l_line) {
						for (r_row = 0; r_row < mat_r->row; ++r_row) {
							for (adds = 0; adds < mat_r->line; ++adds) {
								*(remat_add + line_offset + r_row) += (float)((float)(*(i16mat_l_add + l_line_offset + adds))*(float)(*(f32mat_r_add + r_row_offset + r_row)));
								r_row_offset += mat_r->row;
							}
							r_row_offset = NULL;
						}
						line_offset += remat.row;
						l_line_offset += mat_l->row;
					}
					break;
			default:
				break;
			}
			break;
		case f32Flag:
			f32mat_l_add = (float*)mat_l->SaveAddr;
			switch (mat_r->flag&MatTypeFlag) {
			case i16Flag:
				i16mat_r_add = (int16_t*)mat_r->SaveAddr;
				for (l_line = 0; l_line < mat_l->line; ++l_line) {
					for (r_row = 0; r_row < mat_r->row; ++r_row) {
						for (adds = 0; adds < mat_r->line; ++adds) {
							*(remat_add + line_offset + r_row) += (float)((float)(*(f32mat_l_add + l_line_offset + adds))*(float)(*(i16mat_r_add + r_row_offset + r_row)));
							r_row_offset += mat_r->row;
							printf("1");
						}
						r_row_offset = NULL;
					}
					line_offset += remat.row;
					l_line_offset += mat_l->row;
				}
				break;
			case f32Flag:
				f32mat_r_add = (float*)mat_r->SaveAddr;
				for (l_line = 0; l_line < mat_l->line; ++l_line) {
					for (r_row = 0; r_row < mat_r->row; ++r_row) {
						for (adds = 0; adds < mat_r->line; ++adds) {
							*(remat_add + line_offset + r_row) += (float)((float)(*(f32mat_l_add + l_line_offset + adds))*(float)(*(f32mat_r_add + r_row_offset + r_row)));
							r_row_offset += mat_r->row;
						}
						r_row_offset = NULL;
					}
					line_offset += remat.row;
					l_line_offset += mat_l->row;
				}
				break;
			default:
				break;
			}
			break;
	default:
		break;
	}
	return remat;
}

//�Ż�����:0
//��ӡ������Ϣ
//mat:�������
//return:λ��8��־λ
uint8_t mat_message(const MatStr *mat)
{
	if (mat->SaveAddr == NULL) {
		return false;
	}
#ifdef Simulation
	printf("�����ŵ�ַ = %x\n", (int)mat->SaveAddr);
	if ((mat->flag&MatTypeFlag) == i16Flag) {
		printf("�������� = int16_t\n");
	}
	else {
		printf("�������� = float\n");
	}
	printf("line = %d\n",mat->line);
	printf("row  = %d\n",mat->row);
	printf("\n");
#else
//��ӡ����
#endif // Simulation
	return true;
}