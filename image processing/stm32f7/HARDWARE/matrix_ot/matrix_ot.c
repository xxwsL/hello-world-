#include "matrix_ot.h"

char output(MatStr mat)						//�������
{
	unsigned char i=0, j=0;
	unsigned char iadd=0;
	unsigned char g[12];
	for (i = 0; i < mat.line; i++)
	{
		iadd=i*mat.row;
		for (j = 0; j < mat.row; j++)
		{
		    g[iadd+j]=(unsigned char)*(mat.SaveAddr+iadd+j)+48;
//			printf("%f\t", *(mat.SaveAddr ++));    //�Ʊ�ʽ�������
		} 
//		printf("\n");							   //\n
	}
	LCD_ShowString(0,130,200,16,16,(u8*)g);
	return true;
}

char transpose(MatStr mat)
{
	return true;
}


