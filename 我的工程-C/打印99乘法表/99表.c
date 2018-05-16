#include<stdio.h>
void main(){
	int i,j;
	for (i=1;i<10;i++){
		printf("%4d",i);
		for(j=1;j<=i;j++)
			printf("%4d",i*j);
		printf("\n");//打印前9行
	}
	printf("%4c",'*');//打印*
	for(i=1;i<10;i++)
		printf("%4d",i);//打印最后一行
	printf("\n");
}