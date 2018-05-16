#include <iostream>
using namespace std;

int main()
{
	int m, n, p, q;
	int pos[1001], sno[1001];
	while (cin >> n >> m)
	{
		for (int i = 1; i <= n; ++i)
			sno[i] = pos[i] = i;
		for (int i = 0; i < m; ++i)
		{
			cin >> p >> q;
			if (q > 0)
				for (int j = sno[p]; j < sno[p] + q; ++j)
				{
					int t = pos[j + 1];
					pos[j + 1] = pos[j];
					pos[j] = t;
					sno[t]--;
				}
			else//q < 0
				for (int j = sno[p]; j > sno[p] + q; --j)
				{
					int t = pos[j - 1];
					pos[j - 1] = pos[j];
					pos[j] = t;
					sno[t]++;
				}
			sno[p] += q;
		}
		for (int i = 1; i <= n; ++i)
			cout << pos[i] << " ";
	}
	return 0;
}