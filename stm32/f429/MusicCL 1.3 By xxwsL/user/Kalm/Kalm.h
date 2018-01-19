#ifndef _Kalm_h_
#define _Kalm_h_
#include "xxwsL.h"

#define P1 10
#define R1 20

#define P2 10
#define R2 20

typedef struct 
{
	double LastValue;
	double QValue;
	double PValue;
	double RValue;
	
}Kalmstr;

double Kalm(Kalmstr *KM,double MeasureVe);
double user_abs(double input);

double Ka1(double MeasureVe);
double Ka2(double MeasureVe);
	
#endif


