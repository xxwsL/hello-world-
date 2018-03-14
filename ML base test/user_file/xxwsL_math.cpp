#include "xxwsL_math.h"

//优化次数:0
//signmoid函数
//x:输入一个值x
//return:float型数据
float signmoid(float x) 
{
	float temp=NULL;
	if (x <= -14){
		temp = 0.000001;
		return temp;
	}
	if (x >= 14) {
		temp = 0.999999;
		return temp;
	}
	temp = (float)1/(1 + 1/pow(e, x));
	return temp;
}


//优化次数:0
//signmoid函数求导
//x:输入
//return:float型数据
float signmoid_der(float x)
{
	return x*(1 - x);
}
