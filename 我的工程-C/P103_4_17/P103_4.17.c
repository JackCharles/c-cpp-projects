#include<stdio.h>
void main(){
	int i;
	for(i=3;i<100;i++){
		if(i%2!=0)
			printf("%d��ƽ������8������Ϊ%d\n",i,i*i%8);
	}

}