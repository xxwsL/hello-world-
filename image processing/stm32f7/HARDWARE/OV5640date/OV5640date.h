#ifndef _OV5640date_h_
#define _OV5640date_h_
#include "xxwsL.h"

#define yoffset 0;							//y方向的偏移量

#define Line_size	136			//定义DMA接收数据时,一行数据的最大值
#define Row_size	136			//定义DMA接收数据时,一行数据的最大值
					
#define small_line  17         //小块行维度
#define small_row   17         //小块列维度

void rgblcd_dcmi_rx_callback(void);
void rgb565_test(void);

#endif
