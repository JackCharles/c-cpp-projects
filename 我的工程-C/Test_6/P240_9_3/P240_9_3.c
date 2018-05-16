#include <stdio.h>

void swap1(int*xx,int*yy){
	int *temp;
	int k=10;
	temp=&k;
	*temp=*xx;
	*xx=*yy;
	*yy=*temp;
}

void swap2(int*xx,int*yy){
	int *temp;
	temp=xx;
	xx=yy;
	yy=temp;
	printf("%d%d\n",*xx,*yy);
}

void swap3(int xx,int yy){
	int temp;
	temp=xx;
	xx=yy;
	yy=temp;
}

void main(){
	int x,y;
	x=5;y=3;
	printf("原始数据:x=%d,y=%d\n",x,y);
	swap2(&x,&y);
	printf("x=%d,y=%d\n",x,y);
}