#include "xxwsL.h"
#include "simaple.h"

//matrix_ot test date
int16_t TestMatr[][5] = {
	0x0123,2,3,3,4,
	4,5,6,2,1,
	3,7,8,9,23,
	33,10,11,12,55,
	25,13,91,35,8
};

float TempMatr[][3] = {
	1,2,3,
	4,5,6,
	7,8,9
};

float MultMat[][2] = {
	1,2,
	1,2,
	1,2
};

StatusStr TestStatus;									//标志类
MatStr testmat = i16MatInit(TestMatr);					//初始化信息包括矩阵地址，行数 ，列数
MatStr tempmat = f32MatInit(TempMatr);	
MatStr multmat = f32MatInit(MultMat);
MatStr *voidmat0=NULL;		
MatStr *voidmat1=NULL;


int main(void)									
{
	/*matrix_ot test module*/
	//voidmat0 = mat_create(10, 1, f32Flag);,
	//voidmat1 = mat_create(3, 2, f32Flag);

	//printf("Test矩阵\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat矩阵");
	//mat_message(&tempmat);
	//output(&tempmat);

	//printf("voidmat0矩阵\n");
	//mat_message(voidmat0);
	//output(voidmat0);

	//printf("voidmat1矩阵\n");
	//mat_message(voidmat1);
	//output(voidmat1);

	//while (1);
	/*network test module*/
	uint32_t i = NULL;
	//while (1);
	TrStr tr;
	Train_init(&tr, &trainmat, &hide_work, &out_work, bias_Lspeed, relu_active, softmax_active);
	tr.target = &target_0;
	Train_start("D:\\work\\ML\\ML_base\\simaple\\0", 4, voidmodel, sizeof(voidmodel), &tr);
	while (1);
	return true;
}

