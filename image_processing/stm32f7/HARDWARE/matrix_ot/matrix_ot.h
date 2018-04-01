#ifndef  _matrix_ot_h_
#define  _matrix_ot_h_
#include "xxwsL.h"

//矩阵初始化宏
#define MatrixMessage(Mateiname) (float*)Mateiname,sizeof(Mateiname)/sizeof(Mateiname[0]),sizeof(Mateiname[0])/4,false
#define MatrixFunction (output)
#define MatrixInit(Mateiname) {MatrixMessage(Mateiname),MatrixFunction}

typedef struct MatrixStruct{
	// 矩阵信息
	float*  SaveAddr;
	uint16_t line;
	uint16_t row;
	uint16_t flag;
	//矩阵调用函数
	char (*output) (struct MatrixStruct);

}MatStr;

char output(MatStr mat);
char transpose(MatStr mat);

#endif // ! _matrix_ot_h_
