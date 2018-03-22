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

StatusStr TestStatus;									//��־��
MatStr testmat = i16MatInit(TestMatr);					//��ʼ����Ϣ���������ַ������ ������
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

	//printf("Test����\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmat����");
	//mat_message(&tempmat);
	//output(&tempmat);

	//printf("voidmat0����\n");
	//mat_message(voidmat0);
	//output(voidmat0);

	//printf("voidmat1����\n");
	//mat_message(voidmat1);
	//output(voidmat1);

	//while (1);
	/*network test module*/
	uint16_t i = NULL;
	mat_rand_normal(&hide_work);		//��ʼ��������
	mat_rand_normal(&out_work);

	//sprintf(bmp_name, "%s", "0_0.bmp");
	//bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
	//mat_tovector(voidmodel, &trainmat);											//��ʼ����ǩ1
	//printf("test\n");
	//forward_propaga(&trainmat, &hide_work, &out_work, &target_1);
	//back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//ѵ��ģ��1

	for (i = 0; i < 100; ++i)
	{
		sprintf(bmp_name, "%s", "0_0.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//��ʼ����ǩ0_0
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//ѵ��ģ��0_0

		sprintf(bmp_name, "%s", "1_0.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//��ʼ����ǩ1
		back_propaga(&trainmat, &hide_work, &out_work, &target_1, leardpeed);		//ѵ��ģ��1

		sprintf(bmp_name, "%s", "7_0.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//��ʼ����ǩ7
		back_propaga(&trainmat, &hide_work, &out_work, &target_7, leardpeed);		//ѵ��ģ��7

		sprintf(bmp_name, "%s", "0_1.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//��ʼ����ǩ0_1
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//ѵ��ģ��0_1

		sprintf(bmp_name, "%s", "0_2.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//��ʼ����ǩ0_2
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//ѵ��ģ��0_2

		sprintf(bmp_name, "%s", "0_3.bmp");
		bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
		mat_tovector(voidmodel, &trainmat);											//��ʼ����ǩ0_3
		back_propaga(&trainmat, &hide_work, &out_work, &target_0, leardpeed);		//ѵ��ģ��0_3
	}
	sprintf(bmp_name, "%s", "1_0.bmp");
	bmp_r_tobuf(bmp_data, voidmodel, sizeof(voidmodel));
	mat_tovector(voidmodel, &trainmat);
	forward_propaga(&trainmat, &hide_work, &out_work, &target_1);

	while (1);
	return true;
}

