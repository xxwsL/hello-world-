#ifndef _network_h_
#define _network_h_

#include "xxwsL.h"

#define events	 0.91
#define unevents 0.01

#define events_sample 10

#define error_scope 0.0001

#define leardpeed 0.5

//¶ş²ãÍøÂçÑµÁ·Ä£ĞÍ
bool back_propaga(const struct MatrixStr *mat, struct MatrixStr *hide_network_mat, struct MatrixStr *out_nework_mat, const struct MatrixStr *target_mat, float learm_speed);
//Îó²î·ÖÎö
bool error_analysis(float error_value);

#endif // !_network_h_

