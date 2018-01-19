#ifndef __USART3_H
#define __USART3_H 
#include "sys.h"	  

#define USART3_MAX_RECV_LEN		800					//�����ջ����ֽ���
#define USART3_MAX_SEND_LEN		800					//����ͻ����ֽ���
#define USART3_RX_EN 			1					//0,������;1,����.

extern uint8_t  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern uint8_t  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern __IO uint16_t USART3_RX_STA;   						//��������״̬

void usart3_init(uint32_t pclk1,uint32_t bound);
void u3_printf(char* fmt,...);

uint8_t usart_msg_action(void);//���ڴ�����
	
#endif	   
















