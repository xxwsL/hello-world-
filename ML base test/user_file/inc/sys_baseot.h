#ifndef _sys_baseot_h_
#define _sys_baseot_h_
#include "xxwsL.h"

//��ȡbmp���ص�buf
bool bmp_r_tobuf(const char *bmpname, uint8_t *loadbuf, const uint32_t buf_size);
//��ȡbmp���ض���
bool bmp_alignment_r(const BITMAPINFOHEADER *bmpifo, uint8_t *loadbuf, const unsigned int buf_size, FILE *fp);
//�������������ʼ��
bool rand_init(void);

#endif




