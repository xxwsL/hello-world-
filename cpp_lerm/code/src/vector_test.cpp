#include <xxwsL.h>
#include <vector_use.h>



bool fi(int n) {
	return n<4;
}

int main(void)
{
	//v0
	vector<int> v0;		
	for (int i = 2; i <= 12; ++i) {
		cout << i <<"\n";
		v0.push_back(i);
	}
	vector<int>::iterator i0 = v0.end() - 1;		//����һ��������
	cout << "v0 end element = " << *i0 << '\n';		//���������������
	printvector(v0);

	//v1
	vector<int> v1(3, 7);							//����һ����������������Ԫ��ȫ��ֵ7
	printvector(v1);

	//v2
	vector<int>::iterator it0 = v0.begin();
	vector<int> v2(it0+0, it0+3);					//��v1��0��3�����Ԫ�ؿ�����v2
	printvector(v2);

	//v3
	vector<int> v3(v0);								//����һ�������������������Ƶ�v3
	printvector(v3);

	//v4
	vector<int> v4(5);								
	v4[1] = v4.at(3) = 9;							//������Ӧλ�ø�ֵ
	printvector(v4);

	//reserve(ֻ����vector������Ԫ��)
	v2.reserve(6);
	printvector(v2);

	//resize(����vector����ĩβ����0Ԫ��)
	v2.resize(8);
	printvector(v2);

	v2.resize(2);
	printvector(v2);

	//clear
	v2.clear();
	printvector(v2);

	//insert(����Ԫ��)
	v2.insert(v2.end(), v0[1]);
	printvector(v2);

	v2.insert(v2.end(), v0.at(1));
	printvector(v2);

	v2.insert(v2.end(), 2, 1);					//v2ĩβ��������1
	printvector(v2);

	v2.insert(v2.end(), v0.begin() + 2, v0.begin() + 5);
	printvector(v2);

	//erase(ɾ��Ԫ��)
	v2.erase(v2.end() - 2);
	printvector(v2);

	v2.erase(v2.begin() + 1, v2.end() - 2);
	printvector(v2);

	//assign
	v2.assign(3, 6);
	printvector(v2);

	v2.assign(v0.begin() + 1, v0.end());	//��������ʱ�Զ�����
	printvector(v2);

	//rbegin��rend
	vector<int>::reverse_iterator it1 = v2.rbegin();	//����һ��reverse������
	v3.assign(it1, v2.rend());
	printvector(v3);

	//repalce_if
	v4[0] = 3;
	replace_if(v4.begin(), v4.end(), fi, 7);
	printvector(v4);

	//repalce
	v4[0] = 3; v4[2] = v4[4] = 0;
	replace(v4.begin(), v4.end(), 0, 7);
	printvector(v4);

	//sort
	sort(v4.begin() + 2, v4.end());
	printvector(v4);

	while (1);
	return true;
}