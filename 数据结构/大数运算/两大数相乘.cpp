#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	int a[100], b[100][100],temp0[50];//temp0把输入的乘数转存到a[50],b[50]中
	char c;
	int i, j, p, q;				// pq分别记录两个乘数的位数-1(从0开始)
	int s, temp;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
    memset(temp0,-1,sizeof(temp0));
	cin>>c;
	for(i=0;c!='\n';i++){
		temp0[i]=c-'0';
		c=getchar();	
	}
	for(i=49;temp0[i]==-1&&i>=0;i--);
	p=i;
	for(i,j=0;i>=0;i--,j++)//数字排列顺序颠倒,使得个位在a[0]处
		a[j]=temp0[i];

	memset(temp0,-1,sizeof(temp0));
	cin>>c;//同样的方式处理另一个乘数
	for(i=0;c!='\n';i++){
		temp0[i]=c-'0';//字符转化为数字
		c=getchar();
	}
	for(i=49;temp0[i]==-1&&i>=0;i--);
	q=i;
	for(i,j=0;i>=0;i--,j++)//数字排列顺序颠倒,使得个位在b[50][0]处
		b[50][j]=temp0[i];

	// 开始计算
	for (j = 0; j <= q; j++)
	{
		s = 0;
		for (i = 0; i <= p; i++)
		{
			temp = a[i] * b[50][j] + s;
			b[j][j+i] = temp % 10;
			// +i为了错位相加
			s = temp / 10;
		}
		 b[j][i + j] = s;
//最后一位只写入个位数字，单独添加十位数字
	}
s=0;
for (i=0;i<(p+q+2);i++){//p+q列，注意p,q都少一个
	for(j=1;j<=q;j++){//q层
		b[0][i]+=b[j][i];
		}
	b[0][i]=b[0][i]+s;
	s=b[0][i]/10;
	b[0][i]=b[0][i]%10;
	
	}
	

for (i=49;b[0][i]==0&&i>-1;i--);
for (i;i>=0;i--)
cout<<b[0][i];
cout<<endl;
	return 0;
}