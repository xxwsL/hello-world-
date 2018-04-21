#ifndef _cnn_h_
#define _cnn_h_
#include "xxwsL.h"

class cnn_l{
public:
	cnn_l();
	~cnn_l();
	MatrixStr *kernels;
	int init_cnn(MatrixStr *mat);
	int show_kernels(void);
private:
};

#endif
