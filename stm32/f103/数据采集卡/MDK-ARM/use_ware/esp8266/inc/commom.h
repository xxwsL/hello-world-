#ifndef commom_h
#define commom_h
#include "sys.h"

#define AT_MODE_CONFIG		0				//0,����ES/RSTӲ�����ƽ���ATģʽ;
											//1,���ô�����������(+++1B1B1B)����ATģʽ

//�û����ò���
extern const u8* portnum;			//���Ӷ˿�
 
extern const u8* wifista_ssid;		//WIFI STA SSID
extern const u8* wifista_encryption;//WIFI STA ���ܷ�ʽ
extern const u8* wifista_password; 	//WIFI STA ����

extern const u8* wifiap_ssid;		//WIFI AP SSID
extern const u8* wifiap_encryption;	//WIFI AP ���ܷ�ʽ
extern const u8* wifiap_password; 	//WIFI AP ����

extern u8* kbd_fn_tbl[2];
extern const u8* ATK_ESP8266_CWMODE_TBL[3];
extern const u8* ATK_ESP8266_WORKMODE_TBL[3];
extern const u8* ATK_ESP8266_ECN_TBL[5];

void esp8266_init(void);							//esp8266��ʼ��
void esp8266_IO_init(void);							//esp8266IO�ڳ�ʼ��

u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime); 	//��esp8266����ָ�� 
u8 atk_8266_send_data(u8 *data,u8 *ack,u16 waittime);	//��links��������
u8* atk_8266_check_cmd(u8 *str);						//���Ӧ����

u8 atk_8266_quit_trans(void);						//�˳�͸��ģʽ
void atk_8266_get_wanip(u8* ipbuf);					//��ȡIP

#endif

