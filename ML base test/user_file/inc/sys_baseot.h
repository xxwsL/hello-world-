#ifndef _sys_baseot_h_
#define _sys_baseot_h_
#include "xxwsL.h"

//读取bmp像素到buf
bool bmp_r_tobuf(const char *bmpname, uint8_t *loadbuf, const uint32_t buf_size);
//读取bmp像素对齐
bool bmp_alignment_r(const BITMAPINFOHEADER *bmpifo, uint8_t *loadbuf, const unsigned int buf_size, FILE *fp);
//随机数产生器初始化
bool rand_init(void);

#endif




