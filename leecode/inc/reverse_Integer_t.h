#pragma once
#ifndef _reverse_integer_t_h_
#define _reverse_integer_t_h_

#include <limits.h>
#include <iostream>

using namespace std;

int reverse_integer_t_fi(int x) { 
	cout << ">> this is reverse_integer test\n";
	int y = 0, pop;
	const auto INT_MAX_10 = INT_MAX / 10;
	const auto INT_MIN_10 = INT_MIN / 10;
	while (x != 0) {
		pop = x % 10;
		x /= 10;
		if(y > INT_MAX_10 || (y == INT_MAX_10) && (pop > 7))
			return 0;
		if(y < INT_MIN_10 || (y == INT_MIN_10) && (pop < -8))
			return 0;
		y = y * 10 + pop;
	}	
	return y;
}
#endif // !_Reverse_Integer_test_h_

