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

StatusStr TestStatus;									//��־��
MatStr testmat = i16MatInit(TestMatr);					//��ʼ����Ϣ���������ַ������ ������
MatStr tempmat = f32MatInit(TempMatr);	
MatStr multmat = f32MatInit(MultMat);
MatStr *voidmat0=NULL;		
MatStr *voidmat1=NULL;


int main(void)									
{
	uint32_t i = NULL;
	/*matrix_ot test module*/
	voidmat0 = mat_create(10, 1, f32Flag);
	voidmat1 = mat_create(10, 1, f32Flag);

	//printf("Test����\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat����");
	//mat_message(&tempmat);
	//output(&tempmat);

	//while (1);
	/*network test module*/
	//printf("%f\n",exp_pow(86)*10);
	TrStr tr;
	long time_start = NULL, time_end = NULL;
	rand_init();
	Train_init(&tr, &hide_work, &out_work,target_set,tr_message, relu_active, softmax_active);
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
		printf("ѵ������ = %d\n", i);
	}
	time_end = clock();
	time_end -= time_start;
	printf("ѵ��ʱ�� = %ld h %ld m %ld s %ld ms\n", time_end / 3600000l, time_end % 3600000l / 60000l, time_end % 60000l / 1000l, time_end % 1000l);
	train_test("D:\\work\\ML\\ML_base\\simaple\\set_data\\set0\\0", 5, &tr);
	while (1);
	return true;
}
