#include<stdio.h>
void main(){
	float x,a,i;
	for(x=1;x<=20;x++){
		a=1+1/x;
		for(i=1;i<=10;i++){
		a=1+1/a;
		}
		printf("x=%f	F(x)=%f\n",x,a);
	}
	
}