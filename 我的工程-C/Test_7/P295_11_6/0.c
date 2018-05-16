#include<stdio.h>
#include<stdlib.h>
void main(){
	int a;
	FILE *fp1,*fp2;
	fp1=fopen("1.txt","r");
	fp2=fopen("2.txt","w");
	printf("正在打开文件...\n");
	if((fp1=fopen("1.txt","r"))!=NULL&&(fp2=fopen("2.txt","w"))!=NULL)
		printf("文件打开成功!\n操作继续...\n");
	else{
		printf("打开文件失败,程序结束!\n");
		exit(0);
	}
	while(!feof(fp1)){
		fscanf(fp1,"%d",&a);
		if(a>10)
			fprintf(fp2,"%d ",a);
	}
	fclose(fp1);
	fclose(fp2);
	printf("操作成功!\n");

}