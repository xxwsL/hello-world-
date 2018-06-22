#pragma once
#ifndef _CLASS_TEST_H_
#define _CLASS_TEST_H_
#include <xxwsL.h>

class class_exp
{
public:
	class_exp() {};
	~class_exp() {};
	//重载cin输入>>运算符
	friend istream& operator >> (istream &is, class_exp &exp_) {
		cout << "name = ";
		is >> exp_.name;
		cout << "vlaue0 = ";
		is >> exp_.value0;
		cout << "value1 = ";
		is >> exp_.value1;
		return is;
	}
	//重载cout输出>>运算符
	friend ostream& operator << (ostream &os, class_exp &exp_) {
		os << "name = " << exp_.name << ' ' << "value0 = " << exp_.value0 << ' ' << "value1 = " << exp_.value1;
		return os;
	}
	//重载+运算符
	class_exp operator + (class_exp &exp_) const {
		class_exp exp;
		exp.name = name;
		exp.value0 = value0 + exp_.value0;
		exp.value1 = value1 + exp_.value1;
		return exp;
	}
private:
	int name;
	int value0;
	int value1;
};

void class_test_fi(void)
{
	class_exp exp0, exp1;
	cin >> exp0 >> exp1;
	cout << exp0 + exp1;
}
#endif // !_CLASS_TEST_H_
