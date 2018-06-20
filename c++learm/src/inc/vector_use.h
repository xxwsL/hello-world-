#ifndef _vector_use_h_ 
#define _vector_use_h_
#include <xxwsL.h>

//ģ���ʹ�ӡ���vector
template<class T>
void printvector(const vector<T>& v)
{
	cout << "vector_szie = " << v.size() << "\nvector_capacity = " << v.capacity() << "\n";
	//����һ��������
	typename vector<T>::const_iterator i = v.begin();
	for (; i != v.end(); i++) {
		cout << *i << ' ';
	}
	cout << "\n\n";
	//cout << *i << "\n";
}

#endif
