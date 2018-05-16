#include<stdio.h>
void main(){
	int i;
	for(i=3;i<100;i++){
		if(i%2!=0)
			printf("%d的平方除以8的余数为%d\n",i,i*i%8);
	}

}