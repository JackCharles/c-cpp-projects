#include <stdio.h>
int feibo(int n){
	if(n==1||n==2)
		return 1;
	else
		return feibo(n-1)+(n-2);
}

void main(){
	int n;
	printf("������n:");
	scanf("%d",&n);
	printf("��%d��Ϊ:%d\n",n,feibo(n));
}