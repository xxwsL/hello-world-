//����ͷ
#ifndef  main_h
#define  main_h
#include "conio.h"
#include "stdlib.h"
#include "GUI.h"
#include "stdio.h"

#define scanf_rp scanf_repli
#define print_rp printf_repli
//���������������ת�͸�����

#define x_lenght 359
#define y_lenght 419
//��Ļ��Ӧ�ߴ�

#define RECOMMENDED_MEMORY (1024L * 5)

#define u8 unsigned char 
#define u16 unsigned int
#define u32 unsigned long

enum BOOL{False,True};     //����BOOL��

/*ָ����׺�*/
#define sequence_size 100
#define sequence_base 2
#define sequence_value sequence_size+sequence_base 

int sequence[sequence_value];

#define sysinit sys_init()
#define windowschange windows_change()

#endif