#include<stdio.h>
#include<stdlib.h>
void main(){
	int a,flag,i,j=0,k=0;
	FILE *fp1,*fp2,*fp3;
	fp1=fopen("f.txt","r");
	fp2=fopen("g1.txt","w");
	fp3=fopen("g2.txt","w");
	printf("���ڴ��ļ�...\n");

	(fp1=fopen("f.txt","r"))!=NULL&&(fp2=fopen("g1.txt","w"))!=NULL&&(fp3=fopen("g2.txt","w"))!=NULL?
		printf("�ļ��򿪳ɹ�!\n��������...\n"):(printf("���ļ�ʧ��,�������!\n"),exit(0));

   fprintf(fp2,"���ļ��±����������!\n");
   fprintf(fp3,"���ļ��±���Ĳ�������!\n");

	while(!feof(fp1)){
		flag=1;//���趼������
		fscanf(fp1,"%d",&a);
		for(i=2;i<=a/2;i++)
			(a%i==0)?flag=0:0;//��������
		(flag==1&&a!=1)?(fprintf(fp2,"%d ",a),j++):(fprintf(fp3,"%d ",a),k++);//1��������

		(j==5&&j!=0)?(j=0,fputc('\n',fp2)):0;//���һ����5�������У�����ʼ������
		(k==5&&k!=0)?(k=0,fputc('\n',fp3)):0;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	printf("�����ɹ�!\n");
}


//��Ԫ����������ж����������ʽ1�����ʽ2������������ж�����乹�ɱ��ʽ����for��д����(���1�����2...):(���1�����2...)��
//�ñ��ʽ�з���ֵ���������Ϊ�棬�򷵻ء����ʽ1��������Ϊ���򷵻ء����ʽ2��
//����֧����������Ϊ��ʱ����0����