#pragma once
#ifndef _AUTO_TEST_H_
#define _AUTO_TEST_H_
#include <xxwsL.h>

//��auto��ʼ��ģ�溯��
template <class T, class U>
auto Multiply(T t, U u)
{
	return t * u;

}

void auto_t0(void)
{
	//��auto��ʼ������
	auto ptr = [](uint16_t i)
	{
		std::cout << "hello world = " << i << std::endl;
		return true;
	};
	ptr(1);
}

void auto_test_fi(void)
{
	int a[9];
	auto j = a;
	cout << typeid(j).name() << endl; // This will print int*  

	auto& k = a;
	cout << typeid(k).name() << endl; // This will print int [9] 
}

#endif // !_AUTO_TEST_H_