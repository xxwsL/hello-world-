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

int main(void)
{
	int32_t i = NULL, j = NULL;
	long time_start = NULL, time_end = NULL;
	array<uint16_t, 4> b0;
	array<uint16_t, 4> b1;
	array<uint8_t, 4>  b2;
	/*matrix_ot test module*/

	MatrixStr *voidmat0 = mat_create(2, 2, f32Flag);
	MatrixStr *voidmat1 = mat_create(2, 2, f32Flag);
	MatrixStr *voidmat2 = mat_create(3, 3, f32Flag);

	//printf("Test矩阵\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat矩阵");
	//mat_message(&tempmat);
	//output(&tempmat);

	/*tensor_ot test module*/

	/*network*/

	//创建模拟输入张量0
	TensorStr *tensor0 = tensor_create(3, 3, 3, 1);		//创建6x6x1x3的张量
	tensor_assign(tensor0, 0.0f);						//默认升序赋值张量
	//tensor_output(tensor0);							//打印tensor0

	while (1);

	b0 = { 2,2,2,1 };			//卷积核张量尺寸
	b1 = { 2,2,2,1 };			//卷积输出张量尺寸
	b2 = { 1,1,0,0 };			//卷积步伐信息
	GraphStr *cnn_conv0 = graph_cnn_conv_create(b0, b1, b2, 0.0f, _relu_active);			//创建cnn_conv图
	tensor_assign(_graph_get_conv(cnn_conv0)->kernel, 1.0f);
	tensor_assign(_graph_get_conv(cnn_conv0)->out, 1.0f);

	_graph_get_conv(cnn_conv0)->error_pass_conv(tensor0);
	graph_output(cnn_conv0, _graph_all);
	tensor_output(tensor0);

	time_end  = clock();
	time_end -= time_start;
	printf("time = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	while (1);
	return true;
}