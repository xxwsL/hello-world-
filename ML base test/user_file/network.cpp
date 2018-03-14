#include "network.h"

//�Ż�����:0
//����ѵ��ģ��,���ڷ��򴫲��㷨
//mat:������������
//hide_network_mat:Ӱ�ز����
//out_network_mat:��������
//target_mat:�����������
bool back_propaga(const MatStr *mat,MatStr *hide_network_mat,MatStr *out_nework_mat,const MatStr *target_mat,float learm_speed)
{
	float error_total = NULL,out_network_dersum=NULL;
	float *out_matadd = NULL, *error_matadd = NULL, *out_nework_matadd = NULL, *neth_matadd = NULL, *error_der = NULL;
	float *hide_network_matadd = NULL,*matadd=NULL;
	uint32_t i=NULL,j=NULL, offset0 =NULL,offset1=NULL,update=NULL;
	MatStr *neth_mat=NULL,*out_mat=NULL,*error_mat=NULL;
	neth_mat = mat_create(hide_network_mat->line, mat->row, f32Flag);
	out_mat = mat_create(target_mat->line, target_mat->row, f32Flag);
	error_mat= mat_create(target_mat->line, target_mat->row, f32Flag);
#ifdef Simulation
	error_der = (float*)malloc(target_mat->line*4);
#else
#endif // Simulation
	if (!(out_mat&&error_mat&&neth_mat&&error_der))
		return false;
	matadd = (float*)mat->SaveAddr;
	hide_network_matadd = (float*)hide_network_mat->SaveAddr;
	neth_matadd = (float*)neth_mat->SaveAddr;
	out_matadd = (float*)out_mat->SaveAddr;
	error_matadd = (float*)error_mat->SaveAddr;
	out_nework_matadd = (float*)out_nework_mat->SaveAddr;
	while (true){
		mat_mult_par(hide_network_mat, mat, neth_mat);										//�����*���ز�=neth��
		mat_signmoid_par(neth_mat, neth_mat);												//neth�㾭��signmoid����ѹ��
		mat_mult_par(out_nework_mat, neth_mat, out_mat);									//out_neth*�����=out_mat
		mat_signmoid_par(out_mat,out_mat);													//out_neth����signmoid����ѹ��
		output(out_mat);//��ӡ����
		mat_sub_par(target_mat, out_mat, error_mat);

		error_total = f32mat_dotmult_par(error_mat, error_mat, NULL);
		printf("��� = %f\n",error_total);
		//break;
		if (error_analysis(error_total)) {
			printf("ģ��ѵ�����\n");
			break;
		}

		offset0 = NULL;offset1 = NULL;
		for (i = 0; i < out_nework_mat->line; ++i) {													//������������
			*(error_der +i) = (-(*(error_matadd + i)))*signmoid_der(*(out_matadd+i));					//error_der=-(traget_i-out_i)*outi(1-out_i)
		}																
		for (i = 0; i < neth_mat->line; ++i) {															//�������ز�Ȩ��				
			for (j = 0; j < out_nework_mat->line;++j) {
				out_network_dersum += (*(error_der + j))*(*(out_nework_matadd + offset1 + i));			//out_dersum+=error_der*Wout_network
				offset1 += out_nework_mat->row;
			}
			offset1 = 0;
			out_network_dersum = out_network_dersum*signmoid_der(*(neth_matadd + i));					//out_dersum=out_dersum*net_o(1-net_o)		
			for (j = 0; j < hide_network_mat->row;++j) {
				*(hide_network_matadd + offset0 + j) -= learm_speed*out_network_dersum*(*(matadd + j));	//hide_network_j=learm_speed*outdersum*mat_j
			}
			offset0 += hide_network_mat->row;
			out_network_dersum = NULL;
		}																					//�������ز����
		for (i = 0; i < out_nework_mat->line; ++i) {										//���������Ȩ��
			for (j = 0; j < out_nework_mat->row; ++j) {
				*(out_nework_matadd + offset1 + j) -= learm_speed*(*(error_der +i))*(*(neth_matadd + j));
			}
			offset1 += out_nework_mat->row;
		}																					//������������
		printf("�������� = %d\n\n", update++);
	}
	return true;
}

//�Ż�����:0
//������
//error_value:���ֵ
//return:bool��־λ
bool error_analysis(float error_value)
{
	if (error_value < error_scope)
		return true;
	else
		return false;
}