#include <iostream>
using namespace std;

int main()
{
	int n, k;
	int a[1001];
	while (cin >> n >> k)
	{
		int count = 0;
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		int t = 0;
		for (int i = 0; i < n; ++i)
		{
			t += a[i];
			if (t >= k)
			{
				count++;
				t = 0;
			}
		}
		if (t > 0)
			count++;
		cout << count << endl;
	}
	return 0;
}
