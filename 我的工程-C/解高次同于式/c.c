#include<stdio.h>
#include<stdlib.h>
long power(int xi, int x, int ci);
int main()
{
	int a[30];					// 系数
	int n;						// 次数
	int m, b, x;
	int i;
	long sum;					// n次多项式返回值
	printf("请输入同余式次数(不超过30):");
	scanf("%d", &n);
	printf("请输入%d个系数(从高次倒低次):", n+1);
	for (i = n; i >= 0; i--)
		scanf("%d", &a[i]);
	printf("请输入同余数b和模数m:");
	scanf("%d%d", &b, &m);
	printf("\n其解为:\n");
	for (x = 0; x < m; x++)
	{
		sum = 0;
		for (i = n; i >= 0; i--)
			sum += power(a[i], x, i);
		if ((sum - b) % m == 0)
			printf("x ≡ %d (mod%d)\n", x, m);
	}
	return 0;
}

long power(int xi, int x, int ci)
{
	long sum = 1;
	int i;
	for (i = 0; i < ci; i++)
		sum *= x;
	sum *= xi;
	return sum;
}
