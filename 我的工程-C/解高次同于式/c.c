#include<stdio.h>
#include<stdlib.h>
long power(int xi, int x, int ci);
int main()
{
	int a[30];					// ϵ��
	int n;						// ����
	int m, b, x;
	int i;
	long sum;					// n�ζ���ʽ����ֵ
	printf("������ͬ��ʽ����(������30):");
	scanf("%d", &n);
	printf("������%d��ϵ��(�Ӹߴε��ʹ�):", n+1);
	for (i = n; i >= 0; i--)
		scanf("%d", &a[i]);
	printf("������ͬ����b��ģ��m:");
	scanf("%d%d", &b, &m);
	printf("\n���Ϊ:\n");
	for (x = 0; x < m; x++)
	{
		sum = 0;
		for (i = n; i >= 0; i--)
			sum += power(a[i], x, i);
		if ((sum - b) % m == 0)
			printf("x �� %d (mod%d)\n", x, m);
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
