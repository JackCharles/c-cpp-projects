#include<stdio.h>
void main(){
	FILE *fp;
	char ch;
	int i=1;
	fp=fopen("1.txt","r");
	while (!feof(fp)){ 
		ch=fgetc(fp);
		if(ch=='\n')
			  i++;
	} 
	fclose(fp);
	printf("���ı�����%d��!\n",i);
}


//1.�ڼ��±���һ�����������޸�������Ҫ�лس��ſɽ�����һ�У�����ͳ�ƻس�������
//2.��ÿһ��ȫ�����ݶ�ȡ�������ڶ�ȡ�������ո���н�������ÿ�����2048���ַ���������fgets
