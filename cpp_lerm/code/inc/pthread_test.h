#pragma comment(lib,"pthreadVC2.lib")
#ifndef _PTHREAD_TEST_H_
#define _PTHREAD_TEST_H_
#include <iostream>  
#include <pthread.h> //多线程相关操作头文件，可移植众多平台  
#include <Windows.h>

using namespace std;

#define NUM_THREADS 3

void *PrintHello(void *args)
{
	int thread_arg;
	thread_arg =*((int*)args);
	Sleep(10000);
	printf("Hello from thread %d\n", thread_arg);
	return NULL;
}

void pthread_join_test(pthread_t& thread, int t)
{
	pthread_join(thread, NULL);
	printf("当前线程 %d 执行完成\n", t);
}

void pthread_test_fi0(void)
{
	int rc;
	pthread_t thread[NUM_THREADS];

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for (int t = 0; t < NUM_THREADS; t++)
	{
		printf("Creating thread %d\n", t);
		rc = pthread_create(&thread[t], &attr, PrintHello, &t);
		if (rc)
		{
			printf("ERROR; return code is %d\n", rc);
		}
	}
	for (int t = 0; t < NUM_THREADS; t++)
		pthread_join(thread[t], NULL);
}


#endif // !_PTHREAD_TEST_H_