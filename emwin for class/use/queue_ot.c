#include "queue_ot.h"
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "key_opt.h"
#include "sys_opt.h"
#include "sys_display.h"



extern lines;
Status InitLinkQueue(LinkQueue *Q);          //初始化一个队列
Status DestroyLinkQueue(LinkQueue *Q);       //销毁一个队列
int LinkQueueLength(LinkQueue *Q);          //队列的长度
Status EnLinkQueue(LinkQueue *Q, QElemType);  //将一个元素入队列
Status DeLinkQueue(LinkQueue *Q,QElemType *e);//将一个元素出队列
Status DisplayLinkQueue(LinkQueue,char *queue);         //显示队列中所有元素
void queue_otfn(void);                          //队列操作
void queue_display_init(void);

void queue_otfn()
{
	char queue[] = "[?:?]";
	LinkQueue LQ;
	QElemType e;
	int flag = 1, ch,len;
	Status temp;
	InitLinkQueue(&LQ);  //初始化队列
	queue_display_init();
	while (flag) {
		ch=scanf_repli();
		switch (ch) {
		case 1: 
			creat_Rect(GUI_BLACK);
			print_rp("All queue are :", 0, -1, clearflag);
			DisplayLinkQueue(LQ, &queue);   //显示队列中所有元素
			break;
		case 2:
			print_rp("Please enter the elements of team：",0,-1, clearflag);
			e= scanf_repli();   //输入要入队列的字符
			EnLinkQueue(&LQ, e);//入队列
			DisplayLinkQueue(LQ, &queue);
			break;
		case 3:
			temp = DeLinkQueue(&LQ,&e);  //出队列
			if (temp == OK) {
				print_rp("Come out with one element:", 0,-1, clearflag);
				DisplayLinkQueue(LQ,&queue);
			}
			else
				print_rp("The queue is empty!",0, -1, clearflag);
			break;
		case 4:
			len = LinkQueueLength(&LQ);
			print_rp("The length of the queue is：", 0, -1, clearflag);
			print_rp(&len, 0, -1, 0);
			break;
		case back:back_back; flag = 0;		break;
		case main:back_main; flag = 0;  	break;
		case sure:queue_display_init();		break;
		default:break;
		}
	}
}

Status InitLinkQueue(LinkQueue *Q) {//队列初始化
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode)); //生成一个头结点，并把首尾指针指向头结点
	Q->front->next = NULL;
	return OK;
}
Status DestroyLinkQueue(LinkQueue *Q) {//销毁一个队列
	QueuePtr p;
	QElemType e;
	while (Q->front != Q->rear)
		DeLinkQueue(Q, e);
	free(Q->front);
	Q->front = Q->rear = NULL;
	return OK;
}

int LinkQueueLength(LinkQueue *Q) {//队列的长度
	int i = 48;
	QueuePtr p = Q->front;
	while (p != Q->rear) {
		++i;
		p = p->next;
	}
	return i;
}

Status EnLinkQueue(LinkQueue *Q, QElemType e) {//入队列
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));//生成一个新结点
	p->data = e;                      //赋值
	p->next = NULL;
	Q->rear->next = p;                 //插入至队列尾
	Q->rear = p;                       //修改队尾指针
	return OK;
}

Status DeLinkQueue(LinkQueue *Q, QElemType *e) {//出队列
	QueuePtr p;
	if (Q->front == Q->rear) return ERROR;     //判断队列是否已空，已空返回ERROR
	p = Q->front->next;                      //p指向队列中第一个元素
	e = p->data;                            //取得该元素值
	Q->front->next = p->next;                //修改队首指针
	if (Q->rear == p) Q->rear = Q->front;         //若队列已空，把队尾指针指向头结点
	return OK;                            //成功出队列，返回OK
}

Status DisplayLinkQueue(LinkQueue Q,char *queue) {//显示队列中所有元素
	QueuePtr p;
	int i = 48;
	p = Q.front->next;
	if (p == NULL) print_rp("The queue is empty!",0,-1, 0);//队列为空
	else {

		while (p) {       //否则显示队列中所有元素
			*(queue + 1) = ++i;
			*(queue + 3)=p->data+48;
			print_rp(queue, 0, -1,0);
			p = p->next;
		}
	}
	return OK;
}

void queue_display_init()
{
	numpad_f;
	creat_Rect(GUI_BLACK);
	GUI_SetColor(GUI_WHITE); //设置字体颜色
	GUI_SetFont(&GUI_Font20_ASCII);
	GUI_DispStringAt("program implements the operation of the chain structure queue.",0, Rect_base +20*0);
	GUI_DispStringAt("can queue, queue, and so on.",0, Rect_base + 20 * 1);
	GUI_DispStringAt("Please select:",0, Rect_base + 20 * 2);
	GUI_DispStringAt("(1). Display all elements of the queue",0, Rect_base + 20 * 3);
	GUI_DispStringAt("(2). In the queue",0, Rect_base + 20 * 4);
	GUI_DispStringAt("(3). Out queue", 0, Rect_base + 20 * 5);
	GUI_DispStringAt("(4). Ask for the length of the queue", 0, Rect_base + 20 * 6);
	GUI_DispStringAt("Back.Exit the program", 0, Rect_base + 20 * 7);
	GUI_DispStringAt("Mian.Return to main interface", 0, Rect_base + 20 * 8);
}