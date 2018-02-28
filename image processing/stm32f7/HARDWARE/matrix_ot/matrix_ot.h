#ifndef  _matrix_ot_h_
#define  _matrix_ot_h_
#include "xxwsL.h"

//�����ʼ����
#define MatrixMessage(Mateiname) (float*)Mateiname,sizeof(Mateiname)/sizeof(Mateiname[0]),sizeof(Mateiname[0])/4,false
#define MatrixFunction (output)
#define MatrixInit(Mateiname) {MatrixMessage(Mateiname),MatrixFunction}

typedef struct MatrixStruct{
	// ������Ϣ
	float*  SaveAddr;
	uint16_t line;
	uint16_t row;
	uint16_t flag;
	//������ú���
	char (*output) (struct MatrixStruct);

}MatStr;

char output(MatStr mat);
char transpose(MatStr mat);

#endif // ! _matrix_ot_h_
