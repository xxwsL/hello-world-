#include "sys_baseot.h"

//�Ż�����:0
//bmpname:bmpλ��
//loadbuf:װ��buf
bool bmp_r_tobuf(const char *bmpname,uint8_t *loadbuf, const uint32_t buf_size)
{
	FILE *fp = NULL;
	BITMAPFILEHEADER bmphead;
	BITMAPINFOHEADER bmpifo;
	if (fopen_s(&fp, bmpname, "rb"))
		return false;
	if (!fread(&bmphead, sizeof(bmphead), 1, fp))
		return false;
	if (!(fread(&bmpifo, sizeof(bmpifo), 1, fp)))
		return false;
	bmp_alignment_r(&bmpifo, loadbuf, buf_size, fp);
	fclose(fp);
	return true;
}

//�Ż�����:0
//bmpifo:bmp��Ϣ��
//loadbuf:װ��buf
//buf_size:buf��С(��λ:�ֽ�)
//fp:����bmp���ļ�ָ��
bool bmp_alignment_r(const BITMAPINFOHEADER *bmpifo,uint8_t *loadbuf,const uint32_t buf_size,FILE *fp)
{
	uint8_t free_width=NULL;
	float width_byte = NULL;
	uint8_t *loadbuf_add = NULL;
	uint32_t i = NULL,heigh_size=NULL;
	loadbuf_add = loadbuf;
	switch (bmpifo->biBitCount) {
	case 1:
		fseek(fp, 8, SEEK_CUR);
		break;
	case 4:
		fseek(fp, 64, SEEK_CUR);
		break;
	case 8:
		fseek(fp, 1024, SEEK_CUR);
		break;
	case 16:break;
	case 24:break;
	case 32:break;
	default:return false;
	}
	width_byte = (float)bmpifo->biWidth*bmpifo->biBitCount / 8;
	free_width = 4-((uint32_t)width_byte % 4);
	if (free_width) {
		heigh_size = (uint32_t)bmpifo->biHeight;
		for (i = 0; i < heigh_size; ++i) {
			fread(loadbuf_add, (size_t)width_byte,1,fp);
			loadbuf_add += (uint16_t)width_byte;
			fseek(fp, free_width, SEEK_CUR);
		}
	}
	else 
		fread(loadbuf, 1, buf_size, fp);
	return true;
}

//�Ż�����:0
//�������������ʼ��
//void:���β�
//return:����bool��־λ
bool rand_init(void)
{
	srand((unsigned int)time(NULL));
	return true;
}

//�Ż�����:0
//��ӡf32buf��txt
//path:txt·��
//buf:���ӡ��buf
//buf_size:buf�Ĵ�С
//return:bool��־
bool echo_f32buf_to_txt(const char *path,float *buf,uint32_t buf_size)
{
	uint32_t i = NULL;
	FILE *fp = NULL;
	fopen_s(&fp,path,"w");
	for (i = 0; i < buf_size; ++i) {
		if (!(i % 8))
			fprintf_s(fp, "\n");
		fprintf_s(fp, "%f,",buf[i]);
	}
	fprintf_s(fp, "\n\n");
	fclose(fp);
	return true;
}