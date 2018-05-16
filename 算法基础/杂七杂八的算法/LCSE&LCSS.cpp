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

	/* ���ڶ�̬�����һλ�������ɿ���ʹ��memset������һ��Ҫָ����ʼ������n.
	** ���Ƕ��ڶ�̬����Ķ�ά�����еĳ�Ա�ڶ������������ģ�ʹ��memset�����
	** ��Ŷ���ָ��������ռ䣬�����������ڴ������ƻ���ά����Ľṹ��
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