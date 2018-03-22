#ifndef _xxwsL_math_h_
#define _xxwsL_math_h_

#include "xxwsL.h"

#define e 2.718281f

//signmoid����
float signmoid(const float x);
//signmoid������
float signmoid_der(const float x);
//tanh����
float tanh_(const float x);
//tanh������
float tanh_der(const float x);
//relu����
float relu(const float x);
//relu������
float relu_der(const float x);
//��Ȼ����e����
float exp_pow(const float x);

#endif
