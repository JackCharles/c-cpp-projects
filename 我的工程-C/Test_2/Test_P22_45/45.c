#include<stdio.h>
void main(){
	char a;
	int i=0,I=0,j=0,J=0,k=0,K=0,x=0,y=0,z=0;
	printf("�������ַ���(���س�����):");
	a=getchar();
	while(a!='\n'){
		if(a=='(')	i++;
		if(a==')')	I++;
		if(a=='[')	j++;
		if(a==']')	J++;
		if(a=='{')	k++;
		if(a=='}')	K++;
		a=getchar();//����ѭ��˼�������ַ�����
	}
	if(i==I&&i!=0)
		printf("С�������!\n");
	if(j==J&&j!=0)
		printf("���������!\n");
	if(k==K&&k!=0)
		printf("���������!\n");
}