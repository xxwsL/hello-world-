#ifndef _xxwsL_math_h_
#define _xxwsL_math_h_

#include "xxwsL.h"

#define e 2.718281f

//signmoid函数
float signmoid(const float x);
//signmoid函数求导
float signmoid_der(const float x);
//tanh函数
float tanh_(const float x);
//tanh函数求导
float tanh_der(const float x);
//relu函数
float relu(const float x);
//relu函数求导
float relu_der(const float x);
//自然对数e的幂
float exp_pow(const float x);

#endif
