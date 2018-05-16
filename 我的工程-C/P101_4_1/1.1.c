#include<stdio.h>
void main(){
	float a,b,c,d;
	b=0;a=0;c=1;d=1;
	do{
		a=b+a;
		b=c/(2*d-1);
		c=-c;
		d++;
	}while(1/(2*d-1)>1e-5);
	printf("¦Ð=%.6f\n",4*a);
}