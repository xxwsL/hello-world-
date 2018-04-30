#include "xxwsL.h"
#include "sample.h"

//matrix_ot test date

float TempMatr[3][3] = {
	11,12,13,
	4,5,6,
	7,8,9
};

float MultMat[3][2] = {
	1,2,
	1,2,
	1,2
};

StatusStr TestStatus;									//标志类		
MatStr tempmat = f32MatInit(TempMatr);
MatStr multmat = f32MatInit(MultMat);

bool main(void)
{
	int32_t i = NULL, j = NULL;
	uint16_t s0 = NULL, s1 = NULL, s2 = NULL;
	long time_start = NULL, time_end = NULL;
	/*matrix_ot test module*/

	MatrixStr *voidmat0 = mat_create(6, 6, f32Flag);
	MatrixStr *voidmat1 = mat_create(2, 2, f32Flag);
	MatrixStr *voidmat2 = mat_create(3, 3, f32Flag);

	//printf("Test矩阵\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat矩阵");
	//mat_message(&tempmat);
	//output(&tempmat);

	/*tensor_ot test module*/

	/*cnn*/
	array<uint16_t, 4> b0 = { 2,2,3,1 };
	array<uint16_t, 4> b1 = { 6,6,3,1 };
	array<uint8_t, 4>  b2 = { 1,1,0,0 };

	//创建cnn卷积图
	time_start = clock();
	GraphStr* conv0 = graph_cnn_conv_create(b0, b1, b2, 0.1f, _relu_active);
	tensor_assignment(((cnn_conv*)conv0->graph_data)->kernel, 1.25f);
	((cnn_conv*)conv0->graph_data)->output(_cnn_conv_kernel);
	
	//创建模拟输入张量
	TensorStr *tensor0 = tensor_create(7, 7, 1);
	tensor_assignment(tensor0, 4.0f);
	((cnn_conv*)conv0->graph_data)->conv_ot(tensor0);
	((cnn_conv*)conv0->graph_data)->output(_cnn_conv_out);

	//创建cnn池化图
	b0 = { 3,3,3,1 };
	GraphStr *pooling0 = graph_cnn_pooling_create(2, 2, b0, _cnn_pooling_aver);
	((cnn_pooling*)pooling0->graph_data)->pooling_ot(((cnn_conv*)conv0->graph_data)->out);
	((cnn_pooling*)pooling0->graph_data)->output(_cnn_pooling_out);

	//创建tensorarch图
	b1 = { 27,1,1,1 };
	GraphStr *tensorarch = graph_tensorarch_create(b0, b1);
	tensorarch_op((TensorArch*)tensorarch->graph_data, ((cnn_pooling*)pooling0->graph_data)->out, _direct_left);
	tensor_output(((TensorArch*)tensorarch->graph_data)->r_d_tensor);

	time_end = clock();
	time_end -= time_start;
	printf("time = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	while (1);
	return true;
}