#include "xxwsL.h"
#include "sample.h"

//matrix_ot test date

float TempMatr[3][3] = {
	11,12,13,
	4,5,6,
	7,8,9
};

float MultMat[3][2] = {
	1,2,
	1,2,
	1,2
};

StatusStr TestStatus;									//±Í÷æ¿‡		
MatStr tempmat = f32MatInit(TempMatr);
MatStr multmat = f32MatInit(MultMat);
MatStr *voidmat0 = NULL;
MatStr *voidmat1 = NULL;

bool main(void)
{
	int32_t i = NULL;	
	uint16_t s0 = NULL, s1 = NULL, s2 = NULL;
	long time_start = NULL, time_end = NULL;
	/*matrix_ot test module*/

	voidmat0 = mat_create(10000, 1000, f32Flag);
	voidmat1 = mat_create(3, 2, f32Flag);

	//printf("Testæÿ’Û\n");
	//mat_message(get(testmat));
	//output(&testmat);

	//printf("tempmatæÿ’Û");
	//mat_message(&tempmat);
	//output(&tempmat);

	/*tensor_ot test module*/

	while (1);
	return true;
}