#ifndef Date_get_h
#define Date_get_h
#include "sys.h"

extern u8 Date_buf[15];

void Datecard_task(void); 					//���ݲɼ�������
	
u8 get_link_msg(void);					//��ȡ�������豸��
u8 link_action(void);					//��ȡ��������
void esp8266_action(u8 msg);			//esp8266ִ������

#endif

