#include<stdio.h>
void main(){
	float x,b,c=1,sum;
	int n,a=1;
	printf("������x,n:");
	scanf("%f%d",&x,&n);
	b=x;
	sum=x;//���˴������ж���һ�ǲ�����while������ֱ�����x������Ϊwhile���ѭ�����ϵ�һ��x
	while(a<=n-1&&b/c>=1e-8){//�˴��ж��õ�a,b,c��������߶�Ҫ����ֵ
			b=b*x*x;
			c=2*a+1;
			sum=sum+b/c;//�˴��ӵڶ��ʼ���ӣ���һ����Ϊsum��Ϊx
			a++;
		}
	printf("arch(x)=%f\n",sum);
}