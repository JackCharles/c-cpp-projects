#include<stdio.h>
void main(){
	int i,j,k,m;
	for(i=1;i<=10;i++){//打印九行
		for(j=1;j<=10-i;j++)//打印每行前面的空格
			printf("  ");
		for(k=1;k<=i;k++)//打印每行顺序增加的数字
			printf("%2d",k%10);
		for(m=i-1;m>=1;m--)//打印接着顺序减少的数字
			printf("%2d",m);
		printf("\n");//每行换行
	}
}