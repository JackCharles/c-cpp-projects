#include<stdio.h>
void main(){
	float a=1,n,v,sum=1;
	for(n=1;n<=63;n++){
		a=a*2;
		sum=sum+a;
	}
	v=sum/(1.4e8);
	printf("�����������ԼΪ:%f ������\n",v);
}