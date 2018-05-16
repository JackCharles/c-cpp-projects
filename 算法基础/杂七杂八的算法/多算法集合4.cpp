#include <iostream>
#include <set>
#include <list>
#include <string>
using namespace std;

int f(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int main()
{
	int n;
	int a[50];
	while (cin >> n)
	{

		qsort(a, n, sizeof(int), f);

		int min = a[0], max = a[n - 1];
		int minIndex = 1, maxIndex = n - 2;
		int res = max - min;
		while (minIndex < maxIndex)
		{
			res += max - a[minIndex];
			res += a[maxIndex] - min;
			min = a[minIndex++];
			max = a[maxIndex--];
		}
		res += ((a[maxIndex] - min) > (a[maxIndex] - min) ? (a[maxIndex] - min) : (a[maxIndex] - min));
		cout << res;
	}
}



//1 -500 -1-500- 1 -1000 -1-1000-1-1000-1 - 1000 -1-500 - 500 