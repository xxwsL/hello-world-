#include "main.h"
#include "sys_opt.h"
#include "key_opt.h"
#include "BUTTON.h"
#include "queue_ot.h"

key_g_tpdef kg_structure;

void sys_init(void);//系统初始化
void opt_sw(int key_sign);//系统选择开关，支持重入使用
void windows_change();//窗口选择执行
void dat_clear(void);//数据清除
void back_go(void);//返回上一级函数
void task_cameback(int task_num);//任务回调函数


void task_cameback(int task_num)
{
	kg_structure.task_new = task_num;
	switch (task_num)
	{
	case task1:queue_otfn(); break;
	case task2:break;
	case task3:break;
	case task4:break;
	case task5:break;
	case task6:break;
	}
	kg_structure.task_new = 0;
}

void sys_init(void)
{
	GUI_Init();
	if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
		GUI_ErrorOut("Not enough memory available.");
		return;
	}
	kg_structure.action_new = main;
	sys_main_windows();
}

void opt_sw(int key_sign)
{
	if (key_sign>=task1&&key_sign<task1+task_max)
	{
		task_cameback(key_sign);
	}
	else
	{
		switch (key_sign)
		{
		case keep:                                    break;
		case back:   back_back;                       break;
		case numpad: numpad_f;                  break;
		case main:   back_main;                       break;
		case Engpad: Engpad_f;                  break;
		case sure:  task_face;						  break;
		default:break;
		}
	}
}

void back_go()
{
	if (kg_structure.task_new == 0)
	{
		if (kg_structure.action_new != main)
		{
			back_main;
			kg_structure.action_new = main;
		}
	}
	else
	{
		task_face;
		kg_structure.action_new = sure;
	}
}

void windows_change()
{
	int key_sign = 0;
	key_sign = get_keyvalue();
	opt_sw(key_sign);
	kg_structure.action_ago = kg_structure.action_new;
	kg_structure.action_new = key_sign;

}

void dat_clear()
{

}
//
//void task_runing(struct key_group *kg_point)
//{
//	if (kg_point->action == 1)
//	{
//		switch (kg_point->key_new)
//		{
//		case 1:display_poied_max(); break;
//		case 2:wrielist_init();    break;
//		case 3:chainlist_init();     break;
//		default:break;
//		}
//	}
//}








