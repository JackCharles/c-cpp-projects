#include<stdio.h>
void main(){
	char a;
	int i=0,I=0,j=0,J=0,k=0,K=0,x=0,y=0,z=0;
	printf("请输入字符流(按回车结束):");
	a=getchar();
	while(a!='\n'){
		if(a=='(')	i++;
		if(a==')')	I++;
		if(a=='[')	j++;
		if(a==']')	J++;
		if(a=='{')	k++;
		if(a=='}')	K++;
		a=getchar();//利用循环思想输入字符流。
	}
	if(i==I&&i!=0)
		printf("小括号配对!\n");
	if(j==J&&j!=0)
		printf("中括号配对!\n");
	if(k==K&&k!=0)
		printf("大括号配对!\n");
}