#include "main.h"
#include "key_opt.h"
#include "sys_display.h"
#include "string.h"

GUI_RECT Rect = { 0, Rect_base, x_lenght, y_lenght - back_y - 2 * num_y - 25 };
int lines,rows;

void alldisplay_clear(u32 color);					//ȫ��clear
void sys_main_windows(void);					//����������ʾ
void creat_Rect(u16 clor);						//����һ���ı�
void scanf_repli(char new_line);				// �ع����뺯��
void printf_repli(char *acText, int x, int y, u8 clear_flag);	//�ع��������
void Rcet_reinit(void);

void Rcet_reinit()
{
	creat_Rect(GUI_BLACK);
	lines = 0;
	rows = 0;
}

void scanf_repli(char new_line)
{
	get_keyvalue();
}

void printf_repli(char *acText,int x, int y, u8 clear_flag)
{
	int str_l;
	if (lines > lines_max || clear_flag)
	{
		Rcet_reinit();
	}
	GUI_SetColor(GUI_WHITE);//����������ɫ
	GUI_SetFont(&GUI_Font20_ASCII);
	str_l = strlen(acText);
	if ((x < 0) || (y < 0))
	{
		if((x < 0) && ( y < 0))
		{
			if ((str_l + rows) > (rows_max+1))
			{
				if (lines ==lines_max)
				{
					Rcet_reinit();
					GUI_DispStringAt(acText, rows * 20, Rect_base + lines * 20);
					rows += str_l;
				}
				else
				{
					rows = 0;
					lines ++;
					GUI_DispStringAt(acText, rows * 20, Rect_base + lines * 20);
					rows += str_l;
				}
			}
			else
			{
				GUI_DispStringAt(acText, rows * 20, Rect_base + lines * 20);
				rows += str_l;
			}
		}

		else if (x < 0&&y>=0)
		{
			GUI_DispStringAt(acText, rows*20,y);
			rows += str_l;
		}
		else if(y<0&&x>=0)
		{
			GUI_DispStringAt(acText, x, Rect_base + lines*20);
			lines++;
		}
	}
	else
	{
		GUI_DispStringAt(acText, x, y);
	}
}

//void printf_repli(char *acText, int Ali_mode, int dpy_mode)
//{
//	creat_Rect(GUI_BLACK);
//	GUI_SetColor(GUI_WHITE); //����������ɫ
//	GUI_SetFont(&GUI_Font20_ASCII);
//	GUI_DispStringInRectWrap(acText, &Rect, Ali_mode, dpy_mode);
//}

void alldisplay_clear(u32 color)
{
	GUI_SetBkColor(color);
	GUI_Clear();
}

void sys_main_windows()
{
	creat_Rect(GUI_LIGHTBLUE);
	alldisplay_clear(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_DispStringHCenterAt("edition By XXW 2.0", x_lenght / 2, 5);//������ʾ
	key_creat();
	dat_clear();
	
}

void creat_Rect(u16 clor)
{
	GUI_SetColor(clor);
	GUI_FillRectEx(&Rect);
}


