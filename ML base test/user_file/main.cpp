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

float train_mat[576][1] = {
};

float hide_network_buf[12][576] = {
};

float out_network_buf[10][12] = {
};

float target_mat_0[10][1] = {
	events,unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents
};

float target_mat_1[10][1] = {
	unevents,events,unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents
};

float target_mat_7[10][1] = {
	unevents,unevents,unevents,unevents,unevents,unevents,unevents,events,unevents,unevents
};

MatStr trainmat = f32MatInit(train_mat);
MatStr hide_work = f32MatInit(hide_network_buf);
MatStr out_work = f32MatInit(out_network_buf);
MatStr target_0 = f32MatInit(target_mat_0);
MatStr target_1 = f32MatInit(target_mat_1);
MatStr target_7 = f32MatInit(target_mat_7);

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
	uint16_t i = NULL;
	mat_rand_normal(&hide_work);		//初始化神经网络
	mat_rand_normal(&out_work);

	//sprintf(bmp_name, "%s", "0_0.bmp");
	//bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
	//mat_tovector(voidmodel, &trainmat);											//初始化标签1
	//printf("test\n");
	//forward_propaga(&trainmat, &hide_work, &out_work, &target_1);
	//back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型1

	for (i = 0; i < 100; ++i)
	{
		sprintf(bmp_name, "%s", "0_0.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//初始化标签0_0
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型0_0

		sprintf(bmp_name, "%s", "1_0.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//初始化标签1
		back_propaga(&trainmat, &hide_work, &out_work, &target_1, leardpeed);		//训练模型1

		sprintf(bmp_name, "%s", "7_0.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//初始化标签7
		back_propaga(&trainmat, &hide_work, &out_work, &target_7, leardpeed);		//训练模型7

		sprintf(bmp_name, "%s", "0_1.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//初始化标签0_1
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型0_1

		sprintf(bmp_name, "%s", "0_2.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//初始化标签0_2
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型0_2

		sprintf(bmp_name, "%s", "0_3.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//初始化标签0_3
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型0_3
	}
	sprintf(bmp_name, "%s", "1_0.bmp");
	bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
	mat_tovector(voidmodel, &trainmat);
	forward_propaga(&trainmat, &hide_work, &out_work, &target_1);

	while (1);
	return true;
}

