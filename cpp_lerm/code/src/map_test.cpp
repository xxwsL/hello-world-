#include <xxwsL.h>

int main(void) {

	map<int, string> mapStudent;

	mapStudent[1] = "student_one";

	mapStudent[2] = "student_two";

	mapStudent[3] = "student_three";

	map<int, string>::iterator iter;

	for (iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
		cout << iter->first << " = " << iter->second << "\n";
	while (1);
	return true;
}