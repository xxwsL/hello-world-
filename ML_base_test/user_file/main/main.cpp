#include "xxwsL.h"
#include "sample.h"

//matrix_ot test date
int16_t TestMatr[][5] = {
	0x0123,2,3,3,4,
	4,5,6,2,1,
	3,7,8,9,23,
	33,10,11,12,55,
	25,13,91,35,8
};

float TempMatr[3][3] = {
	1,2,3,
	4,5,6,
	7,8,9
};

float MultMat[3][2] = {
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
	int32_t i = NULL;
	/*matrix_ot test module*/
	voidmat0 = mat_create(10, 1, f32Flag);
	voidmat1 = mat_create(10, 1, f32Flag);

	MatStr **p=NULL;

	//printf("Test矩阵\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat矩阵");
	//mat_message(&tempmat);
	//output(&tempmat);
	//while (1);
	/*network test module*/
	//printf("%f\n",exp_pow(86)*10);
	ms tr;
	MatStr *layer[3] = {&hide_work,&out_work};
	active_fi_buf(fi, 2) = {relu_active,softmax_active};
	long time_start = NULL, time_end = NULL;
	rand_init();
	Train_init(&tr, layer,target_set,op_set, mlp_message_buf,fi);
	time_start = clock();
	for (i = 0; i < 330; ++i) {
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set0\\0", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set1\\1", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set2\\2", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set3\\3", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set4\\4", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set5\\5", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set6\\6", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set7\\7", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set8\\8", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set9\\9", rand() % 10, &tr);
		Train_start("D:\\work\\ML\\ML_base\\simaple\\set_data\\set10\\10", rand() % 10, &tr);
		printf("训练个数 = %d\n", i);
	}
	time_end = clock();
	time_end -= time_start;
	printf("训练时间 = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	train_test("D:\\work\\ML\\ML_base\\simaple\\test_set\\test0_", 0, &tr);
	train_test("D:\\work\\ML\\ML_base\\simaple\\test_set\\test1_", 0, &tr);
	//echo_f32buf_to_txt("D:\\work\\ML\\ML_base\\simaple\\demo.txt", (float*)tr.layer[0]->SaveAddr, 576*12);
	while (1);
	return true;
}

