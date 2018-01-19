#ifndef queue_ot_h
#define queue_ut_h

#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -1
#define OVERFLOW   -2

//Status �Ǻ���������,��ֵ�Ǻ������״̬����
typedef int Status;
//ElemType ��˳�������Ԫ������,�˳�����Ϊint��
typedef int QElemType;

//-----��������--���е���ʽ�洢�ṹ-----
typedef struct QNode {       //������ṹ
	QElemType     data;     //������
	struct QNode *next;     //ָ����
}QNode, *QueuePtr;
typedef struct linkqueue {  //������нṹ
	QueuePtr front;        //��ͷָ��
	QueuePtr rear;         //��βָ��
}LinkQueue;

#endif