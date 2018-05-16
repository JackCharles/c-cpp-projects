#include<stdio.h>
void main(){
	char a;
	int i=0;
	printf("请输入英文(以回车结束):");
	a=getchar();
    for(i=0;a!='\n';i++){//判断什么时候结束，并计数
		for( ;a==' '; )//如果空格，循环输入，不是空格跳出
			a=getchar();
		for( ;a!=' '&&a!='\n'; )//跳出后，再输入空格或回车（开始该单词，并结束该单词，返回计数）
			a=getchar();
	}
	printf("你输入的单词有%d个!\n",i);
}




//for语句判断加循环




