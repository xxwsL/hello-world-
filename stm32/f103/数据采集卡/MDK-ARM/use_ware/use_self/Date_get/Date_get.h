#ifndef Date_get_h
#define Date_get_h
#include "sys.h"

extern u8 Date_buf[15];

void Datecard_task(void); 					//数据采集卡任务
	
u8 get_link_msg(void);					//获取发明了设备号
u8 link_action(void);					//获取操作命令
void esp8266_action(u8 msg);			//esp8266执行命令

#endif

