#include<stdio.h>

int Ack(int m,int n){
	printf("m=%d  n=%d\n",m,n);
	if(m==0)
		return n+1;
	else if(n==0)
		return Ack(m-1,1);
	else if(m>0&&n>0)
		return Ack(m-1,Ack(m,n-1));
}

void main(){
	int m=3,n=2,k;
	k=Ack(m,n);
	printf("运算结果为:%d\n",k);
}