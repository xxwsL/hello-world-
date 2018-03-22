#include "sys_baseot.h"

//优化次数:0
//bmpname:bmp位置
//loadbuf:装载buf
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