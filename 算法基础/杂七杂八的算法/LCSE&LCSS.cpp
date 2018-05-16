#include <iostream>
#include <string>

using namespace std;

int LCSE(string a, string b)
{
	int alen = a.length();
	int blen = b.length();
	if (alen == 0 || blen == 0)
		return 0;

	int **c = new int*[alen+1];
	for (int i = 0; i < alen+1; ++i)
	{
		c[i] = new int[blen+1];
		for (int j = 0; j < blen + 1; ++j)
			c[i][j] = 0;
	}

	/* 对于动态分配的一位数组依旧可以使用memset，但是一定要指定初始化长度n.
	** 但是对于动态分配的二维数组中的成员在堆区不是连续的，使用memset会清空
	** 存放二级指针的连续空间，附带清除别的内存区域，破坏二维数组的结构。
	** memset(c, 0, (alen+1)*(blen+1) * sizeof(int));
	*/

	for (int i = 0; i < alen; ++i)
	{
		for (int j = 0; j < blen; ++j)
		{
			if (a[i] == b[j])
				c[i + 1][j + 1] = c[i][j] + 1;
			else
				c[i + 1][j + 1] = c[i+1][j]>c[i][j+1]? c[i + 1][j]: c[i][j + 1];
		}
	}
	int res = c[alen][blen];

	for (int i = 0; i < alen+1; ++i)
		delete[] c[i];
	delete[] c;

	return res;
}


int LCSS(string a, string b)
{
	int alen = a.length();
	int blen = b.length();
	if (alen == 0 || blen == 0)
		return 0;

	int maxlen = 0;
	int **c = new int*[alen + 1];
	for (int i = 0; i < alen + 1; ++i)
	{
		c[i] = new int[blen + 1];
		for (int j = 0; j < blen + 1; ++j)
			c[i][j] = 0;
	}

	for (int i = 0; i < alen; ++i)
	{
		for (int j = 0; j < blen; ++j)
		{
			if (a[i] == b[j])
			{ 
				c[i + 1][j + 1] = c[i][j] + 1;
				maxlen = c[i + 1][j + 1] > maxlen ? c[i + 1][j + 1] : maxlen;
			}
			else
				c[i + 1][j + 1] = 0;
		}
	}

	for (int i = 0; i < alen+1; ++i)
		delete[] c[i];
	delete[] c;

	return maxlen;
}


int main()
{
	string a, b;
	while (getline(cin, a))
	{
		getline(cin, b);
		cout << LCSS(a, b) << endl;
	}

	return 0;
}