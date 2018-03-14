#include "xxwsL_math.h"

//�Ż�����:0
//signmoid����
//x:����һ��ֵx
//return:float������
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


//�Ż�����:0
//signmoid������
//x:����
//return:float������
float signmoid_der(float x)
{
	return x*(1 - x);
}
