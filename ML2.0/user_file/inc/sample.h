#ifndef _sample_h_
#define _sample_h_
#include "xxwsL.h"

#define events	 1.0f
#define unevents 0.0f

#define samples 10
#define layers 1

#define max_update 1
#define batch_size 1
#define error_scope 0.05f
#define learmspeed 0.01f

//network test date
//0:损失函数宏
//1:最多更新次数
//2:批大小
//3:误差限定值
//4:学习速率
float tr_message[5] = { _cross_entropy,max_update,batch_size,error_scope,learmspeed };

//float target_mat_0[2][1] = {
//	events,unevents
//};
//
//float target_mat_1[2][1] = {
//	unevents,events
//};

float target_mat_0[10][1] = {
	events,unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents
};

float target_mat_1[10][1] = {
	unevents,events,unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents
};

float target_mat_2[10][1] = {
	unevents,unevents,events,unevents,unevents,unevents,unevents,unevents,unevents,unevents
};

float target_mat_3[10][1] = {
	unevents,unevents,unevents,events,unevents,unevents,unevents,unevents,unevents,unevents
};

float target_mat_4[10][1] = {
	unevents,unevents,unevents,unevents,events,unevents,unevents,unevents,unevents,unevents
};

float target_mat_5[10][1] = {
	unevents,unevents,unevents,unevents,unevents,events,unevents,unevents,unevents,unevents
};

float target_mat_6[10][1] = {
	unevents,unevents,unevents,unevents,unevents,unevents,events,unevents,unevents,unevents
};

float target_mat_7[10][1] = {
	unevents,unevents,unevents,unevents,unevents,unevents,unevents,events,unevents,unevents
};

float target_mat_8[10][1] = {
	unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents,events,unevents
};

float target_mat_9[10][1] = {
	unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents,unevents,events
};

MatStr target_0 = f32MatInit(target_mat_0);
MatStr target_1 = f32MatInit(target_mat_1);
MatStr target_2 = f32MatInit(target_mat_2);
MatStr target_3 = f32MatInit(target_mat_3);
MatStr target_4 = f32MatInit(target_mat_4);
MatStr target_5 = f32MatInit(target_mat_5);
MatStr target_6 = f32MatInit(target_mat_6);
MatStr target_7 = f32MatInit(target_mat_7);
MatStr target_8 = f32MatInit(target_mat_8);
MatStr target_9 = f32MatInit(target_mat_9);

MatStr *target_set[] = { &target_0 ,&target_1,&target_2,&target_3,&target_4,&target_5,&target_6,&target_7,&target_8,&target_9 };
//MatStr *target_set[] = { &target_0 ,&target_1 };

#endif 

