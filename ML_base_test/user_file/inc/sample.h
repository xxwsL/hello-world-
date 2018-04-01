#ifndef _sample_h_
#define _sample_h_
#include "xxwsL.h"

#define events	 1.0f
#define unevents 0.0f

#define samples 10

#define nextworks 1

//network test date
float tr_message[6] = {bias0,bias1,bias2,leardpeed,samples,nextworks};


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

MatStr hide_work = f32MatInit(hide_network_buf);
MatStr out_work = f32MatInit(out_network_buf);
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

#endif 

