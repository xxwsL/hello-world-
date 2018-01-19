#include "Date_get.h"
#include "usart3.h"
#include "commom.h"
#include "OLED.h"

u8 Date_buf[15]="xxwtset12345678";

void Datecard_task(void)
{
	u8 msg;
	
	if(usart_msg_action()==1)
	{
	msg=get_link_msg();
	esp8266_action(msg);
	OLED_Clear();
	OLED_center_dpy("xxwsL tip",1);
	OLED_Refresh_Gram();
		
	}
}
	
u8 get_link_msg(void)
{
	u8 *links;
	u8 msg=0;
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
		 
		msg|=link_action();	
		
		 return msg;
	}	
	
	return 0xff;
}


u8 link_action(void)
{
	if(atk_8266_check_cmd("xxwsL")!=0)
	{
		return 0x04;
	}
	return 0xff;
}

void esp8266_action(u8 msg)
{
	switch(msg&0x03)
	{
		case  0 : atk_8266_send_cmd("AT+CIPSEND=0,15","OK",20); break;
		case  1 : atk_8266_send_cmd("AT+CIPSEND=1,15","OK",20); break;
		case  2 : atk_8266_send_cmd("AT+CIPSEND=2,15","OK",20); break;
		case  3 : atk_8266_send_cmd("AT+CIPSEND=3,15","OK",20); break;
		default:break;
	}
	switch(msg&0xec)
	{
		case 0x04 : atk_8266_send_data(Date_buf,"OK",20);break;
		default	  :break;
	}
}






