#include "voiceot.h"

VB LowVBstr={LowVStDef,LowVMinDef,LowVMidDef,LowVMaxDef,LowVMaxhDef,0};
VB HightVBstr={HightVStDef,HightVMinDef,HightVMidDef,HightVMaxDef,HightVMaxhDef,0};

void voiceot_init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOH, ENABLE); 	//初始化GPIOG时钟	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   //输入模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	//下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度选择
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	 
	GPIO_Init(GPIOH, &GPIO_InitStructure);	
}

int8_t voiveot_value(uint16_t voicei,VB *VBstr_p)
{
	uint8_t revalue;
	
	if(voicei>VBstr_p->VoiceBaseMid)
	{
		if(voicei>VBstr_p->VoiceBaseMaxh)
		{
			revalue=4;
		}
		else if(voicei>VBstr_p->VoiceBaseMax)
		{
			revalue=3;
		}
		else
		{
			revalue=2;
		}
	}	
	else if(voicei>VBstr_p->VoiceBaseMin)
	{

		revalue=1;
	}
	else if(voicei>VBstr_p->VoiceBaseSt)
	{
		revalue=0;
	}
	else
	{
		return error;
	}

	
	return revalue;
}

int8_t voice_lowot(uint16_t voicei)
{
	int8_t temp;
	temp=voiveot_value(voicei,&LowVBstr);
	if(temp==error)
		return error;
	else
		return (temp+5);

}

int8_t voice_hightot(uint16_t voicei)
{
	int8_t temp;
	temp=voiveot_value(voicei,&HightVBstr);
	if(temp==error)
		return error;
	else
		return (temp+10);
}

int8_t DO_ot(void)
{
	return GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_5);
}










	












