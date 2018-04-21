#include "mlp.h"

//�Ż�����:5
//ѵ����ʼ��
//tr:ѵ����
//layer:ȫ���Ӳ㼯
//target_set:ѵ��������ǩ��
//tr_message:ѵ��ģ�������Ϣͷ
//tr_fi:ѵ��ģ�ͼ����&�󵼺�����
//return:int��־λ
int mlp_init(mlpstr *mlp, float op, active_fi_str(fi), TensorStr *layer)
{
	int16_t i = NULL;
	//��ʼ�����Ӳ�
	mlp->layer = layer;
	//��ʼ������
	mlp->op = op;
	//��ʼ������
	mlp->active_fi = fi;
	//��ʼ������� & ����̬�ֲ��������ʼ�����ز� & ��ʼ��΢�ֲ�	
		mlp->outmat->mat[0] = mat_create(layer->mat[0]->line, 1, f32Flag);
		mat_rand_normal(mlp->layer->mat[0]);
		mlp->gr_mat->mat[0] = mat_create(mlp->outmat->mat[0]->line, 1, f32Flag);
		//������󵼺���װ��
		if ((void*)mlp->active_fi == (void*)mat_signmoid_par)
			//signmoid
			mlp->active_fid = signmoid_fd;
		else if ((void*)mlp->active_fi == (void*)mat_tanh_par)
			//tanh
			mlp->active_fid = tanh_fd;
		else if ((void*)mlp->active_fi == (void*)mat_relu_par)
			//relu
			mlp->active_fid = relu_fd;
		else if ((void*)mlp->active_fi == (void*)mat_softmax_par)
			//softmax
			mlp->active_fid = softmax_fd;
		else
			mlp->active_fid = NULL;
	return true;
}

//�Ż�����:0
//���ڵ�mlpǰ�����
//mlp:mlp�ڵ�
//inmat:�������
int mlp_one_op(void *mlp_add,TensorStr *inmat)
{
	MlpStr *mlp = (MlpStr*)mlp_add;
	mat_mult_par(mlp->layer->mat[0], inmat->mat[0], mlp->outmat->mat[0]);
	mat_addto_value(mlp->outmat->mat[0], mlp->op);
	mlp->active_fi(mlp->outmat->mat[0], mlp->outmat->mat[0]);
	return true;
}

//�Ż�����:0
//op:ƫ������
//fi:�����
//line:�г�
//row:�г�
//return:MlpStrָ��
//����mlp������
MlpStr *mlp_create(float op, active_fi_str(fi), uint16_t line, uint16_t row)
{
	MlpStr *remlp = NULL;
	//����mlp�ڴ�
	remlp = (MlpStr*)malloc(sizeof(MlpStr));
	if(remlp){
		//������������
		remlp->layer = tensor_create(line, row, 1);
		remlp->outmat = tensor_create(line, 1, 1);
		remlp->gr_mat = tensor_create(line, row, 1);
		//�������ʧ��
		if ((!remlp->layer) || (!remlp->gr_mat) || (!remlp->outmat)) {
			tensor_delete(remlp->layer);
			tensor_delete(remlp->outmat);
			tensor_delete(remlp->gr_mat);
			free(remlp);
			remlp = NULL;
			return false;
		}
		//��ʼ������� & ����̬�ֲ��������ʼ�����ز� & ��ʼ��΢�ֲ�	
		remlp->layer->mat[0] = mat_create(line, row, f32Flag);
		remlp->outmat->mat[0] = mat_create(line, 1, f32Flag);
		remlp->gr_mat->mat[0] = mat_create(line, row, f32Flag); 
		mat_zero(remlp->gr_mat->mat[0]);
		mat_rand_normal(remlp->layer->mat[0]);
		remlp->op = op;
		remlp->active_fi = fi;
		//������󵼺���װ��
		if ((void*)remlp->active_fi == (void*)mat_signmoid_par)
			//signmoid
			remlp->active_fid = signmoid_fd;
		else if ((void*)remlp->active_fi == (void*)mat_tanh_par)
			//tanh
			remlp->active_fid = tanh_fd;
		else if ((void*)remlp->active_fi == (void*)mat_relu_par)
			//relu
			remlp->active_fid = relu_fd;
		else if ((void*)remlp->active_fi == (void*)mat_softmax_par)
			//softmax
			remlp->active_fid = softmax_fd;
		else
			remlp->active_fid = NULL;
	}
	return remlp;
}

//�Ż�����:0
//mlp_add:mlp��ַ
//return:int��־
//content:Ҫ��ӡ������
//��ӡmlp
int mlp_output(void *mlp_add , uint8_t content) 
{
	MlpStr *mlp = (MlpStr*)mlp_add;
	char fi[] = "mlp_fi = " ;
	char fid[] = "mlp_fid = ";
	if (content&_mlp_layer) {
		//��ӡlayer
		cout << "_mlp_layer = " << endl;
		tensor_output(mlp->layer);
	}
	if (content&_mlp_outmat) {
		//��ӡout_mat
		cout << "mlp_out_mat = " << endl;
		tensor_output(mlp->outmat);
	}
	if (content&_mlp_gr_mat) {
		//��ӡgr_mat
		cout << "mlp_gr_mat = " << endl;
		tensor_output(mlp->gr_mat);
	}
	if (content&_mlp_op) {
		//��ӡƫ������
		cout << "mlp_op = " << mlp->op << endl<<endl;
	}
	if (content&_mlp_fi) {
		//������󵼺���װ��
		if ((void*)mlp->active_fi == (void*)mat_signmoid_par)
			//signmoid
			cout << fi << "signmoid" << endl << endl;
		else if ((void*)mlp->active_fi == (void*)mat_tanh_par)
			//tanh
			cout << fi << "tanh" << endl << endl;
		else if ((void*)mlp->active_fi == (void*)mat_relu_par)
			//relu
			cout << fi << "relu" << endl << endl;
		else if ((void*)mlp->active_fi == (void*)mat_softmax_par)
			//softmax
			cout << fi << "softmax" << endl << endl;
		else
			cout << fi << "NULL" << endl << endl;
	}
	if (content&_mlp_fid) {
		//������󵼺���װ��
		if ((void*)mlp->active_fid == (void*)signmoid_fd)
			//signmoid
			cout << fid << "= signmoid_der" << endl << endl;
		else if ((void*)mlp->active_fid == (void*)tanh_fd)
			//tanh
			cout << fid << "tanh_der" << endl << endl;
		else if ((void*)mlp->active_fid == (void*)relu_fd)
			//relu
			cout << fid << "relu_der" << endl << endl;
		else if ((void*)mlp->active_fid == (void*)softmax_fd)
			//softmax
			cout << "fid" << "softmax_der" << endl << endl;
		else
			cout << fid <<  "NULL" << endl << endl;
	}

	return true;
}

//�Ż�����:0
//tensor:��������
//r_mlp:mlp
//�������Ӳ��ݶ�
int mlp_gr(TensorStr *tensor, MlpStr *r_mlp)
{
	uint16_t i = NULL, j = NULL, nums_0 = NULL, nums_1 = NULL;
	uint32_t line_offset0 = NULL;
	float  *mat0 = NULL, *mat1 = NULL, *mat2 = NULL;

	//�ݶȾ�����г�
	nums_0 = r_mlp->gr_mat->mat[0]->line;
	//�ݶȾ�����г�
	nums_1 = r_mlp->gr_mat->mat[0]->row;
	//r_mlp���������ָ��(��Ϊ΢�־���װ����)
	mat0 = (float*)r_mlp->outmat->mat[0]->SaveAddr;
	//��ǰ��layer����ָ��
	mat1 = (float*)tensor->mat[0]->SaveAddr;
	//�ݶȾ�������ָ��
	mat2 = (float*)r_mlp->gr_mat->mat[0]->SaveAddr;
	//�����ݶȾ���
	for (; i < nums_0; ++i) {
		for (; j < nums_1; ++j) {
			mat2[line_offset0 + j] = mat0[i] * mat1[j];
		}
		line_offset0 += nums_1;
	}
	return true;
}

//�Ż�:0
//l_mlp:��ǰmlp��
//r_mlp:��һmlp��
//�������
int mlp_error_pass(MlpStr *l_mlp, MlpStr* r_mlp)
{
	uint16_t  i = NULL, j = NULL, nums_0 = NULL, nums_1 = NULL;
	float *mat_0 = NULL, *mat_1 = NULL, *mat_2 = NULL, sum_temp_0 = NULL;
	uint32_t line_offset0 = NULL;

	//l_mlp���������г�(���µ�������)
	nums_0 = l_mlp->outmat->mat[0]->line;
	//r_mlp���������г�(ÿ����һ�������еļӷ���)
	nums_1 = r_mlp->outmat->mat[0]->line;
	//��ǰ��Ҫ���µ������������
	mat_0 = (float*)l_mlp->outmat->mat[0]->SaveAddr;
	//Ȩ�ؾ���,���ڸ���������
	mat_1 = (float*)r_mlp->layer->mat[0]->SaveAddr;
	//��һ������������
	mat_2 = (float*)r_mlp->outmat->mat[0]->SaveAddr;
	//��ǰ����㼤����󵼹���
	l_mlp->active_fid(l_mlp->outmat->mat[0],l_mlp->outmat->mat[0],NULL);
	//���²��������
	for (i = NULL; i < nums_0; ++i) {
		for (j = NULL; j < nums_1; ++j) {
			sum_temp_0 += mat_2[j] * mat_1[line_offset0 + i];
			line_offset0 += nums_0;
		}
		line_offset0 = NULL;
		mat_0[i] *= sum_temp_0;
	}
	return true;
}

//�Ż�:0
//mlp:mlp
//learmspeed:ѧϰ����
//����mlp����Ȩ��
int mlp_update(MlpStr *mlp,float learmspeed)
{
	uint32_t i = NULL,nums_0=mat_size(mlp->layer->mat[0]);
	float *mat_0 = (float*)mlp->layer->mat[0]->SaveAddr, *mat_1 = (float*)mlp->gr_mat->mat[0]->SaveAddr;
	for (; i < nums_0; ++i) {
		mat_0[i] -= learmspeed * mat_1[i];
	}
	return true;
}