#include<stdio.h>
void main(){
	int g,s,b,i;
	for(i=100;i<=999;i++){
		g=i%10;
		s=((i-g)/10)%10;
		b=(i-10*s-g)/100;
		if(i==g*g*g+s*s*s+b*b*b)
			printf("%d ÊÇArmstrongÊý!\n",i);
	}
}