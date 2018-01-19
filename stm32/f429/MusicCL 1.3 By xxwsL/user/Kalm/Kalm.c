#include "Kalm.h"

Kalmstr KM1={NULL,NULL,P1,R1};
Kalmstr KM2={NULL,NULL,P2,R2};

double Kalm(Kalmstr *KM,double MeasureVe)
{
	double KG;
	if(KM->LastValue==NULL)
	{
		KM->LastValue=MeasureVe;
		return KM->LastValue;
	}
	else
	{
		KM->QValue=user_abs(MeasureVe-KM->LastValue);
		KM->PValue=KM->PValue+KM->QValue;
		KG=KM->PValue/(KM->PValue+KM->RValue);
		KM->LastValue=KM->LastValue+KG*(MeasureVe-KM->LastValue);
		KM->PValue=(1-KG)*KM->PValue;
	}
	return KM->LastValue;
	
}

double Ka1(double MeasureVe)
{
	return (uint16_t)Kalm(&KM1,MeasureVe);
}

double Ka2(double MeasureVe)
{
	return (uint16_t)Kalm(&KM2,MeasureVe);
}

double user_abs(double input)
{
	if(input<0)
		return -input;
	else
		return input;
		
}





