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
	printf("该文本共有%d行!\n",i);
}


//1.在记事本中一行字数有无限个，必须要有回车才可进入下一行，所以统计回车数即可
//2.把每一行全部数据读取出来，在读取中遇到空格该行结束，设每行最大2048个字符，可以用fgets
