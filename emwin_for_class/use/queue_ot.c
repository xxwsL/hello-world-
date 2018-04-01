#include "queue_ot.h"
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "key_opt.h"
#include "sys_opt.h"
#include "sys_display.h"



extern lines;
Status InitLinkQueue(LinkQueue *Q);          //��ʼ��һ������
Status DestroyLinkQueue(LinkQueue *Q);       //����һ������
int LinkQueueLength(LinkQueue *Q);          //���еĳ���
Status EnLinkQueue(LinkQueue *Q, QElemType);  //��һ��Ԫ�������
Status DeLinkQueue(LinkQueue *Q,QElemType *e);//��һ��Ԫ�س�����
Status DisplayLinkQueue(LinkQueue,char *queue);         //��ʾ����������Ԫ��
void queue_otfn(void);                          //���в���
void queue_display_init(void);

void queue_otfn()
{
	char queue[] = "[?:?]";
	LinkQueue LQ;
	QElemType e;
	int flag = 1, ch,len;
	Status temp;
	InitLinkQueue(&LQ);  //��ʼ������
	queue_display_init();
	while (flag) {
		ch=scanf_repli();
		switch (ch) {
		case 1: 
			creat_Rect(GUI_BLACK);
			print_rp("All queue are :", 0, -1, clearflag);
			DisplayLinkQueue(LQ, &queue);   //��ʾ����������Ԫ��
			break;
		case 2:
			print_rp("Please enter the elements of team��",0,-1, clearflag);
			e= scanf_repli();   //����Ҫ����е��ַ�
			EnLinkQueue(&LQ, e);//�����
			DisplayLinkQueue(LQ, &queue);
			break;
		case 3:
			temp = DeLinkQueue(&LQ,&e);  //������
			if (temp == OK) {
				print_rp("Come out with one element:", 0,-1, clearflag);
				DisplayLinkQueue(LQ,&queue);
			}
			else
				print_rp("The queue is empty!",0, -1, clearflag);
			break;
		case 4:
			len = LinkQueueLength(&LQ);
			print_rp("The length of the queue is��", 0, -1, clearflag);
			print_rp(&len, 0, -1, 0);
			break;
		case back:back_back; flag = 0;		break;
		case main:back_main; flag = 0;  	break;
		case sure:queue_display_init();		break;
		default:break;
		}
	}
}

Status InitLinkQueue(LinkQueue *Q) {//���г�ʼ��
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode)); //����һ��ͷ��㣬������βָ��ָ��ͷ���
	Q->front->next = NULL;
	return OK;
}
Status DestroyLinkQueue(LinkQueue *Q) {//����һ������
	QueuePtr p;
	QElemType e;
	while (Q->front != Q->rear)
		DeLinkQueue(Q, e);
	free(Q->front);
	Q->front = Q->rear = NULL;
	return OK;
}

int LinkQueueLength(LinkQueue *Q) {//���еĳ���
	int i = 48;
	QueuePtr p = Q->front;
	while (p != Q->rear) {
		++i;
		p = p->next;
	}
	return i;
}

Status EnLinkQueue(LinkQueue *Q, QElemType e) {//�����
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));//����һ���½��
	p->data = e;                      //��ֵ
	p->next = NULL;
	Q->rear->next = p;                 //����������β
	Q->rear = p;                       //�޸Ķ�βָ��
	return OK;
}

Status DeLinkQueue(LinkQueue *Q, QElemType *e) {//������
	QueuePtr p;
	if (Q->front == Q->rear) return ERROR;     //�ж϶����Ƿ��ѿգ��ѿշ���ERROR
	p = Q->front->next;                      //pָ������е�һ��Ԫ��
	e = p->data;                            //ȡ�ø�Ԫ��ֵ
	Q->front->next = p->next;                //�޸Ķ���ָ��
	if (Q->rear == p) Q->rear = Q->front;         //�������ѿգ��Ѷ�βָ��ָ��ͷ���
	return OK;                            //�ɹ������У�����OK
}

Status DisplayLinkQueue(LinkQueue Q,char *queue) {//��ʾ����������Ԫ��
	QueuePtr p;
	int i = 48;
	p = Q.front->next;
	if (p == NULL) print_rp("The queue is empty!",0,-1, 0);//����Ϊ��
	else {

		while (p) {       //������ʾ����������Ԫ��
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
	GUI_SetColor(GUI_WHITE); //����������ɫ
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