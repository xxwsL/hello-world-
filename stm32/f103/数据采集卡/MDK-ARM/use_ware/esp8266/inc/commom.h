#ifndef commom_h
#define commom_h
#include "sys.h"

#define AT_MODE_CONFIG		0				//0,采用ES/RST硬件控制进入AT模式;
											//1,采用串口特殊序列(+++1B1B1B)进入AT模式

//用户配置参数
extern const u8* portnum;			//连接端口
 
extern const u8* wifista_ssid;		//WIFI STA SSID
extern const u8* wifista_encryption;//WIFI STA 加密方式
extern const u8* wifista_password; 	//WIFI STA 密码

extern const u8* wifiap_ssid;		//WIFI AP SSID
extern const u8* wifiap_encryption;	//WIFI AP 加密方式
extern const u8* wifiap_password; 	//WIFI AP 密码

extern u8* kbd_fn_tbl[2];
extern const u8* ATK_ESP8266_CWMODE_TBL[3];
extern const u8* ATK_ESP8266_WORKMODE_TBL[3];
extern const u8* ATK_ESP8266_ECN_TBL[5];

void esp8266_init(void);							//esp8266初始化
void esp8266_IO_init(void);							//esp8266IO口初始化

u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime); 	//向esp8266发送指令 
u8 atk_8266_send_data(u8 *data,u8 *ack,u16 waittime);	//想links发生数据
u8* atk_8266_check_cmd(u8 *str);						//检测应答结果

u8 atk_8266_quit_trans(void);						//退出透传模式
void atk_8266_get_wanip(u8* ipbuf);					//获取IP

#endif

