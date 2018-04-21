#include "inc\cnn.h"

cnn_l::cnn_l() {
}

cnn_l::~cnn_l()
{
}

int cnn_l::init_cnn(MatrixStr *mat)
{
	kernels = mat;
	return true;
}

int cnn_l::show_kernels(void)
{
	output(kernels);
	return true;
}