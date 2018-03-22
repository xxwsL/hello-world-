#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

//#define signmoid_active
//#define tanh_active
#define relu_active

#define events	 0.82f
#define unevents 0.02f

#define events_sample 10

#define error_scope 0.01f

#define leardpeed 0.1f

#define hide_bias 0.1f
#define out_bias 0.1f

typedef struct MlpStruct {
	struct MatrixStr *mat;
	struct MatrixStr *layer[2];
	struct MatrixStr *outmat[2];
	float bias[2];
	bool (*active_fi0) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
	bool (*active_fi1) (const struct MatrixStr *mat, struct MatrixStr *loadmat);
}MlpStr;

//反向传播
bool back_propaga(const struct MatrixStr *mat, struct MatrixStr *hide_network_mat, struct MatrixStr *out_nework_mat, const struct MatrixStr *target_mat, float learm_speed);
//误差分析
bool error_analysis(float error_value);
//前向传播
bool forward_propaga(const struct MatrixStr *mat, struct MatrixStr *hide_network_mat, struct MatrixStr *out_nework_mat, const struct MatrixStr *target_mat);

#endif // !_network_h_

