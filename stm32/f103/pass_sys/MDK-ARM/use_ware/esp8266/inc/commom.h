#ifndef commom_h
#define commom_h
#include "sys.h"

#define AT_MODE_CONFIG		0				//0,����ES/RSTӲ�����ƽ���ATģʽ;
											//1,���ô�����������(+++1B1B1B)����ATģʽ

//�û����ò���
extern const uint8_t* portnum;			//���Ӷ˿�
 
extern const uint8_t* wifista_ssid;		//WIFI STA SSID
extern const uint8_t* wifista_encryption;//WIFI STA ���ܷ�ʽ
extern const uint8_t* wifista_password; 	//WIFI STA ����

extern const uint8_t* wifiap_ssid;		//WIFI AP SSID
extern const uint8_t* wifiap_encryption;	//WIFI AP ���ܷ�ʽ
extern const uint8_t* wifiap_password; 	//WIFI AP ����

extern uint8_t* kbd_fn_tbl[2];
extern const uint8_t* ATK_ESP8266_CWMODE_TBL[3];
extern const uint8_t* ATK_ESP8266_WORKMODE_TBL[3];
extern const uint8_t* ATK_ESP8266_ECN_TBL[5];

void esp8266_init(void);							//esp8266��ʼ��
void esp8266_IO_init(void);							//esp8266IO�ڳ�ʼ��

uint8_t atk_8266_send_cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime); 	//��esp8266����ָ�� 
uint8_t atk_8266_send_data(uint8_t *data,uint8_t *ack,uint16_t waittime);	//��links��������
uint8_t *atk_8266_check_cmd(uint8_t *str);						//���Ӧ����

uint8_t atk_8266_quit_trans(void);						//�˳�͸��ģʽ
void atk_8266_get_wanip(uint8_t* ipbuf);					//��ȡIP
uint8_t get_link_msg(void);
void esp8266_get(void);

#endif

