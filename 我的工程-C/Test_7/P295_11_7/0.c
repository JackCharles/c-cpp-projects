#include<stdio.h>
#include<stdlib.h>
void main(){
	int a,flag,i,j=0,k=0;
	FILE *fp1,*fp2,*fp3;
	fp1=fopen("f.txt","r");
	fp2=fopen("g1.txt","w");
	fp3=fopen("g2.txt","w");
	printf("正在打开文件...\n");

	(fp1=fopen("f.txt","r"))!=NULL&&(fp2=fopen("g1.txt","w"))!=NULL&&(fp3=fopen("g2.txt","w"))!=NULL?
		printf("文件打开成功!\n操作继续...\n"):(printf("打开文件失败,程序结束!\n"),exit(0));

   fprintf(fp2,"此文件下保存的是素数!\n");
   fprintf(fp3,"此文件下保存的不是素数!\n");

	while(!feof(fp1)){
		flag=1;//假设都是素数
		fscanf(fp1,"%d",&a);
		for(i=2;i<=a/2;i++)
			(a%i==0)?flag=0:0;//不是素数
		(flag==1&&a!=1)?(fprintf(fp2,"%d ",a),j++):(fprintf(fp3,"%d ",a),k++);//1不是素数

		(j==5&&j!=0)?(j=0,fputc('\n',fp2)):0;//如果一行有5个数则换行，并起始不换行
		(k==5&&k!=0)?(k=0,fputc('\n',fp3)):0;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	printf("操作成功!\n");
}


//三元运算符，“判断条件？表达式1：表达式2”，其中如果有多条语句构成表达式则按照for的写法“(语句1，语句2...):(语句1，语句2...)”
//该表达式有返回值，如果条件为真，则返回“表达式1”，条件为假则返回“表达式2”
//单分支机构，条件为假时可用0代替