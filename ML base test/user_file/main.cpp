#include "xxwsL.h"

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

//network test date
uint8_t model[72] = {
	0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0xE0,0x00,0x00,0x60,0x00,0x00,0x70,0x00,0x00,0x30,0x00,0x00,0x38,0x00,0x00,0x18,0x00,0x00,0x1C,0x00,0x00,0x0C,0x00,0x00,0x0E,0x00,0x00,0x06,0x00,0x00,
	0x07,0x00,0x00,0x03,0x00,0x80,0x03,0x00,0x80,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x00,0x00,0xC0,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

float train_mat[576][1] = {
};

float hide_network_buf[10][576] = {
};

float out_network_buf[10][10] = {
};

float target_mat[10][1] = {
	0.01,0.91,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01
};

MatStr trainmat = f32MatInit(train_mat);
MatStr hide_work = f32MatInit(hide_network_buf);
MatStr out_work = f32MatInit(out_network_buf);
MatStr targetmat = f32MatInit(target_mat);

int main(void)									
{
	/*matrix_ot test module*/
	//voidmat0 = mat_create(4*8, 1, f32Flag);
	//voidmat1 = mat_create(5, 5, f32Flag);

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

	/*network test module*/
	mat_assignment(&hide_work,0.5);		//初始化神经网络
	mat_assignment(&out_work,0.5);

	mat_tovector(model, &trainmat);		//初始化标签

	back_propaga(&trainmat,&hide_work,&out_work,&targetmat,leardpeed);		//训练模型

	//printf("hide_work矩阵\n");
	//mat_message(&hide_work);
	////output(&hide_work);

	//printf("out_work矩阵\n");
	//mat_message(&out_work);
	//output(&out_work);

	while (1);
	return true;
}

