#include "xxwsL.h"

int16_t TestMatr[][5] = {
	0x0123,2,3,3,4,
	4,5,6,2,1,
	3,7,8,9,23,
	33,10,11,12,55,
	25,13,91,35,8
};

float TempMatr[][2] = {
	1,2,
	3,4
};

int16_t MultMat[][3] = {
	1,2,1,
	1,2,1
};

StatusStr TestStatus;									//标志类
MatStr testmat = i16MatInit(TestMatr);					//初始化信息包括矩阵地址，行数 ，列数
MatStr tempmat = f32MatInit(TempMatr);	
MatStr multmat = i16MatInit(MultMat);
MatStr voidmat;						


int main(void)									
{
	//tempmat =matfi.mat_cov(&tempmat);
	
	//voidmat = matfi.mat_mult(&tempmat,&multmat);

	//mat_qr(&testmat,&voidmat,&tempmat);

	printf("Test矩阵\n");
	matfi.mat_message(get(testmat));
	matfi.output(&testmat);

	printf("voidmat矩阵\n");
	matfi.mat_message(&voidmat);
	matfi.output(&voidmat);

	printf("tempmat矩阵");
	matfi.mat_message(&tempmat);
	matfi.output(&tempmat);

	while (1);
	return true;
}

