#include <iostream>
#include <cmath>

using namespace std;

//1 < M < N < 1000000
int GetPrimer(int m, int n)
{
	if (m < 2 || m >= n || n>999999)
		return 0;

	int count = 0;
	bool flag;
	for (int i = m; i <= n; i++)
	{
		flag = true;
		int t = static_cast<int>(sqrt(i));
		for (int j = 2; j <= t; j++)
			if (i%j == 0)
			{
				flag = false;
				break;
			}
		if (flag)
			count++;
	}
	return count;
}


int main()
{
	int m, n;
	while (cin >> m)
	{
		cin >> n;
		cout << GetPrimer(m, n) << endl;
	}

	return 0;
}