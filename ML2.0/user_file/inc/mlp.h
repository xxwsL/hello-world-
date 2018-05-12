#ifndef _mlp_h_
#define _mlp_h_
#include "xxwsL.h"

#define _get_mlp(name) ((struct MlpStr*)name)

//mlp�����ݺ�
#define _mlp_layer  0x01
#define _mlp_outmat 0x02
#define _mlp_gr_mat 0x04
#define _mlp_tensor 0x07
#define _mlp_op	    0x08	
#define _mlp_fi	    0x10 	
#define _mlp_fid    0x20
#define _mlp_fi_all 0x30
#define _mlp_gr_op  0x40
#define _mlp_all    0x7f

//mlp��
typedef struct MlpStr {
	//���Ӳ�
	struct TensorStr *layer;
	//�����
	struct TensorStr *outmat;
	//�ݶȲ�
	struct TensorStr *gr_mat;
	//ƫ��
	float op;
	//ƫ���ᶽ
	float op_gr;
	//�����
	bool (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
	//�󵼺���
	bool (*active_fid) (const struct MatrixStr *mat, struct MatrixStr *loadmat, const struct MatrixStr *target);
}mlpstr;

//mlp�ڵ��ʼ��
bool mlp_init(mlpstr *mlp, float op, bool (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat), struct TensorStr *layer);
//���ڵ�mlpǰ�����
bool mlp_one_op(MlpStr *mlp, struct TensorStr *inmat);
//����mlp������
MlpStr *mlp_create(float op, bool (*active_fi) (const struct MatrixStr *mat, struct MatrixStr *loadmat), uint16_t line, uint16_t row);
//ɾ��mlp
bool mlp_create(MlpStr* &mlp);
//��ӡmlp
bool mlp_output(void *mlp_add, uint8_t content);
//�������Ӳ��ݶ�
bool mlp_gr(struct TensorStr *tensor, MlpStr *r_mlp);
//�������
bool mlp_error_pass(MlpStr *l_mlp, MlpStr* r_mlp);
bool mlp_error_pass(TensorStr *tensor, MlpStr* mlp);
//����mlp����Ȩ��
bool mlp_update(MlpStr *mlp, float learmspeed);

#endif 

