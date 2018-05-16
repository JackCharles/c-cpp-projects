#include<stdio.h>
void copy(char a[],char b[],int n);
void main(){
	char a[]="dhajmsamhdak";
	char b[100];
	int n=sizeof(a)/sizeof(char);//n为字符个数
	copy(a,b,n);
	printf("\n");
}

void copy(char a[],char b[],int n){
	int i,j,k;
	for(i=0;i<n&&a[i]!='m';i++);//找到第一个m对应i的位置
		k=i;
	for(i=i+1,j=0;i<n;i++,j++)
		b[j]=a[i];
	for(i=0;i<n-k;i++)//输出m以后的项数
		printf("%2c",b[i]);
}