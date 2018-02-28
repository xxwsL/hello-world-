#include "xxwsL.h"

int16_t TestMatr[][5] = {
	0x0123,2,3,3,4,
	4,5,6,2,1,
	3,7,8,9,23,
	33,10,11,12,55,
	25,13,91,35,8
};

float TempMatr[2][2] = {
};

MatStr testmat = i16MatrixInit(TestMatr);	//��ʼ����Ϣ���������ַ������ ������
MatStr tempmat = i16MatrixInit(TempMatr);	
MatStr voidmat;
StatusStr TestStatus;							
												
int main(void)									
{
	if (testmat.flag & i16Flag){
		printf("this is a int16_t matrix\n\n");		//���Ծ������� 
	}

	printf("Test Mat line = %d\n\n", testmat.line);		//���Ծ�������
	printf("Test Mat row  = %d\n\n", testmat.row);			//���Ծ�������

	voidmat = matrix_cut(&testmat, 2, 2, 1, f32Flag);

	printf("Test���� =\n");
	output(&testmat);
	printf("voidmat���� =\n");
	output(&voidmat);
	while (1);
	return true;
}

