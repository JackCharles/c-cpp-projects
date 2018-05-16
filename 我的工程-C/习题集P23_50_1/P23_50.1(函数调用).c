#include <stdio.h>
int jc(int); 
float mi(float,int); 
	void main(){ 
	float a,b,shx=0,x; 
	int n,i; 
	printf("«Î ‰»Îx,n:"); 
	scanf("%f %d",&x,&n); 
	for(i=1;i<=n&&(mi(x,(2*i-1))/jc(2*i-1))>1e-8;i++)
		shx=shx+(mi(x,(2*i-1))/jc(2*i-1));
	printf("shx=%f\n",shx); 
} 
int jc(int i){ 
	int a=1,j; 
	for(j=1;j<=i;j++) 
		a=a*j; 
	return a; 
} 
float mi(float a,int b){ 
	float c=1,i; 
	for(i=1;i<=b;i++) 
		c=c*a; 
	return c; 
}