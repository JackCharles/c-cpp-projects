#include<stdio.h>
	int a,b,c;
	void p(int x,int y,int*z){
		*z=x+y+*z;
		printf("%d  %d  %d\n",x,y,*z);
	}
	int main(){
		a=5;b=8;c=3;
		p(a,b,&c);
		p(7,a+b+c,&a);
		p(a*b,a/b,&c);
	}