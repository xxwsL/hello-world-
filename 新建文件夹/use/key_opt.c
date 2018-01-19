#include "main.h"
#include "BUTTON.h"
#include "key_opt.h"

static const GUI_WIDGET_CREATE_INFO key_use[] = {
	{ BUTTON_CreateIndirect,   "Back",     back,     9 , y_lenght - back_y - 5, back_x, back_y},
	{ BUTTON_CreateIndirect,   "Numpad",   numpad,   24 + back_x, y_lenght - back_y - 5, back_x},
	{ BUTTON_CreateIndirect,   "Main",     main,    (x_lenght - back_x) / 2, y_lenght - back_y - 5, back_x, back_y },
	{ BUTTON_CreateIndirect,   "Engpad",   Engpad,	(x_lenght - back_x) / 2 + 71.5, y_lenght - back_y - 5, back_x, back_y },
	{ BUTTON_CreateIndirect,   "Sure",     sure,     x_lenght - back_x - 9, y_lenght - back_y - 5, back_x, back_y }
};


void key_creat();//创建按钮并定义属性
void numpad_creat();//创建数字键盘
void Engpad_creat();//创建Eng键盘
int get_keyvalue();//获得键值
char num_ch_Eng(int num);
void tasks_button_creat();//创建任务select界面


static void _cbDialog(WM_MESSAGE * pMsg) {
	int           NCode;
	int           Id;
	BUTTON_Handle hButton;

	switch (pMsg->MsgId) {
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);      // Id of widget
		NCode = pMsg->Data.v;                 // Notification code
		switch (NCode) {
		case WM_NOTIFICATION_RELEASED:      // React only if released
			if (Id == GUI_ID_BUTTON0) {       // Toggle callback

			} 
			if (Id == GUI_ID_BUTTON1) {       // Toggle callback

			}
			if (Id == GUI_ID_BUTTON2) {       // Toggle font

			}
			if (Id == GUI_ID_BUTTON3) {       // Toggle color

			}

			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void key_creat()
{
#ifdef key_edition1_0
	BUTTON_Handle Button_back, Button_numpad, Button_main,Button_Engpad, Button_sure;
	Button_back    = BUTTON_Create(9 , y_lenght-back_y-5, back_x, back_y, back, WM_CF_SHOW);
	BUTTON_SetText(Button_back,"Back");
	Button_numpad  = BUTTON_Create(24+ back_x, y_lenght - back_y - 5, back_x, back_y, numpad, WM_CF_SHOW);
	BUTTON_SetText(Button_numpad, "Numpad");
	Button_main    = BUTTON_Create((x_lenght - back_x) / 2, y_lenght - back_y - 5, back_x, back_y, main, WM_CF_SHOW);
	BUTTON_SetText(Button_main, "Main");
	Button_Engpad  = BUTTON_Create((x_lenght - back_x) / 2+71.5, y_lenght - back_y - 5, back_x, back_y, Engpad,WM_CF_SHOW);
	BUTTON_SetText(Button_Engpad, "Engpad");
	Button_sure    = BUTTON_Create(x_lenght-back_x-9, y_lenght-back_y-5, back_x, back_y, sure, WM_CF_SHOW);
	BUTTON_SetText(Button_sure, "Sure");
#endif

#ifdef key_edition2_0
	GUI_ExecDialogBox(key_use, GUI_COUNTOF(key_use), 0, 0, 0, 0);
#endif
}//这个按钮创建需要加强可移植性

void numpad_creat()
{
#ifdef key_edition1_0
	BUTTON_Handle Button_0, Button_1, Button_2, Button_3, Button_4, Button_5, Button_6, Button_7, Button_8, Button_9;
	creat_Rect(GUI_LIGHTBLUE);
	Button_0 = BUTTON_Create(1 * 20 + 0 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, 0, WM_CF_SHOW);
	BUTTON_SetText(Button_0, "0");
	Button_1 = BUTTON_Create(2 * 20 + 1 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, 1, WM_CF_SHOW);
	BUTTON_SetText(Button_1, "1");
	Button_2 = BUTTON_Create(3 * 20 + 2 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, 2, WM_CF_SHOW);
	BUTTON_SetText(Button_2, "2");
	Button_3 = BUTTON_Create(4 * 20 + 3 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, 3, WM_CF_SHOW);
	BUTTON_SetText(Button_3, "3");
	Button_4 = BUTTON_Create(5 * 20 + 4 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, 4, WM_CF_SHOW);
	BUTTON_SetText(Button_4, "4");
	Button_5 = BUTTON_Create(1 * 20 + 0 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, 5, WM_CF_SHOW);
	BUTTON_SetText(Button_5, "5");
	Button_6 = BUTTON_Create(2 * 20 + 1 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, 6, WM_CF_SHOW);
	BUTTON_SetText(Button_6, "6");
	Button_7 = BUTTON_Create(3 * 20 + 2 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, 7, WM_CF_SHOW);
	BUTTON_SetText(Button_7, "7");
	Button_8 = BUTTON_Create(4 * 20 + 3 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, 8, WM_CF_SHOW);
	BUTTON_SetText(Button_8, "8");
	Button_9 = BUTTON_Create(5 * 20 + 4 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, 9,WM_CF_SHOW);
	BUTTON_SetText(Button_9, "9");
#endif	
}

void Engpad_creat()
{
#ifdef key_edition1_0
	BUTTON_Handle Button_a, Button_b, Button_c, Button_d, Button_e, Button_f, Button_g, Button_h, Button_i, Button_j;
	creat_Rect(GUI_LIGHTBLUE);
	Button_a = BUTTON_Create(1 * 20 + 0 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, Engbase, WM_CF_SHOW);
	BUTTON_SetText(Button_a, "a");
	Button_b = BUTTON_Create(2 * 20 + 1 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, Engbase+1, WM_CF_SHOW);
	BUTTON_SetText(Button_b, "b");
	Button_c = BUTTON_Create(3 * 20 + 2 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, Engbase+2, WM_CF_SHOW);
	BUTTON_SetText(Button_c, "c");
	Button_d = BUTTON_Create(4 * 20 + 3 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, Engbase+3, WM_CF_SHOW);
	BUTTON_SetText(Button_d, "d");
	Button_e = BUTTON_Create(5 * 20 + 4 * num_x, y_lenght - back_y - 2 * num_y - 20, num_x, num_y, Engbase+4, WM_CF_SHOW);
	BUTTON_SetText(Button_e, "e");
	Button_f = BUTTON_Create(1 * 20 + 0 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, Engbase+5, WM_CF_SHOW);
	BUTTON_SetText(Button_f, "f");
	Button_g = BUTTON_Create(2 * 20 + 1 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, Engbase+6, WM_CF_SHOW);
	BUTTON_SetText(Button_g, "g");
	Button_h = BUTTON_Create(3 * 20 + 2 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, Engbase+7, WM_CF_SHOW);
	BUTTON_SetText(Button_h, "h");
	Button_i = BUTTON_Create(4 * 20 + 3 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, Engbase+8, WM_CF_SHOW);
	BUTTON_SetText(Button_i, "i");
	Button_j = BUTTON_Create(5 * 20 + 4 * num_x, y_lenght - back_y - 1 * num_y - 15, num_x, num_y, Engbase+9, WM_CF_SHOW);
	BUTTON_SetText(Button_j, "j");
#endif
}

int get_keyvalue()
{
#ifdef key_edition1_0
	int sign = 0;
do {
	GUI_Exec();
	sign = GUI_GetKey();
} while (sign == 0);
if(sign>= Engbase&&sign<Engbase +26)
{
	num_ch_Eng(sign);
}
else
return sign;
#endif
}

char num_ch_Eng(int num)
{
	return (char)(num - Engbase + 'a');;
}

void tasks_button_creat()
{
#ifdef key_edition1_0
	BUTTON_Handle Button_task1, Button_task2, Button_task3, Button_task4, Button_task5, Button_task6;
	creat_Rect(GUI_LIGHTBLUE);
	Button_task1 = BUTTON_Create((x_lenght - task_x) / 2, 34 + 0 * task_y + 1 * 10, task_x, task_y, task1, WM_CF_SHOW);
	BUTTON_SetText(Button_task1, "queue ot");
	Button_task2 = BUTTON_Create((x_lenght - task_x) / 2, 34 + 1 * task_y + 2 * 10, task_x, task_y, task2, WM_CF_SHOW);
	BUTTON_SetText(Button_task2, "Task2");
	Button_task3 = BUTTON_Create((x_lenght - task_x) / 2, 34 + 2 * task_y + 3 * 10, task_x, task_y, task3, WM_CF_SHOW);
	BUTTON_SetText(Button_task3, "Task3");
	Button_task4 = BUTTON_Create((x_lenght - task_x) / 2, 34 + 3 * task_y + 4 * 10, task_x, task_y, task4, WM_CF_SHOW);
	BUTTON_SetText(Button_task4, "Task4");
	Button_task5 = BUTTON_Create((x_lenght - task_x) / 2, 34 + 4 * task_y + 5 * 10, task_x, task_y, task5, WM_CF_SHOW);
	BUTTON_SetText(Button_task5, "Task5");
	Button_task6 = BUTTON_Create((x_lenght - task_x) / 2, 34 + 5 * task_y + 6 * 10, task_x, task_y, task6, WM_CF_SHOW);
	BUTTON_SetText(Button_task6, "Task6");
#endif
}



//u8 key_get()//对获得的键值判断
//{
//	u8 key_value;
//
//	kg.action = 0;
//
//	scanf("%c", &key_value);
//
//	if (kg.key_new == 0)
//	{
//		if (key_value == 'e')
//		{
//			kg.key_new = 1;
//			return kg.key_new;
//		}
//		else
//		{
//			return kg.key_new;
//		}
//	}
//	else if (kg.key_new>0)
//	{
//		if (key_value == 'q')
//		{
//			kg.key_new = 0;
//			return kg.key_new;
//		}
//		else
//		{
//			if (key_value == 'd')
//			{
//				kg.action = 1;
//			}
//			else if (key_value == 's'&&kg.key_new != task_max)
//			{
//				kg.key_new += 1;
//				return kg.key_new;
//			}
//			else if (key_value == 'w'&&kg.key_new != task_min)
//			{
//				kg.key_new -= 1;
//				return kg.key_new;
//			}
//			else
//			{
//				return kg.key_new;
//			}
//		}
//	}
//
//}