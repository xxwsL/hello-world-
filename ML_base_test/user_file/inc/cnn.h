#ifndef _cnn_h_
#define _cnn_h_
#include "xxwsL.h"

class cnn_l{
public:
	cnn_l();
	~cnn_l();
	MatrixStr *kernels;
	bool init_cnn(MatrixStr *mat);
	bool show_kernels(void);
private:
};

#endif
