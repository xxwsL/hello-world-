#ifndef queue_ot_h
#define queue_ut_h

#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -1
#define OVERFLOW   -2

//Status 是函数的类型,其值是函数结果状态代码
typedef int Status;
//ElemType 是顺序表数据元素类型,此程序定义为int型
typedef int QElemType;

//-----单链队列--队列的链式存储结构-----
typedef struct QNode {       //定义结点结构
	QElemType     data;     //数据域
	struct QNode *next;     //指针域
}QNode, *QueuePtr;
typedef struct linkqueue {  //定义队列结构
	QueuePtr front;        //队头指针
	QueuePtr rear;         //队尾指针
}LinkQueue;

#endif