#pragma once
#ifndef _MAP_TEST_H_
#define _MAP_TEST_H_
#include <string>
#include <iostream>
#include <map>

using namespace std;

void map_test_fi(void) {
	map<int, string> mapStudent;

	mapStudent[1] = "student_one";

	mapStudent[2] = "student_two";

	mapStudent[3] = "student_three";

	map<int, string>::iterator iter;

	for (iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
		cout << iter->first << " = " << iter->second << "\n";
}
#endif