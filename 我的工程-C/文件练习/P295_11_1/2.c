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
	printf("E:\\c���Կ���\\�ҵĹ���\\�ļ���ϰ\\P295_11_1\\1.dat�ļ�����%d���ַ���\n",i-1);//���ơ�\0����ռ��һλ
	//�˴�����ļ�·��������һ����\��,һ��б�ܱ�ʾ�ַ�ת�������\\�����ַ�ת����вű�ʾ��\��;
}
