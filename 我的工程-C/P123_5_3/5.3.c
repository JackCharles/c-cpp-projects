#include<stdio.h>
long long jc(long);//��������ԭ��
void main(){
	int m,n;
	double a;
	printf("��������������m,n(m>=n):");
	scanf("%d%d",&m,&n);
	if(m>=0&&n>=0&&m>=n){
		a=jc(m)/(jc(m-n)*jc(n));//ע��˴�Ҫ������������ǿ��ת��
		printf("�����:%lf\n",a);
	}
	else
		printf("�������!\n");	     
}
long long jc(long x){//����׳˺���
	long a=1,i;
	if(x!=0){
		for(i=1;i<=x;i++)
			a=a*i;
	}
	else 
		a=1;
	return a;
}

/*ע����c�����У�һ���������������������������б���һ�£�
���������ʹ�����Ͳ�һ�����ڱ��롢���ӻ��ڲ���������޷����У�
���綨��int a(����)�����������%f(������)�������л����*/
