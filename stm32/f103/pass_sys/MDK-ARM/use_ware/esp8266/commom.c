#include "commom.h"

//�û�������
//
//���Ӷ˿ں�:8086,�������޸�Ϊ�����˿�.
const uint8_t* portnum="8086";		 

//WIFI STAģʽ,����Ҫȥ���ӵ�·�������߲���,��������Լ���·��������,�����޸�.
const uint8_t* wifista_ssid="ALIENTEK";			//·����SSID��
const uint8_t* wifista_encryption="wpawpa2_aes";	//wpa/wpa2 aes���ܷ�ʽ
const uint8_t* wifista_password="15902020353"; 	//��������

//WIFI APģʽ,ģ���������߲���,�������޸�.
const uint8_t* wifiap_ssid="Date-get";			//����SSID��
const uint8_t* wifiap_encryption="wpawpa2_aes";	//wpa/wpa2 aes���ܷ�ʽ
const uint8_t* wifiap_password="12345678"; 		//�������� 

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//4������ģʽ
const uint8_t *ATK_ESP8266_CWMODE_TBL[3]={"STAģʽ ","APģʽ ","AP&STAģʽ "};	//ATK-ESP8266,3������ģʽ,Ĭ��Ϊ·����(ROUTER)ģʽ 
//4�ֹ���ģʽ
const uint8_t *ATK_ESP8266_WORKMODE_TBL[3]={"TCP������","TCP�ͻ���"," UDP ģʽ"};	//ATK-ESP8266,4�ֹ���ģʽ
//5�ּ��ܷ�ʽ
const uint8_t *ATK_ESP8266_ECN_TBL[5]={"OPEN","WEP","WPA_PSK","WPA2_PSK","WPA_WAP2_PSK"};

uint8_t ipbuf[16]=""; 	//IP����


void esp8266_init()
{
	uint8_t p[32]="";
	esp8266_IO_init();
	while(atk_8266_send_cmd("AT","OK",20))//���WIFIģ���Ƿ�����
	{
		atk_8266_quit_trans();//�˳�͸��
		atk_8266_send_cmd("AT+CIPMODE=0","OK",20);  //�ر�͸��ģʽ
		OLED_center_dpy("NO esp8266",1);
		OLED_center_dpy("Try linking",2);
		OLED_Refresh_Gram();		
	}
	while(atk_8266_send_cmd("ATE0","OK",20));//�رջ���
	
	atk_8266_send_cmd("AT+CWMODE=2","OK",20);
	atk_8266_send_cmd("AT+RST","OK",20);
	delay_ms(500);//��ʱ2s�ȴ�ģ������
	
	sprintf((char*)p,"AT+CWSAP=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);    //����ģ��APģʽ���߲���
	atk_8266_send_cmd(p,"OK",200);
	OLED_Clear();
	OLED_center_dpy("Linking succse",1);
	OLED_center_dpy("Module living",2);
	OLED_Refresh_Gram();
	delay_ms(200);
	
	atk_8266_send_cmd("AT+CIPMUX=1","OK",20);   //0�������ӣ�1��������	
	
	memset(p,0,sizeof(p));
	sprintf((char*)p,"AT+CIPSERVER=1,%s",(uint8_t*)portnum);
	while(atk_8266_send_cmd(p,"OK",20));     //����Serverģʽ���˿ں�Ϊ8086
	atk_8266_get_wanip(ipbuf);//������ģʽ,��ȡWAN IP
	
	OLED_Clear();
	OLED_center_dpy("Wifi date_get",0);
	OLED_center_dpy("passwd 12345678",1);
	OLED_center_dpy(ipbuf,2);
	OLED_Refresh_Gram();
	USART3_RX_STA=0;
	
}

void esp8266_IO_init()
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE7 PE9 PE11 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  PBout(12)=1;
  PBout(13)=1;
	
}

//��ATK-ESP8266��������
//cmd:���͵������ַ���
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
uint8_t atk_8266_send_cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime)
{
	uint8_t res=0; 
	USART3_RX_STA=0;
	u3_printf("%s\r\n",cmd);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(atk_8266_check_cmd(ack))
				{
//					printf("ack:%s\r\n",(uint8_t*)ack);
					break;//�õ���Ч���� 
				}
					USART3_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 

//ATK-ESP8266���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��
uint8_t *atk_8266_check_cmd(uint8_t *str)
{
	
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//���ӽ�����
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}

//ATK-ESP8266�˳�͸��ģʽ
//����ֵ:0,�˳��ɹ�;
//       1,�˳�ʧ��
uint8_t atk_8266_quit_trans(void)
{
	while((USART3->SR&0X40)==0);	//�ȴ����Ϳ�
	USART3->DR='+';      
	delay_ms(15);					//���ڴ�����֡ʱ��(10ms)
	while((USART3->SR&0X40)==0);	//�ȴ����Ϳ�
	USART3->DR='+';      
	delay_ms(15);					//���ڴ�����֡ʱ��(10ms)
	while((USART3->SR&0X40)==0);	//�ȴ����Ϳ�
	USART3->DR='+';      
	delay_ms(500);					//�ȴ�500ms
	return atk_8266_send_cmd("AT","OK",20);//�˳�͸���ж�.
}

//��ȡClient ip��ַ
//ipbuf:ip��ַ���������
void atk_8266_get_wanip(uint8_t* ipbuf)
{
	uint8_t *p,*p1;
		if(atk_8266_send_cmd("AT+CIFSR","OK",50))//��ȡWAN IP��ַʧ��
		{
			ipbuf[0]=0;
			return;
		}		
		p=atk_8266_check_cmd("\"");
		p1=(uint8_t*)strstr((const char*)(p+1),"\"");
		*p1=0;
		sprintf((char*)ipbuf,"%s",p+1);	
}

//��ATK-ESP8266����ָ������
//data:���͵�����(����Ҫ���ӻس���)
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)luojian
uint8_t atk_8266_send_data(uint8_t *data,uint8_t *ack,uint16_t waittime)
{
	uint8_t res=0; 
	USART3_RX_STA=0;
	u3_printf("%s",data);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(atk_8266_check_cmd(ack))break;//�õ���Ч���� 
				USART3_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
}

uint8_t get_link_msg(void)
{
	u8 *links;
	uint8_t msg=0;
	links=atk_8266_check_cmd("+IPD");
	if(links!=0)
	{
		 switch(*(links+5))
		 {
			 case '0' : msg|=0x00; break;
			 case '1' : msg|=0x01; break;
			 case '2' : msg|=0x02; break;
			 case '3' : msg|=0x03; break;
			 default  : msg =0xff; break;
		 }	
		 esp8266task;
		 return msg;
			 
		 
	}	
	
	return 0xff;
}

void esp8266_get(void)			//��ѧbug������debugѭ����
{
	switch(get_link_msg()&0x03)
	{
	case  0 : atk_8266_send_cmd("","OK",20); break;
	case  1 : atk_8266_send_cmd("","OK",20); break;
	case  2 : atk_8266_send_cmd("","OK",20); break;
	case  3 : atk_8266_send_cmd("","OK",20); break;
	default:break;
	}

}


