#pragma once
#ifndef _SEND_POKER_H_
#define _SEND_POKER_H_
#include<stdio.h>  
#include<time.h>  


#define POKER_NUM 10000  

int poker[POKER_NUM];

void iniPoker()
{
	for (int i = 0; i<POKER_NUM; i++)
	{
		poker[i] = i + 1;
	}
}
void suffle()
{
	for (int i = 0; i<POKER_NUM; i++)
	{
		int index = rand() % (POKER_NUM - i) + i;         //获取从i~POKER_NUM的一个索引  
		std::swap(poker[i], poker[index]);        //交换  
	}
}
void printPoker()
{
	for (int i = 0; i<POKER_NUM; i++)
	{
		if (i % 9 == 0) printf("\n");
		printf("%6d", poker[i]);
	}
}
void send_poker_test_fi (void)
{
	srand(time(NULL));
	iniPoker();
	printPoker();
	suffle();
	printf("\n-------------------------------------------------------------\n");
	printPoker();
}

#endif