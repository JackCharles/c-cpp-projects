#include<stdio.h>
void main(){
	FILE *fp;
	int i=0;
	fp=fopen("1.dat","r");
	while(!feof(fp)){
		fgetc(fp);
		i++;
	}
	fclose(fp);
	printf("E:\\c语言开发\\我的工程\\文件练习\\P295_11_1\\1.dat文件中有%d个字符。\n",i-1);//不计‘\0’所占的一位
	//此处输出文件路径不能用一个‘\’,一个斜杠表示字符转义符，‘\\’再字符转义符中才表示‘\’;
}
