#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	int a[100], b[100][100],temp0[50];//temp0������ĳ���ת�浽a[50],b[50]��
	char c;
	int i, j, p, q;				// pq�ֱ��¼����������λ��-1(��0��ʼ)
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
	for(i,j=0;i>=0;i--,j++)//��������˳��ߵ�,ʹ�ø�λ��a[0]��
		a[j]=temp0[i];

	memset(temp0,-1,sizeof(temp0));
	cin>>c;//ͬ���ķ�ʽ������һ������
	for(i=0;c!='\n';i++){
		temp0[i]=c-'0';//�ַ�ת��Ϊ����
		c=getchar();
	}
	for(i=49;temp0[i]==-1&&i>=0;i--);
	q=i;
	for(i,j=0;i>=0;i--,j++)//��������˳��ߵ�,ʹ�ø�λ��b[50][0]��
		b[50][j]=temp0[i];

	// ��ʼ����
	for (j = 0; j <= q; j++)
	{
		s = 0;
		for (i = 0; i <= p; i++)
		{
			temp = a[i] * b[50][j] + s;
			b[j][j+i] = temp % 10;
			// +iΪ�˴�λ���
			s = temp / 10;
		}
		 b[j][i + j] = s;
//���һλֻд���λ���֣��������ʮλ����
	}
s=0;
for (i=0;i<(p+q+2);i++){//p+q�У�ע��p,q����һ��
	for(j=1;j<=q;j++){//q��
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