#include<stdio.h>
void main(){
	float pi=1,a=2,b=1,c=2,d=3,n=1;
	do{
		pi=pi*(a/b)*(c/d);
		a+=2;
		b+=2;
		c+=2;
		d+=2;
		n++;
	}while((2*n/(2*n-1)-(2*n-2)/(2*n-1))>1e-5);
	printf("pi=%f\n",pi*2);
}