#ifndef _OV5640date_h_
#define _OV5640date_h_
#include "xxwsL.h"

#define yoffset 0;							//y�����ƫ����

#define Line_size	136			//����DMA��������ʱ,һ�����ݵ����ֵ
#define Row_size	136			//����DMA��������ʱ,һ�����ݵ����ֵ
					
#define small_line  17         //С����ά��
#define small_row   17         //С����ά��

void rgblcd_dcmi_rx_callback(void);
void rgb565_test(void);

#endif
