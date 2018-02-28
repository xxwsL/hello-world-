#include "OV5640.h"

u16 curline=0;							//����ͷ�������,��ǰ�б��
u32 dcmi_line_buf[2][Line_size];	//RGB��ʱ,����ͷ����һ��һ�ж�ȡ,�����л���  
u16 dcmi_buf[Row_size][Line_size];	//һ֡����buffer

float small_buf[small_line][small_row];
MatStr small_mat=MatrixInit(small_buf);

//RGB�����ݽ��ջص�����
void rgblcd_dcmi_rx_callback(void)
{  
	u16 *pbuf;
	u16 i;
	if(DMA2_Stream1->CR&(1<<19)){	//DMAʹ��buf1,��ȡbuf0
		pbuf=(u16*)dcmi_line_buf[0]; 
	}
	else{ 							//DMAʹ��buf0,��ȡbuf1
		pbuf=(u16*)dcmi_line_buf[1]; 
	} 	
//	LTDC_Color_Fill(0,curline,lcddev.width-1,curline,pbuf);//DM2D���
    for(i=0;i<Line_size;i++){
		dcmi_buf[curline][i]=*(pbuf+i);
	}
	if(curline<Row_size-1){
		curline++;
	}
//	else{
//		curline=0;
//	}		
}

void rgb565_test(void)
{
	u8 test_flag=0;
	u16 line=0;
	u8 key=0;
	
	OV5640_RGB565_Mode();	//RGB565ģʽ	
	OV5640_Focus_Init();
	OV5640_Light_Mode(0);	//�Զ�ģʽ
	OV5640_Color_Saturation(3);//ɫ�ʱ��Ͷ�0
	OV5640_Brightness(4);	//����0
	OV5640_Contrast(3);		//�Աȶ�0
	OV5640_Sharpness(33);	//�Զ����
	OV5640_Focus_Constant();//���������Խ�
	DCMI_Init();			//DCMI����
	
	dcmi_rx_callback=rgblcd_dcmi_rx_callback;//RGB���������ݻص�����
	DCMI_DMA_Init((u32)dcmi_line_buf[0],(u32)dcmi_line_buf[1],Line_size/2,1,1);//DCMI DMA���� 

	OV5640_OutSize_Set(4,0,Line_size,Row_size);		//����������ʾ
	DCMI_Start(); 
	
	while(1)
	{ 
		key=KEY_Scan(0); 
		if(test_flag)
			{
				LED1(1);
				for(line=0;line<Row_size;line++)
				{
					LTDC_Color_Fill(0,line,Line_size,line,(u16*)dcmi_buf[line]);
				}
				test_flag=0;
				LED0(1);
			}
		if(key)
		{ 
			if(key==KEY0_PRES)
			{
				test_flag=1;
				LED0(0);
			}
		} 
		delay_ms(10);		
	}  
	
}

char get_small_buf(float* buf)
{
	
	return true;
}














