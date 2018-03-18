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
MatStr *voidmat0;		
MatStr *voidmat1;

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
	//voidmat0 = mat_create(5, 5, f32Flag);
	//voidmat1 = mat_create(3, 2, f32Flag);

	//mat_rand_normal(voidmat0);
	//mat_mult_par(&tempmat, &multmat, voidmat1);

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
	mat_tovector(model0_0, &trainmat);
	back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		 //训练模型0_0
	//forward_propaga(&trainmat,&hide_work,&out_work,&target_0);
	for (i = 0; i < 100; ++i)
	{
		mat_tovector(model0_0, &trainmat);											//初始化标签0_0
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型0_0

		mat_tovector(model1, &trainmat);											//初始化标签1
		back_propaga(&trainmat, &hide_work, &out_work, &target_1, leardpeed);		//训练模型1

		mat_tovector(model7, &trainmat);											//初始化标签7
		back_propaga(&trainmat, &hide_work, &out_work, &target_7, leardpeed);		//训练模型7

		mat_tovector(model0_1, &trainmat);											//初始化标签0_1
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型0_1

		mat_tovector(model0_2, &trainmat);											//初始化标签0_2
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型0_2

		mat_tovector(model0_3, &trainmat);											//初始化标签0_3
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//训练模型0_3
	}
	//mat_assignment(&trainmat,1);
	//mat_message(&hide_work);
	//output(&hide_work);
	//output(&out_work);
	mat_tovector(model1, &trainmat);
	forward_propaga(&trainmat, &hide_work, &out_work, &target_0);

	while (1);
	return true;
}

