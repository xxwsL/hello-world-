#pragma once
#ifndef _GINSENG_TEST_H_
#define _GINSENG_TEST_H_

#include <xxwsL.h>
#include <utility> 


void rvalue_reference(void) {
	int i = 2;
	int &lr = i;
	int &&rr = i * 3;
	const int &lr1 = i * 3;
	int &&rr1 = 5;
	int &&rr2 = std::move(lr);
	std::cout << "i = " << i << std::endl;
	std::cout << "lr = " << lr << std::endl;
	std::cout << "rr = " << rr << std::endl;
	std::cout << "lr1 = " << lr1 << std::endl;
	std::cout << "rr1  = " << rr1 << std::endl;
	std::cout << "rr2  = " << rr2 << std::endl;
	std::cout << "lr = " << lr << std::endl;
}

int  q(int&& x) {
	int y = x;
	x = 4;
	y = 5;
	return y;
}

void ginseng_test_fi(void)
{
	int x = 2, y = 3;
	rvalue_reference();
	cout << q(x + y) << x << y;
	while (1);
}
#endif // !_GINSENG_TEST_H_
