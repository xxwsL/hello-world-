#ifndef _sys_baseot_h_
#define _sys_baseot_h_
#include "xxwsL.h"

//计算一维数组长度
#define buf_len_1(buf_name) sizeof(buf_name)/sizeof(buf_name[0])
//计算二维数组长度
#define buf_len_2(buf_name) sizeof(buf_name)/sizeof(buf_name[0][0])

//读取bmp像素到buf
bool bmp_r_tobuf(const char *bmpname, uint8_t *loadbuf, const uint32_t buf_size);
//读取bmp像素对齐
bool bmp_alignment_r(const BITMAPINFOHEADER *bmpifo, uint8_t *loadbuf, const unsigned int buf_size, FILE *fp);
//随机数产生器初始化
bool rand_init(void);
//打印buf到txt文件
bool echo_f32buf_to_txt(const char *path, float *buf, uint32_t buf_size);
//读bmp像素到buf
bool read_bmp_to_buf(const char *simaple_file, const uint32_t i, MatrixStr *mat);
//读bmp的初始化
bool read_bmp_init(uint32_t buf_size);

#endif




