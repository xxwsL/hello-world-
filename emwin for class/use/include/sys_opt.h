#ifndef sys_opt_h
#define sys_opt_h

#define task_max 6

//����������
#define back_main sys_main_windows()
#define back_back back_go()
#define task_face tasks_button_creat()
#define numpad_f numpad_creat()
#define Engpad_f Engpad_creat()

typedef struct key_group
{
	int action_ago;//��ǰ״̬
	int action_new;
	int action_will;//��Ҫ����
	int task_new;
}key_g_tpdef;

#endif // !sys_opt_h
