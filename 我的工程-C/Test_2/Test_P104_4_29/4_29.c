#include<stdio.h>
void main(){
	float a=1,n,v,sum=1;
	for(n=1;n<=63;n++){
		a=a*2;
		sum=sum+a;
	}
	v=sum/(1.4e8);
	printf("所需麦子体积约为:%f 立方米\n",v);
}