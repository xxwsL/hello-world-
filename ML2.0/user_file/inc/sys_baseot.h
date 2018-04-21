#ifndef _sys_baseot_h_
#define _sys_baseot_h_
#include "xxwsL.h"

//����һά���鳤��
#define buf_len_1(buf_name) sizeof(buf_name)/sizeof(buf_name[0])
//�����ά���鳤��
#define buf_len_2(buf_name) sizeof(buf_name)/sizeof(buf_name[0][0])

//��ȡbmp���ص�buf
int bmp_r_tobuf(const char *bmpname, uint8_t *loadbuf, const uint32_t buf_size);
//��ȡbmp���ض���
int bmp_alignment_r(const BITMAPINFOHEADER *bmpifo, uint8_t *loadbuf, const unsigned int buf_size, FILE *fp);
//�������������ʼ��
int rand_init(void);
//��ӡbuf��txt�ļ�
int echo_f32buf_to_txt(const char *path, float *buf, uint32_t buf_size);

#endif




