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

//优化次数:0
//tanh函数
//x:输入一个值x
//return:float型数据
float tanh_(float x)
{
	if (x <= -7) {
		return  -0.999999;
	}
	if (x >= 7) {
		return  0.999999;
	}
	return (float)tanh(x);
}

//优化次数:0
//tanh函数求导
//x:输入
//return:float型数据
float tanh_der(float x)
{
	return 1-x*x;
}


//优化次数:0
//relu函数
//x:输入
//return:float型数据
float relu(float x)
{
	return (x > 0) ? x : 0;
}


//优化次数:0
//relu函数求导
//x:输入
//return:float型数据
float relu_der(float x)
{
	return (x == 0) ? 0 : 1;
}

//优化次数:0
//rand随机数和
//rands:rand随机数数量
//return:float数据
float rand_sum(uint32_t rands)
{
	float sum = NULL;
	sum += (float)rand();
	return sum;
}

