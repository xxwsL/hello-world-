#include "xxwsL.h"

int16_t TestMatr[][5] = {
	0x0123,2,3,3,4,
	4,5,6,2,1,
	3,7,8,9,23,
	33,10,11,12,55,
	25,13,91,35,8
};

float TempMatr[][2] = {
	1,2,
	3,4
};

StatusStr TestStatus;									//��־��
MatStr testmat = i16MatInit(TestMatr);					//��ʼ����Ϣ���������ַ������ ������
MatStr tempmat = f32MatInit(TempMatr);	
MatStr voidmat;							

int main(void)									
{
	if (testmat.flag & i16Flag){
		printf("this is a int16_t matrix\n\n");			//���Ծ������� 
	}

	printf("Test Mat line = %d\n\n", testmat.line);		//���Ծ�������
	printf("Test Mat row  = %d\n\n", testmat.row);		//���Ծ�������

	voidmat = matfi.mat_cut(&testmat, 2, 2, 1, f32Flag);

	printf("Test���� =\n");
	matfi.output(&testmat);
	printf("voidmat���� =\n");
	matfi.output(&voidmat);

	printf("tempmat���� =\n");
	tempmat =matfi.mat_cov(&tempmat);
	matfi.output(&tempmat);
	

	while (1);
	return true;
}

