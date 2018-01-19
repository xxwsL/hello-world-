#include "pass.h"

PassDef PassStr={PassNewDef};

int16_t pass_task(void)
{
	pass_action();
	return true;
}

void Pass_init(void)
{
	pass_gpio_init();
	pass_display();
}

void pass_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PC6 PC7 */
  GPIO_InitStruct.Pin = Hin|Lin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull= GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

int16_t pass_action(void)
{
	
	static uint8_t flag;
	if(usart_msg_action())
	{
		esp8266_get();
		pass_display();
		return true;
	}
	else if(!flag)
	{
		if(PBin(HinNums)&&(!PBin(LinNums)))
		{
			PassStr.PassNew++;
			pass_display();
			flag=1;
		}
		if(PBin(LinNums)&&(!PBin(HinNums)))
		{
			if(PassStr.PassNew>0)
			{
				PassStr.PassNew--;
				pass_display();
				flag=1;
			}
		}
		
	}
	else if((PBin(HinNums))&&(PBin(LinNums)))
	{
		flag=0;
	}
	return false;
}

int8_t comman_pass(void) 
{
	uint8_t *links;
	int16_t tempd0=0;
	if(atk_8266_check_cmd("rst"))
	{
		PassStr.PassNew=0;
		OLED_Clear();
		OLED_center_dpy("false",3);
		OLED_Refresh_Gram();
		return true;
	}
	links=atk_8266_check_cmd("set");
	if(links)
	{
		tempd0+=((*(links+3)-48))*100; //
		tempd0+=((*(links+4)-48))*10;
		tempd0+=((*(links+5)-48));
		PassStr.PassNew=tempd0;
		return true;
	}
	return false;
}

void pass_display(void)
{
	uint8_t temps1[9];
	uint8_t temps2[9];
	int16_t tempd1;
	
	tempd1=PassMaxDef-PassStr.PassNew;
	sprintf((char*)temps1,"Free %c%c%c",(tempd1/100+48),(tempd1/10%10+48),(tempd1%10+48));
	sprintf((char*)temps2,"Busy %c%c%c",(PassStr.PassNew/100+48),(PassStr.PassNew/10%10+48),(PassStr.PassNew%10+48));
	OLED_Clear();
	OLED_center_dpy("xxwsL tip",0);
	OLED_center_dpy(temps1,1);
	OLED_center_dpy(temps2,2);
	if(PassStr.PassNew>400)
	{
		OLED_center_dpy("Full",3);
	}
	else
	{
		OLED_center_dpy("Null",3);
	}
	OLED_Refresh_Gram();
}


