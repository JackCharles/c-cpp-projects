#include<stdio.h>
#include<stdlib.h>
void main(){
	int a;
	FILE *fp1,*fp2;
	fp1=fopen("1.txt","r");
	fp2=fopen("2.txt","w");
	printf("���ڴ��ļ�...\n");
	if((fp1=fopen("1.txt","r"))!=NULL&&(fp2=fopen("2.txt","w"))!=NULL)
		printf("�ļ��򿪳ɹ�!\n��������...\n");
	else{
		printf("���ļ�ʧ��,�������!\n");
		exit(0);
	}
	while(!feof(fp1)){
		fscanf(fp1,"%d",&a);
		if(a>10)
			fprintf(fp2,"%d ",a);
	}
	fclose(fp1);
	fclose(fp2);
	printf("�����ɹ�!\n");

}