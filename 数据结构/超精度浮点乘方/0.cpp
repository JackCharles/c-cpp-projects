#include<iostream>
#include<cstring>
#include<stdio.h>
using namespace std;
int a[100], b[101][100],temp0[100];//temp0������ĳ���ת�浽a[50],b[50]��
char c;
int i, j=0, p, q,t=0;	//tС��λ��			// pq�ֱ��¼����������λ��-1(��0��ʼ)

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
			i+=j;//�ܿ�С����
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
		for(i,j=0; i>=0; i--,j++) //��������˳��ߵ�,ʹ�ø�λ��a[0]��
			a[j]=temp0[i];

		for(int k=1; k<ci; k++)
		{
			for(i=99; temp0[i]==-1&&i>=0; i--);
			q=i;
			for(i,j=0; i>=0; i--,j++) //��������˳��ߵ�,ʹ�ø�λ��b[50][0]��
				b[100][j]=temp0[i];

			// ��ʼ����
			for (j = 0; j <= q; j++)
			{
				s = 0;
				for (i = 0; i <= p; i++)
				{
					temp = a[i] * b[100][j] + s;
					b[j][j+i] = temp % 10;
					// +iΪ�˴�λ���
					s = temp / 10;
				}
				b[j][i + j] = s;
//���һλֻд���λ���֣��������ʮλ����
			}
			s=0;
			for (i=0; i<ci*(p+1); i++) //p+q�У�ע��p,q����һ��
			{
				for(j=1; j<=p; j++) //q��
				{
					b[0][i]+=b[j][i];
				}
				b[0][i]=b[0][i]+s;
				s=b[0][i]/10;
				b[0][i]=b[0][i]%10;

			}
			for(i=99; b[0][i]==0; i--);
			p=i;//a[i]��λ���ı�
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
