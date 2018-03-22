 #include "xxwsL_math.h"

//�Ż�����:0
//signmoid����
//x:����һ��ֵx
//return:float������
float signmoid(float x) 
{
	float temp=NULL;
	if (x <= -14){
		temp = 0.000001f;
		return temp;
	}
	if (x >= 14) {
		temp = 0.999999f;
		return temp;
	}
	temp = (float)(1/(1 + 1/pow(e, x)));
	return temp;
}


//�Ż�����:0
//signmoid������
//x:����
//return:float������
float signmoid_der(float x)
{
	return x*(1 - x);
}

//�Ż�����:0
//tanh����
//x:����һ��ֵx
//return:float������
float tanh_(float x)
{
	if (x <= -7) {
		return  -0.999999f;
	}
	if (x >= 7) {
		return  0.999999f;
	}
	return (float)tanh(x);
}

//�Ż�����:0
//tanh������
//x:����
//return:float������
float tanh_der(float x)
{
	return 1-x*x;
}


//�Ż�����:0
//relu����
//x:����
//return:float������
float relu(float x)
{
	return (x > 0) ? x : 0.0f;
}


//�Ż�����:0
//relu������
//x:����
//return:float������
float relu_der(float x)
{
	return (x == 0) ? 0.0f : 1.0f;
}

//�Ż�����:0
//rand�������
//rands:rand���������
//return:float����
float rand_sum(uint32_t rands)
{
	float sum = NULL;
	sum += (float)rand();
	return sum;
}

//�Ż�����:0
//��Ȼ����e����
//x:����
//return:float����
float exp_pow(float x)
{
	return (float)pow(e,x);
}


