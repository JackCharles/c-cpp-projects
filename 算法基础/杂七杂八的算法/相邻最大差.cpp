#include <algorithm>
#include <iostream>

using namespace std;

// typedef int (__cdecl* _CoreCrtNonSecureSearchSortCompareFunction)(void const*, void const*);
int c(void const*a, void const*b)
{
	return *((int*)a) - *((int*)b);
}

int main()
{
	int n,t;
	int *a;
	while (cin >> n)
	{
		a = new int[n];
		for (int i = 0; i < n; i++)
		{
			cin >> t;
			a[i] = t;
		}

		qsort(a, n, sizeof(int),c);
		int max = 0;
		for (int i = 0; i < n-1; i++)
		{
			int r = a[i] - a[i + 1] > 0 ? (a[i] - a[i + 1]) : (a[i + 1] - a[i]);
			max = r > max ? r : max;
		}
		cout << max;
		delete[] a;
	}
	return 0;
}