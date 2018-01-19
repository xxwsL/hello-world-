#include "ot_AD9834.h"

AD9834def AD9834str={"??f=????"};
void AD9834_task(void)
{
	if(usart_msg_action())         //接收到数据
	{
	esp8266_get();
	OLED_Clear();
	OLED_center_dpy("xxwsL tip",1);
	OLED_center_dpy(AD9834str.msg_g,2);
	OLED_Refresh_Gram();
	}
}


int16_t ot_AD9834(int16_t input) //15-5 频率系数；4-3 HZ,KHZ,MHZ；2 输出通道；1-0 波形 
{
	int16_t Wave;
	unsigned long freq=0;
	unsigned char ch;
	if(input==error)
	{
		return error;
	}
	freq=(unsigned long)((input&0xffe0)>>5);
	switch(input&0x0003)
	{
		case 0x0001:Wave=Sine_Wave;break;
		case 0x0002:Wave=Square_Wave;break;
		case 0x0003:Wave=Triangle_Wave;break;
		default:break;
	}
	switch(input&0x0004)
	{
		case 0x0000:ch=FREQ_0;break;
		case 0x0004:ch=FREQ_1;break;
		default:break;
	}
	switch(input&0x0018)
	{
		case 0x0008:break;
		case 0x0010:freq=1000*freq;break;
		case 0x0018:freq=1000000*freq;break;
		default:break;
	}
	AD9834_Select_Wave(Wave);//Sine_Wave  Square_Wave  Triangle_Wave
	AD9834_Set_Freq(ch, freq);
	return true;
}


int16_t AD9834_action(void) //explame s1f=100m;
{
	uint8_t reg=0;
	uint8_t *links;
	int16_t msg=0,i=1;
	int16_t temp=0;
	links=atk_8266_check_cmd("f=");
	if(links!=0)
	{
		switch(*(links-2))
		{
			case 's':msg|=0x0001;break;
			case 'q':msg|=0x0002;break;
			case 't':msg|=0x0003;break;
			default:return error;
		}
		switch(*(links-1))
		{
			case '0':			 break;
			case '1':msg|=0x0004;break;
			default:return error;
		}
		reg=*(links-4)-51;
		switch(*(links+reg))
		{
			case 'h':msg|=0x0008;break;
			case 'k':msg|=0x0010;break;
			case 'm':msg|=0x0018;break;
			default:return error;
		}	
		reg-=2;
		if(reg>3)
		{
			return error;
		}
		while(reg)
		{
			temp+=(int16_t)(*(links+reg+1)-48)*i;
			i*=10;
			reg--;
		}
		sprintf((char*)AD9834str.msg_g,"%s",(links-2));
		msg|=(temp<<5);
	}
	return msg;
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

void esp8266_get(void)			//玄学bug，不加debug循环，
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



