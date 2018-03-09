/*
*   矩阵连乘积A1A2A3A4A5A6最优计算次序
*   A1: 30 x 35
*   A2: 35 x 15
*   A3: 15 x 5
*   A4: 5  x 10
*   A5: 10 x 20
*   A6: 20 x 25
*
*   最优计算次序：((A1(A2A3))((A4A5)A6))
*   程序输出
*   Multiply A2,2 and A3,3
*   Multiply A1,1 and A2,3
*   Multiply A4,4 and A5,5
*   Multiply A4,5 and A6,6
*   Multiply A1,3 and A4,6
*/
#include <iostream>
using namespace std;

/*
*  计算最优值
*  输出：最优值数组m，记录最优断开位置的数组s
*/
void matrixChain(int *p, int n, int m[][7], int s[][7])
{
	for (int i = 1; i <= n; i++)
	{
		m[i][i] = 0;
	}
	for (int r = 2; r <= n; r++)
	{
		for (int i = 1; i <= n - r + 1; i++)
		{
			int j = i + r - 1;
			m[i][j] = m[i][i] + m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (int k = i + 1; k < j; k++)
			{
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}

/* 构造最优解 */
void traceback(int i, int j, int s[][7])
{
	if (i == j)
	{
		return;
	}
	traceback(i, s[i][j], s);
	traceback(s[i][j] + 1, j, s);
	cout << "Multiply A" << i << "," << s[i][j];
	cout << " and A" << (s[i][j] + 1) << "," << j << endl;
}

int main()
{
	int p[7] = { 30, 35, 15, 5, 10, 20, 25 };
	int m[7][7] = { 0 };
	int s[7][7] = { 0 };
	matrixChain(p, 6, m, s);
	traceback(1, 6, s);
	getchar();
	return 0;
}