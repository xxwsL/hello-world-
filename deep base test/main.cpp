#include "xxwsL.h"

int16_t TestMatr[][5] = {
	0x0123,2,3,3,4,
	4,5,6,2,1,
	3,7,8,9,23,
	33,10,11,12,55,
	25,13,91,35,8
};

float TempMatr[2][2] = {
};

MatStr testmat = i16MatrixInit(TestMatr);	//初始化信息包括矩阵地址，行数 ，列数
MatStr tempmat = i16MatrixInit(TempMatr);	
MatStr voidmat;
StatusStr TestStatus;							
												
int main(void)									
{
	if (testmat.flag & i16Flag){
		printf("this is a int16_t matrix\n\n");		//测试矩阵类型 
	}

	printf("Test Mat line = %d\n\n", testmat.line);		//测试矩阵行数
	printf("Test Mat row  = %d\n\n", testmat.row);			//测试矩阵列数

	voidmat = matrix_cut(&testmat, 2, 2, 1, f32Flag);

	printf("Test矩阵 =\n");
	output(&testmat);
	printf("voidmat矩阵 =\n");
	output(&voidmat);
	while (1);
	return true;
}

