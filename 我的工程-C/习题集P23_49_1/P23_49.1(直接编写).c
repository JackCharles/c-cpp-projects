#include<stdio.h>
void main (){
	float c,d=1,x,sum=0;
	int a=1,n,flag=1;
	printf ("������x,n:");
	scanf("%f%d",&x,&n);
	if(n==1)
		sum=x;
	else{
		c=x;
		sum=x;
		while ((a<=n-1)&&(c/d>1e-8)){	
			c=c*x*x;//��
			d=d*(2*a)*(2*a+1);//�׳�		
			sum=sum-flag*(c/d);
			flag=-flag;
			a++;
			}
	}
	printf("sinx=%f\n",sum);
}