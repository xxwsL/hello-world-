#include "matrix_ot.h"

MatFistr mat_tf = MatFiInit;

//�Ż�����:4
//���float�;���
//mat:����
//return:λ��8��־λ
bool output(const MatStr *mat)		
{
	uint16_t i = 0, j = 0;								//�к��е�ַƫ����
	float* f32add;										//float���;���ָ��
	int16_t* i16add;									//int16_t����ָ��
	if (mat == NULL) {
		return false;
	}
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
		default:
			return false;
			break;
	}
	return true;
}

//�Ż�����:3
//�Ѿ����и�ɶ�Ӧ��С
//matrix_a:���и����a
//matrix_b:�и������
//cut_line_szie:�и��г�
//cut_row_size :�и��г�
//number:�и�Ŀ��λ��
//return:����ṹ��(�ڴ���������ڴ�,û���ͷ�)
MatStr* mat_cut(const MatStr *mat,uint16_t cut_line_size, uint16_t cut_row_size, uint16_t number, uint16_t remat_type)
{
	uint16_t  i = NULL,j=NULL;
	uint16_t  rows_max=NULL;
	int16_t   *i16mat_add=NULL, *i16remat=NULL;
	float	  *f32mat_add=NULL, *f32remat=NULL;
	MatStr *remat=NULL;
	if (mat == NULL) {
		return false;
	}
	if (cut_line_size <= mat->line || cut_row_size <= mat->row) {
		rows_max = mat->row / cut_row_size;
		switch (mat->flag&MatTypeFlag) {
		case i16Flag:					//�и�int16_t����
			i16mat_add = (int16_t*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//��ʼ�и��ַ
			switch (remat_type)
			{
				case i16Flag:			//����int16_t����
					remat = mat_create(cut_line_size, cut_row_size,i16Flag);
					i16remat =(int16_t*)remat->SaveAddr;				
					for (i = 0; i < cut_line_size; i++) {
						for (j = 0; j < cut_row_size; j++) {
							*(i16remat++) = (int16_t)(*(i16mat_add + j));
						}
						i16mat_add += mat->row;
					}
					remat->flag = i16Flag;
					break;
				case f32Flag:			//����float����
					remat = mat_create(cut_line_size, cut_row_size, f32Flag);
					f32remat = (float*)remat->SaveAddr;
					for (i = 0; i < cut_line_size; i++) {
						for (j = 0; j < cut_row_size; j++) {
							*(f32remat++) = (float)(*(i16mat_add + j));
						}
						i16mat_add += mat->row;
					}
					remat->flag = f32Flag;
					break;
				break;
			default:
				return false;
				break;
			}
			break;
		case f32Flag:					//�и�float����
			f32mat_add = (float*)mat->SaveAddr + (number / rows_max*cut_line_size*mat->row) + (number%rows_max*cut_row_size);	//��ʼ�и��ַ
			switch (remat_type)
			{
			case i16Flag:				//����int16_t����
				remat = mat_create(cut_line_size, cut_row_size, i16Flag);
				i16remat = (int16_t*)remat->SaveAddr;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(i16remat++) = (int16_t)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat->flag = i16Flag;
				break;					//����float����
			case f32Flag:
				remat = mat_create(cut_line_size, cut_row_size, f32Flag);
				f32remat = (float*)remat->SaveAddr;
				for (i = 0; i < cut_line_size; i++) {
					for (j = 0; j < cut_row_size; j++) {
						*(f32remat++) = (float)(*(f32mat_add + j));
					}
					f32mat_add += mat->row;
				}
				remat->flag = f32Flag;
				break;
				break;
			default:
				return false;
				break;
			}
			break;
		default:
			return false;
			break;
		}
	}
	return remat;
}

//�Ż�����:2
//�����Э����		
//����:��������(������������1),����:����ά��
//mat:�������
//
MatStr* mat_cov(const MatStr *mat)
{
	uint16_t i = 0, j = 0,k=0;
	int16_t *i16mat_add;
	uint32_t line_offset=0,diff_mat_line=0;
	MatStr *remat,*aver_mat,*diff_mat;
	float *f32mat_add;
	if (!mat) {
		return false;
	}
	remat = mat_create(mat->row,mat->row,f32Flag);		//�����ڴ��ע���С����
	mat_zero(remat);
	aver_mat = mat_create(1, mat->row, f32Flag);			//ע�⣬ע�⣬ע��
	mat_zero(aver_mat);
	diff_mat = mat_create(mat->line,mat->row,f32Flag);
	switch (mat->flag&MatTypeFlag){	
		case i16Flag:										//����int16_t����
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//������ͬά���ܺ�
				for (j = 0; j < mat->row; j++) {
					*((float*)aver_mat->SaveAddr + j) +=(float)(*(i16mat_add++));		
				}
			}
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//������ͬά�Ⱦ�ֵ
				*((float*)aver_mat->SaveAddr + j) /= mat->line;
			}
			for (i = 0; i < mat->line; i++) {				//��������
				for (j = 0; j < mat->row; j++) {
					*((float*)diff_mat->SaveAddr + line_offset + j) = (*(i16mat_add++)) - (*((float*)aver_mat->SaveAddr + j));
				}
				line_offset += mat->row;
			}
			break;
		case f32Flag:										//����float����
			f32mat_add = (float*)mat->SaveAddr;
			for (i = 0; i < mat->line; i++) {				//������ͬά���ܺ�
				for (j = 0; j < mat->row; j++) {
					*((float*)aver_mat->SaveAddr + j) = (*((float*)aver_mat->SaveAddr + j)) + (float)(*(f32mat_add++));
				}
			}
			f32mat_add = (float*)mat->SaveAddr;
			for (j = 0; j < mat->row; j++) {				//������ͬά�Ⱦ�ֵ
				*((float*)aver_mat->SaveAddr + j) /= mat->line;;
			}
			for (i = 0; i < mat->line; i++) {				//��������
				for (j = 0; j < mat->row; j++) {
					*((float*)diff_mat->SaveAddr + line_offset + j) = (*(f32mat_add++)) - (*((float*)aver_mat->SaveAddr + j));
				}
				line_offset += mat->row;
			}
			break;
		default:return false;
		break;
	}
	line_offset = 0;
	for (i = 0; i < mat->row;i++) {							//�����ά��֮��Э����		
		for (j = i; j < mat->row; j++) {
			for (k = 0; k < mat->line; k++) {
				*((float*)remat->SaveAddr + line_offset + j) += (*((float*)diff_mat->SaveAddr +i+ diff_mat_line))*(*((float*)diff_mat->SaveAddr +j+ diff_mat_line));
				diff_mat_line += mat->row;
			}
			diff_mat_line = 0;
			(*((float*)remat->SaveAddr + line_offset + j)) /= (mat->line - 1);
			if (i != j) {
				*((float*)remat->SaveAddr + j*mat->row + i) = (*((float*)remat->SaveAddr + line_offset + j));
			}
		}
		line_offset += mat->row;
	}
	mat_delete(aver_mat);
	mat_delete(diff_mat);
	return remat;
}

//�Ż�����:0
//��������(�����ڴ�Ƭ���ֵӲ�����ֵ,���ʼ��0)
//mat_line:��������
//mat_row:��������
//mat_type:��������
//return:����ṹ��
MatStr* mat_create(uint16_t mat_line, uint16_t mat_row, uint16_t mat_type)
{
	int16_t *i16add;
	float *f32add;
	MatStr *create_mat;
#ifdef Simulation		//����ģʽ
	 create_mat= (MatStr*)malloc(sizeof(MatStr));
#else
//�ڴ����ģ��
#endif 
	switch (mat_type&MatTypeFlag){
		case i16Flag:
#ifdef Simulation		//����ģʽ
			i16add = (int16_t*)malloc(mat_line*mat_row*2);
#else
//�ڴ����ģ��
#endif 
			if ((i16add != NULL)&&(create_mat!=NULL)) {		//�����ڴ���
				create_mat->SaveAddr = i16add;
				create_mat->flag = i16Flag;
			}
			else {						//�����ڴ�ʧ��
				return false;
			}
			break;
		case f32Flag:
#ifdef Simulation		//����ģʽ
			f32add = (float*)malloc(mat_line*mat_row * 4);
#else
//�ڴ����ģ��
#endif 		
			if ((f32add != NULL) && (create_mat != NULL)) {
				create_mat->SaveAddr = f32add;
				create_mat->flag = f32Flag;
			}
			else {
				return false;
			}
			break;
	default:
		return false;
		break;
}
	create_mat->line = mat_line;		//�����С��ֵ
	create_mat->row  = mat_row;
	return create_mat;
}

//�Ż�����:1
//ɾ�������ͷž����ڴ�
//mat:Ҫ�ͷŵľ���ָ��
//return:λ��8��־λ
bool mat_delete(MatStr *mat)
{
	if (mat == NULL) {
		return false;
	}
	switch (mat->flag&MatTypeFlag)
	{
		case i16Flag:
#ifdef Simulation		//����ģʽ
			free((int16_t*)mat->SaveAddr);
			mat->SaveAddr = NULL;
			free(mat);
			mat = NULL;
#else
//�ڴ����ģ��
#endif // Simulation
			break;
		case f32Flag:
#ifdef Simulation		//����ģʽ
			free((float*)mat->SaveAddr);
			mat->SaveAddr = NULL;
			free(mat);
			mat = NULL;
#else
//�ڴ����ģ��
#endif // Simulation
			break;
	default:
		return false;
		break;
	}
	return true;
}

//�Ż�����:1
//����ȫԱ��ֵvalue
//mat:���븳ֵ����
//value:��Чֵ
//return:λ��8��־λ
bool mat_assignment(MatStr *mat,float value)
{
	int16_t *i16add=NULL;
	float *f32add=NULL;
	uint32_t i=0,mat_size=0;
	mat_size = mat->line*mat->row;
	if (!mat){			//�����ַ�ʹ�С����Ϊ0
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

//�Ż�����:1
//����ȫԱ��ֵ0
//mat:���븳ֵ����
//return:λ��8��־λ
bool mat_zero(MatStr *mat)
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
	if (!mat) {
		return false;
	}
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
	mat_size=mat_tf.mat_size(mat);
	if (!mat) {
		return false;
	}
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
MatStr* mat_mult(const MatStr *mat_l,const MatStr *mat_r)
{
	uint16_t l_line = NULL, r_row = NULL, adds = NULL, l_line_offset=NULL,r_row_offset=NULL;
	int16_t *i16mat_l_add=NULL,*i16mat_r_add=NULL;
	float *f32mat_l_add = NULL, *f32mat_r_add = NULL,*remat_add=NULL;
	uint32_t line_offset = NULL;
	MatStr *remat;
	if((mat_l->SaveAddr==NULL)||(mat_r->SaveAddr==NULL)||(mat_l->row!=mat_r->line)){		//�վ���and��˾����в������ҳ˾��󷵻ؿվ���
		remat=mat_create(NULL,NULL,NULL);
		return remat;
	}
	remat = mat_create(mat_l->line,mat_r->row,f32Flag);		//Ϊ���ؾ��󿪱��ڴ�
	mat_zero(remat);
	remat_add = (float*)remat->SaveAddr;
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
						line_offset += remat->row;
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
						line_offset += remat->row;
						l_line_offset += mat_l->row;
					}
					break;
			default:
				return false;
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
						}
						r_row_offset = NULL;
					}
					line_offset += remat->row;
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
					line_offset += remat->row;
					l_line_offset += mat_l->row;
				}
				break;
			default:
				return false;
				break;
			}
			break;
	default:
		return false;
		break;
	}
	return remat;
}

//�Ż�����:0
//�������
//mat_l:��˾���l
//mat_r:�ҳ˾���r
//loadmat:װ�ؾ���
//return:bool��־λ
bool mat_mult_par(const MatStr *mat_l, const MatStr *mat_r,MatStr *loadmat)
{
	uint16_t l_line = NULL, r_row = NULL, adds = NULL, l_line_offset = NULL, r_row_offset = NULL;
	int16_t *i16mat_l_add = NULL, *i16mat_r_add = NULL;
	float *f32mat_l_add = NULL, *f32mat_r_add = NULL, *remat_add = NULL;
	uint32_t line_offset = NULL;
	if ((!mat_l) || (!mat_r)||(!loadmat)) {		//�վ���and��˾����в������ҳ˾��󷵻ؿվ���
		return false;
	}
	if ((mat_l->row != mat_r->line)||(mat_l->line!=loadmat->line)||(mat_r->row!=loadmat->row)) {
		return false;
	}
	mat_zero(loadmat);
	remat_add = (float*)loadmat->SaveAddr;
	switch (mat_l->flag&MatTypeFlag) {
	case i16Flag:
		i16mat_l_add = (int16_t*)mat_l->SaveAddr;
		switch (mat_r->flag&MatTypeFlag) {
		case i16Flag:
			i16mat_r_add = (int16_t*)mat_r->SaveAddr;
			for (l_line = 0; l_line < mat_l->line; ++l_line) {
				for (r_row = 0; r_row < mat_r->row; ++r_row) {
					for (adds = 0; adds < mat_r->line; ++adds) {
						*(remat_add + line_offset + r_row) += (float)((float)(*(i16mat_l_add + l_line_offset + adds))*(float)(*(i16mat_r_add + r_row_offset + r_row)));
						r_row_offset += mat_r->row;
					}
					r_row_offset = NULL;
				}
				line_offset += loadmat->row;
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
				line_offset += loadmat->row;
				l_line_offset += mat_l->row;
			}
			break;
		default:
			return false;
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
					}
					r_row_offset = NULL;
				}
				line_offset += loadmat->row;
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
				line_offset += loadmat->row;
				l_line_offset += mat_l->row;
			}
			break;
		default:
			return false;
			break;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

//�Ż�����:1
//��ӡ������Ϣ
//mat:�������
//return:λ��8��־λ
bool mat_message(const MatStr *mat)
{
	if (!mat) {
		return false;
	}
#ifdef Simulation
	printf("�����ŵ�ַ = %x\n", mat->SaveAddr);
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

//�Ż�����:0
//����QR�ֽ�
//mat:�������
//q_mat:�ֽ����q
//r_mat:�ֽ����r
//return:bool��־λ
bool mat_qr(const MatStr *mat,MatStr *q_mat,MatStr *r_mat)			//debug
{
	uint16_t i = NULL, j = NULL, k = NULL,m=NULL;
	int16_t *mat_i16add=NULL;
	float *buf_a = NULL, *buf_b = NULL,temp=NULL;
	float *mat_f32add=NULL,*q_f32add=NULL,*r_f32add=NULL;
	MatStr *qmat,*rmat,b_mat;
	if (mat == NULL) {
		return false;
	}
#ifdef Simulation
	buf_a = (float*)malloc(mat->line*4);
	buf_b = (float*)malloc(mat->line * 4);
#else
#endif 
	qmat = mat_create(mat->line,mat->row,f32Flag);
	rmat = mat_create(mat->row, mat->row, f32Flag);
	q_f32add = (float*)qmat->SaveAddr;
	r_f32add = (float*)rmat->SaveAddr;
	mat_zero(rmat);
	mat_load(&b_mat,mat->line,1,f32Flag,buf_b);
	switch (mat->flag&MatTypeFlag){
		case i16Flag:
			mat_i16add = (int16_t*)(mat->SaveAddr);
			for (j = 0; j < mat->line; ++j){
				for (i = 0; i < mat->line; ++i){
					buf_a[i] = buf_a[i]= mat_i16add[i * mat->row + j];
				}
				for (k = 0; k < j; ++k)
				{
					r_f32add[k * rmat->row + j] = 0;
					for (m = 0; m < mat->line; ++m){
						r_f32add[k * rmat->row + j] += buf_a[m] * q_f32add[m * qmat->row + k];
					}
					for (m = 0; m < mat->line; ++m){
						buf_b[m] -= r_f32add[k * rmat->row + j] * q_f32add[m * qmat->row + k];
					}
				}
				temp = mat_norm2(&b_mat);
				r_f32add[j * rmat->row + j] = temp;

				for (i = 0; i < mat->line; ++i){
					q_f32add[i * qmat->row + j] = buf_b[i] / temp;
				}
			}
			break;
		case f32Flag:
			mat_f32add = (float*)(mat->SaveAddr);
			for (j = 0; j < mat->line; ++j) {
				for (i = 0; i < mat->line; ++i) {
					buf_a[i] = buf_b[i] = mat_f32add[i * mat->row + j];
				}
				for (k = 0; k < j; ++k)
				{
					r_f32add[k * rmat->row + j] = 0;
					for (m = 0; m < mat->line; ++m) {
						r_f32add[k * rmat->row + j] += buf_a[m] * q_f32add[m * qmat->row + k];
					}
					for (m = 0; m < mat->line; ++m) {
						buf_b[m] -= r_f32add[k * rmat->row + j] * q_f32add[m * qmat->row + k];
					}
				}
				temp = mat_norm2(&b_mat);
				r_f32add[j * rmat->row + j] = temp;

				for (i = 0; i < mat->line; ++i) {
					q_f32add[i * qmat->row + j] = buf_b[i] / temp;
				}
			}
			break;
	default:
		return false;
		break;
	}
#ifdef Simulation
	free(buf_a);
	buf_a = NULL;
	free(buf_b);
	buf_b = NULL;
#else
#endif 
	return true;
}

//�Ż�����:0
//����ӷ�
//q_mat:���float����a
//r_mat:�Ҽ�float����b
//return:float�;���
MatStr* mat_add(const MatStr *mat_a,const MatStr *mat_b)
{
	uint32_t i=NULL,matsize=NULL;
	float *f32mata_add = NULL, *f32matb_add = NULL,*f32remat_add;
	MatStr *remat;
	if ((!mat_a) || (!mat_b))
		return false;
	if ((mat_a->line != mat_b->line) || (mat_a->row != mat_b->row))
		return false;
	matsize = mat_size(mat_a);
	f32mata_add = (float*)mat_a->SaveAddr;
	f32matb_add = (float*)mat_b->SaveAddr;
	remat=mat_create(mat_a->line,mat_a->row,f32Flag);
	f32remat_add = (float*)remat->SaveAddr;
		for (i = 0; i <matsize; ++i) {
		*(f32remat_add + i) = *(f32mata_add + i) + (*(f32matb_add + i));
	}
	return remat;
}

//�Ż�����:0
//�������
//q_mat:���float����a
//r_mat:�Ҽ�float����b
//return:float�;���
MatStr* mat_sub(const MatStr *mat_a, const MatStr *mat_b)
{
	uint32_t i = NULL, matsize = NULL;
	float *f32mata_add = NULL, *f32matb_add = NULL, *f32remat_add;
	MatStr *remat;
	if ((!mat_a) || (!mat_b))
		return false;
	if ((mat_a->line != mat_b->line) || (mat_a->row != mat_b->row))
		return false;
	matsize = mat_size(mat_a);
	f32mata_add = (float*)mat_a->SaveAddr;
	f32matb_add = (float*)mat_b->SaveAddr;
	remat = mat_create(mat_a->line, mat_a->row, f32Flag);
	f32remat_add = (float*)remat->SaveAddr;
	for (i = 0; i <matsize; ++i) {
		*(f32remat_add + i) = *(f32mata_add + i) - (*(f32matb_add + i));
	}
	return remat;
}

//�Ż�����:0
//�������
//q_mat:���float����a
//r_mat:�Ҽ�float����b
//loadmat:�������
//return:bool�ͱ�־
bool mat_sub_par(const MatStr *mat_a, const MatStr *mat_b,MatStr *loadmat)
{
	uint32_t i = NULL, matsize = NULL;
	float *f32mata_add = NULL, *f32matb_add = NULL, *f32remat_add;
	if ((!mat_a) || (!mat_b)||(!loadmat))
		return false;
	if ((mat_a->line != mat_b->line) || (mat_a->row != mat_b->row))
		return false;
	matsize = mat_size(mat_a);
	f32mata_add = (float*)mat_a->SaveAddr;
	f32matb_add = (float*)mat_b->SaveAddr;
	f32remat_add = (float*)loadmat->SaveAddr;
	for (i = 0; i <matsize; ++i) {
		*(f32remat_add + i) = *(f32mata_add + i) - (*(f32matb_add + i));
	}
	return true;
}

//�Ż�����:0
//����ת��
//mat:�������
//return:����������෴���;���
MatStr* mat_change(const MatStr *mat)
{
	uint32_t i = NULL, matsize = NULL;
	int16_t *i16mat_add = NULL,*i16remat_add=NULL;
	float *f32mat_add=NULL,*f32remat_add=NULL;
	MatStr *remat;
	if (!mat->SaveAddr)
		return false;
	matsize = mat_size(mat);
	switch (mat->flag&MatTypeFlag){
		case i16Flag:
			i16mat_add = (int16_t*)mat->SaveAddr;
			remat = mat_create(mat->line, mat->row, f32Flag);
			f32remat_add = (float*)remat->SaveAddr;
			for (i = 0; i < matsize; ++i) {
				*(f32remat_add + i) = (float)(*(i16mat_add+i));
			}
			break;
		case f32Flag:
			f32mat_add = (float*)mat->SaveAddr;
			remat = mat_create(mat->line, mat->row, i16Flag);
			i16remat_add = (int16_t*)remat->SaveAddr;
			for (i = 0; i < matsize; ++i) {
				*(f32remat_add + i) = (int16_t)(*(i16mat_add + i));
			}
			break;
	default:
		return false;
		break;
	}
	return remat;
}

//�Ż�����:0
//����signmoid������
//mat:�����������;���
//return:float�;���
MatStr* mat_signmoid(const MatStr *mat)
{
	uint16_t lines = NULL, rows = NULL;
	int16_t *i16mat_add = NULL;
	float *f32mat_add = NULL,*f32remat_add=NULL;
	MatStr *remat;
	if (!mat)
		return false;
	remat = mat_create(mat->line,mat->row,f32Flag);
	f32remat_add = (float*)remat->SaveAddr;
	switch (mat->flag&MatTypeFlag){
		case i16Flag:
			i16mat_add = (int16_t*)mat->SaveAddr;
			for (lines = 0; lines < mat->line; ++lines) {
				for (rows = 0; rows < mat->row; ++rows) {
					*(f32remat_add++) = signmoid((float)*(i16mat_add++));
				}
			}
			break;
		case f32Flag:
			f32mat_add = (float*)mat->SaveAddr;
			for (lines = 0; lines < mat->line; ++lines) {
				for (rows = 0; rows < mat->row; ++rows) {
					*(f32remat_add++) = signmoid(*(f32mat_add++));
				}
			}
			break;
	default:
		return false;
		break;
	}
	return remat;
}

//�Ż�����:0
//����signmoid������
//mat:�����������;���
//return:bool��־λ
//loadmat:װ�ؾ���
bool mat_signmoid_par(const MatStr *mat,MatStr *loadmat)
{
	uint16_t lines = NULL, rows = NULL;
	int16_t *i16mat_add = NULL;
	float *f32mat_add = NULL, *f32remat_add = NULL;
	if (!mat_proofread(mat,loadmat))
		return false;
	f32remat_add = (float*)loadmat->SaveAddr;
	switch (mat->flag&MatTypeFlag) {
	case i16Flag:
		i16mat_add = (int16_t*)mat->SaveAddr;
		for (lines = 0; lines < mat->line; ++lines) {
			for (rows = 0; rows < mat->row; ++rows) {
				*(f32remat_add++) = signmoid((float)*(i16mat_add++));
			}
		}
		break;
	case f32Flag:
		f32mat_add = (float*)mat->SaveAddr;
		for (lines = 0; lines < mat->line; ++lines) {
			for (rows = 0; rows < mat->row; ++rows) {
				*(f32remat_add++) = signmoid(*(f32mat_add++));
			}
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

//�Ż�����:0
//��һ������װ�ص�������
//mat:������ݵľ�����
//line:������г�
//row:������г�
//mattype:���������
//���ݵ�ַ
bool mat_load(MatStr *mat,uint16_t line,uint16_t row, uint16_t mattype, void *saveadd)
{
	if ((!mat)||(mat->SaveAddr))
		return false;
	mat->flag = mattype;
	mat->line = line;
	mat->row = row;
	mat->SaveAddr = saveadd;
	return true;
}

//�Ż�����:0
//��������У��
//mat_a:�������a
//mat_b:�������b
//return:bool�ͱ�־λ
bool mat_proofread(const MatStr *mat_a, const MatStr *mat_b)
{
	if (!(mat_a&&mat_b))
		return false;
	if ((mat_a->line == mat_b->line) && (mat_a->row == mat_b->row))
		return true;
	else
		return false;
}

//�Ż�����:0
//������and���
//mat_l:���������
//mat_r:���������
//loadmat:�������,����Ϊ0������
//return:float�ͱ�־������
float f32mat_dotmult_par(const MatStr *mat_l,const MatStr *mat_r,MatStr *loadmat)
{
	float *mat_ladd = NULL, *mat_radd = NULL, *loadmat_add = NULL, redate=NULL;
	uint32_t i=NULL,matsize=NULL;
	if ((mat_l->line != mat_r->line) || (mat_l->row != mat_r->row))
		return false;
	matsize = mat_size(mat_l);
	if (!loadmat){
		mat_ladd = (float*)mat_l->SaveAddr;
		mat_radd = (float*)mat_r->SaveAddr;
		for (i = 0; i < matsize; ++i) {
			redate += (*(mat_ladd++))*(*(mat_radd)++);
		}
		return redate;
	}
	else {
		mat_ladd = (float*)mat_l->SaveAddr;
		mat_radd = (float*)mat_r->SaveAddr;
		loadmat_add = (float*)loadmat->SaveAddr;
		for (i = 0; i < matsize; ++i) {
			*(loadmat_add++) = (*(mat_ladd++))*(*(mat_radd)++);
		}
	}
	return true;
}

//�Ż�����:0
//��һ��8byte�����������ÿһλ��Ӧת��Ϊһ������
//buf:�����ַ
//loadmat:װ�ؾ������
//return:bool�ͱ�־
bool mat_tovector(const uint8_t *buf,MatStr *loadmat)
{
	float l_value = 0.0f,r_value=0.1f;
	float *loadmatadd = NULL;
	uint16_t j = NULL;
	uint32_t i = NULL;
	if (!loadmat)
		return false;
	loadmatadd = (float*)loadmat->SaveAddr;
	for (i = 0; i < loadmat->line;++i) {
		*(loadmatadd + i) = (*(buf + j) & 0x01) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x02) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x04) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x08) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x10) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x20) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x40) ? l_value : r_value;
		i++;
		*(loadmatadd + i) = (*(buf + j) & 0x80) ? l_value : r_value;
		j++;
	}
	return true;
}

//�Ż�����:0
//����tanh������
//mat:�����������;���
//return:bool��־λ
//loadmat:װ�ؾ���
bool mat_tanh_par(const MatStr *mat, MatStr *loadmat)
{
	uint16_t lines = NULL, rows = NULL;
	float *f32mat_add = NULL, *f32remat_add = NULL;
	if (!mat_proofread(mat, loadmat))
		return false;
	f32mat_add = (float*)mat->SaveAddr;
	for (lines = 0; lines < mat->line; ++lines) {
		for (rows = 0; rows < mat->row; ++rows) {
			*(f32remat_add++) = (float)tanh(*(f32mat_add++));
		}
	}
	return true;
}


//�Ż�����:0
//����relu������
//mat:�������
//loadmat:װ�ؾ���
bool mat_relu_par(const MatStr *mat,MatStr *loadmat)
{
	uint16_t lines = NULL, rows = NULL;
	float *f32mat_add = NULL, *f32remat_add = NULL;
	if (!mat_proofread(mat, loadmat))
		return false;
	f32remat_add = (float*)loadmat->SaveAddr;
		f32mat_add = (float*)mat->SaveAddr;
		for (lines = 0; lines < mat->line; ++lines) {
			for (rows = 0; rows < mat->row; ++rows) {
				*(f32remat_add++) = relu(*(f32mat_add++));
			}
		}
	return true;
}


//�Ż�����:0
//��������̬�����ֵ
//mat:�������
bool mat_rand_normal(MatStr *mat)
{
	float *f32add = NULL,temp=NULL,tempsum=NULL;
	uint32_t i = 0, mat_size = 0;
	if (!mat) {			//�����ַ�ʹ�С����Ϊ0
		return false;
	}
	mat_size = mat->line*mat->row;
	f32add = (float*)mat->SaveAddr;
		for (i = 0; i < mat_size; ++i) {
			temp = (float)rand();
			tempsum += temp;
			*(f32add + i) = temp;
		}
		temp = tempsum / i;
		for (i = 0; i < mat_size; ++i) {
			f32add[i] = (f32add[i]-temp)/tempsum*100;
		}
	return true;
}


//�Ż�����:0
//��������Ԫ��ƫ��һ��ֵ
//mat:����һ������
//value:ƫ��ֵ
bool mat_addto_value(MatStr *mat, const float value)
{
	float *matadd = NULL;
	uint32_t matszie = NULL,i=NULL;
	if (!mat)
		return false;
	matszie = mat_size(mat);
	matadd = (float*)mat->SaveAddr;
	for (i = 0; i < matszie; ++i) {
		matadd[i] += value;
	}
	return true;
}

//�Ż�����:0
//����softmax��
//mat:�������
//loadmat:װ�ؾ���
bool mat_softmax(const MatStr *mat,MatStr *loadmat) 
{
	uint32_t i = NULL, matszie = NULL;
	float exp_pow_sum = NULL;
	float *f32mat_add = NULL, *f32loadmat_add = NULL;
	if (!mat_proofread(mat, loadmat))
		return false;
	matszie = mat_size(mat);
	f32mat_add = (float*)mat->SaveAddr;
	f32loadmat_add = (float*)loadmat->SaveAddr;
	for (i = 0; i < matszie; ++i) {
		f32loadmat_add[i] = exp_pow(f32mat_add[i]);
		exp_pow_sum += f32loadmat_add[i];
		}
	for (i = 0; i < matszie; ++i) {
		f32loadmat_add[i] /= exp_pow_sum;
	}
	return true;
}

//�Ż�����:0
//����s����Ԫ�����
//mat:�������
//return:double����
double mat_element_sum(const MatStr *mat)
{
	uint32_t i = NULL,matsize=NULL;
	double sum = NULL;
	float *f32mat_add = NULL;
	if (!mat)
		return false;
	matsize = mat_size(mat);
	f32mat_add = (float*)mat->SaveAddr;
	for (i = 0; i < matsize; ++i) {
			sum += (double)f32mat_add[i];
		}
	return sum;
}

//�Ż�����:0
//����softmax��
//mat:�������
//loadmat:װ�ؾ���
//addr:��λ��
//return:bool��־λ
bool mat_softmax_der(MatStr *mat,MatStr *loadmat,uint32_t addr)
{
	uint32_t i = NULL, matsize = NULL;
	float *mataddr = NULL, *loadmataddr = NULL;
	if (mat_proofread(mat, loadmat)) {
		return true;
		mataddr = (float*)mat->SaveAddr;
		loadmataddr = (float*)loadmat->SaveAddr;
		matsize = mat_size(mat);
		for (i = 0; i < matsize; ++i) {
			loadmataddr[i] = (i == addr) ? (mataddr[i] - 1) : mataddr[i];
		}
		return true;
	}
	return false;
}











































