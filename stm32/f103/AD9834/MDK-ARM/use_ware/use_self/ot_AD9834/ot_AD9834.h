#ifndef ot_AD9834_h
#define ot_AD9834_h
#include "sys.h"

typedef struct
{
	uint8_t msg_g[8];
}AD9834def;
	
void AD9834_task(void); 					
int16_t AD9834_action(void);
uint8_t get_link_msg(void);					//��ȡ�������豸��	
void esp8266_get(void);
#endif

