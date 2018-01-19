#ifndef commom_h
#define commom_h
#include "sys.h"

#define AT_MODE_CONFIG		0				//0,采用ES/RST硬件控制进入AT模式;
											//1,采用串口特殊序列(+++1B1B1B)进入AT模式

//用户配置参数
extern const uint8_t* portnum;			//连接端口
 
extern const uint8_t* wifista_ssid;		//WIFI STA SSID
extern const uint8_t* wifista_encryption;//WIFI STA 加密方式
extern const uint8_t* wifista_password; 	//WIFI STA 密码

extern const uint8_t* wifiap_ssid;		//WIFI AP SSID
extern const uint8_t* wifiap_encryption;	//WIFI AP 加密方式
extern const uint8_t* wifiap_password; 	//WIFI AP 密码

extern uint8_t* kbd_fn_tbl[2];
extern const uint8_t* ATK_ESP8266_CWMODE_TBL[3];
extern const uint8_t* ATK_ESP8266_WORKMODE_TBL[3];
extern const uint8_t* ATK_ESP8266_ECN_TBL[5];

void esp8266_init(void);							//esp8266初始化
void esp8266_IO_init(void);							//esp8266IO口初始化

uint8_t atk_8266_send_cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime); 	//向esp8266发送指令 
uint8_t atk_8266_send_data(uint8_t *data,uint8_t *ack,uint16_t waittime);	//想links发生数据
uint8_t *atk_8266_check_cmd(uint8_t *str);						//检测应答结果

uint8_t atk_8266_quit_trans(void);						//退出透传模式
void atk_8266_get_wanip(uint8_t* ipbuf);					//获取IP
uint8_t get_link_msg(void);
void esp8266_get(void);

#endif

