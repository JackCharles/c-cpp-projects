#include<stdio.h>
void main(){
	int i,j,k,m;
	for(i=1;i<=10;i++){//��ӡ����
		for(j=1;j<=10-i;j++)//��ӡÿ��ǰ��Ŀո�
			printf("  ");
		for(k=1;k<=i;k++)//��ӡÿ��˳�����ӵ�����
			printf("%2d",k%10);
		for(m=i-1;m>=1;m--)//��ӡ����˳����ٵ�����
			printf("%2d",m);
		printf("\n");//ÿ�л���
	}
}