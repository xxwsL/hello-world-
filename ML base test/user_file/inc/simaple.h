#ifndef _simaple_h_
#define _simaple_h_
#include "xxwsL.h"

//network test date
float bias_Lspeed[3] = {bias0,bias1,leardpeed};
uint8_t voidmodel[72] = {};

uint8_t model0_0[72] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x98,0x03,0x00,0x0C,0x02,0x00,0x06,0x02,0x00,0x01,0x02,0x80,0x01,0x02,0x80,0x00,0x02,0xC0,0x00,0x02,0x40,0x00,0x02,0x40,0x00,0x03,0x40,
	0x00,0x01,0x40,0x80,0x01,0x40,0x80,0x00,0xC0,0xC1,0x00,0x00,0x67,0x00,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff
};

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


MatStr trainmat = f32MatInit(train_mat);
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


#endif // !_simaple_h_

