#include<iostream>
#include<cstring>
#include<stdio.h>
using namespace std;
int a[100], b[101][100],temp0[100];//temp0把输入的乘数转存到a[50],b[50]中
char c;
int i, j=0, p, q,t=0;	//t小数位数			// pq分别记录两个乘数的位数-1(从0开始)

int s, temp,ci;
int flag=0;
int main()
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

	memset(temp0,-1,sizeof(temp0));
	while(cin>>c)
	{
		if(c=='0')
			flag=1;
		for(i=0; c!=' '; i++)
		{
			j=0;
			if(c=='.')
			{
				t=0;
				j=-1;
			}
			t++;
			temp0[i]=c-'0';
			i+=j;//避开小数点
			c=getchar();
		}
		if(flag)
		{
			for(j=0; j<=i; j++)
				temp0[j]=temp0[j+1];
			temp0[i]=-1;
		}
		cin>>ci;
		for(i=99; temp0[i]==-1&&i>=0; i--);
		p=i;
		for(i,j=0; i>=0; i--,j++) //数字排列顺序颠倒,使得个位在a[0]处
			a[j]=temp0[i];

		for(int k=1; k<ci; k++)
		{
			for(i=99; temp0[i]==-1&&i>=0; i--);
			q=i;
			for(i,j=0; i>=0; i--,j++) //数字排列顺序颠倒,使得个位在b[50][0]处
				b[100][j]=temp0[i];

			// 开始计算
			for (j = 0; j <= q; j++)
			{
				s = 0;
				for (i = 0; i <= p; i++)
				{
					temp = a[i] * b[100][j] + s;
					b[j][j+i] = temp % 10;
					// +i为了错位相加
					s = temp / 10;
				}
				b[j][i + j] = s;
//最后一位只写入个位数字，单独添加十位数字
			}
			s=0;
			for (i=0; i<ci*(p+1); i++) //p+q列，注意p,q都少一个
			{
				for(j=1; j<=p; j++) //q层
				{
					b[0][i]+=b[j][i];
				}
				b[0][i]=b[0][i]+s;
				s=b[0][i]/10;
				b[0][i]=b[0][i]%10;

			}
			for(i=99; b[0][i]==0; i--);
			p=i;//a[i]的位数改变
			for(j=0; j<99; j++)
				a[j]=b[0][j];
			memset(b,0,sizeof(b));
		}

		t=(t-1)*ci;

		for(i=99; a[i]==0&&i>=t; i--);
		for(i; i>=t; i--)
			cout <<a[i];
		cout<<'.';
		for(j=0; a[j]==0; j++);
		for (i=t-1; i>=j; i--)
			cout<<a[i];

		cout<<endl;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));

		memset(temp0,-1,sizeof(temp0));
	}
	return 0;
}
