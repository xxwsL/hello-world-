#include "sys_baseot.h"

uint8_t *bmp_buf = NULL;
uint32_t bmp_buf_size = NULL;

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

//优化次数:0
//bmpifo:bmp信息表
//loadbuf:装载buf
//buf_size:buf大小(单位:字节)
//fp:打开了bmp的文件指针
bool bmp_alignment_r(const BITMAPINFOHEADER *bmpifo,uint8_t *loadbuf,const uint32_t buf_size,FILE *fp)
{
	uint8_t free_width=NULL;
	float width_byte = NULL;
	uint8_t *loadbuf_add = NULL;
	uint32_t i = NULL,heigh_size=NULL;
	loadbuf_add = loadbuf;
	//bmp位深度
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
	//bmp图片一行的字节数
	width_byte = (float)bmpifo->biWidth*bmpifo->biBitCount / 8;
	//bmp像素存储各式,4的倍数(即以long为单位),不足的以0填充
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

//优化次数:0
//随机数产生器初始化
//void:无形参
//return:返回bool标志位
bool rand_init(void)
{
	srand((unsigned int)time(NULL));
	return true;
}

//优化次数:0
//打印f32buf到txt
//path:txt路劲
//buf:需打印的buf
//buf_size:buf的大小
//return:bool标志
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

//优化次数:1
//读bmp像素到buf
bool read_bmp_to_buf(const char *simaple_file, const uint32_t i, MatrixStr *mat)
{
	char bmp_data[100] = {};
	char bmp_name[9] = {};
	if (i < 10) {
		bmp_name[0] = (char)(i + 48);
		bmp_name[1] = '.'; bmp_name[2] = 'b'; bmp_name[3] = 'm'; bmp_name[4] = 'p';
	}
	else if (i < 100) {
		bmp_name[0] = (char)(i / 10 + 48);
		bmp_name[1] = (char)(i % 10 + 48);
		bmp_name[2] = '.'; bmp_name[3] = 'b'; bmp_name[4] = 'm'; bmp_name[5] = 'p';
	}
	else if (i < 1000) {
		bmp_name[0] = (char)(i / 100 + 48);
		bmp_name[1] = (char)(i / 10 % 10 + 48);
		bmp_name[2] = (char)(i % 10 + 48);
		bmp_name[3] = '.'; bmp_name[4] = 'b'; bmp_name[5] = 'm'; bmp_name[6] = 'p';
	}
	else if (i < 10000) {
		bmp_name[0] = (char)(i / 1000 + 48);
		bmp_name[1] = (char)(i / 100 % 10 + 48);
		bmp_name[2] = (char)(i / 10 % 10 + 48);
		bmp_name[3] = (char)(i % 10 + 48);
		bmp_name[4] = '.'; bmp_name[5] = 'b'; bmp_name[6] = 'm'; bmp_name[7] = 'p';
	}
	else if (i < 100000) {
		bmp_name[0] = (char)(i / 10000 + 48);
		bmp_name[1] = (char)(i / 1000 % 10 + 48);
		bmp_name[2] = (char)(i / 100 % 10 + 48);
		bmp_name[3] = (char)(i / 10 % 10 + 48);
		bmp_name[4] = (char)(i % 10 + 48);
		bmp_name[5] = '.'; bmp_name[6] = 'b'; bmp_name[7] = 'm'; bmp_name[8] = 'p';
	}
	sprintf(bmp_data, "%s%s", simaple_file, bmp_name);
	bmp_r_tobuf(bmp_data, bmp_buf, bmp_buf_size);
	mat_tovector(bmp_buf, mat);
	f32mat_up_down_change(mat);
	return true;
}

//读bmp的初始化
bool read_bmp_init(uint32_t buf_size)
{
	bmp_buf = new uint8_t[buf_size];
	bmp_buf_size = buf_size;
	if (bmp_buf)
		return false;
	else
		return true;
}