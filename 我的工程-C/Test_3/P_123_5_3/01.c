#include<stdio.h>
float jc(float);
void main(){
	float x,m,n;
	printf("������m,n(m>=n):");
	scanf("%f%f",&m,&n);
	if(m>n){
		x=jc(m)/(jc(m-n)*jc(n));
		printf("%f\n",x);
	}
	else if(m==n)
		printf("1\n");
	else if(m<n)
		printf("�������!\n");
}
float jc(float a){
	float i,b=1;
	for(i=1;i<=a;i++)
		b=b*i;
	return b;
}