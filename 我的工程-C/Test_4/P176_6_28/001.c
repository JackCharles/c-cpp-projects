#include<stdio.h>
#define n 100
void main(){
	int k,m,s,i,j;//k����������s�Ǵӵ�s����ʼ��m��ÿm��
	int a[n];
	scanf("%d %d %d",&k,&s,&m);
	for(i=1;i<=k;i++)
		a[i]=i;
	for(i=s+m-1;k!=1;i=i+m-1){
		if(i%k==0)
			i=k;//iΪҪ�����Ǹ���
		else i=i%k;
		printf("%d ",a[i]);
		for(j=i;j<n;j++)
			a[j]=a[j+1];
		k--;//����
	}
	printf("\n");
	printf("winner is %d\n",a[1]);
}