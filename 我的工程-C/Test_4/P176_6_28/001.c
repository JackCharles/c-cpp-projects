#include<stdio.h>
#define n 100
void main(){
	int k,m,s,i,j;//k是总人数，s是从第s个开始，m是每m个
	int a[n];
	scanf("%d %d %d",&k,&s,&m);
	for(i=1;i<=k;i++)
		a[i]=i;
	for(i=s+m-1;k!=1;i=i+m-1){
		if(i%k==0)
			i=k;//i为要死的那个人
		else i=i%k;
		printf("%d ",a[i]);
		for(j=i;j<n;j++)
			a[j]=a[j+1];
		k--;//覆盖
	}
	printf("\n");
	printf("winner is %d\n",a[1]);
}