#include<stdio.h>
#include<stdlib.h>
struct StuInf{
	char name[20];
	int No;
	float ach;
	struct StuInf*next;
};
typedef struct StuInf* pstu;//�Զ�������(�ṹ��ָ������)


pstu CreatList(int n){//nΪѧ����
	pstu p,top=NULL,rear=NULL;
	int i;
	for(i=1;i<=n;i++){
		p=(pstu)malloc(sizeof(struct StuInf));
		printf("�������%d��ѧ����������ѧ�š��ɼ�:\n",i);
		scanf("%s%d%f",p->name,&(p->No),&(p->ach));
		p->next=NULL;
		if(top==NULL){
			top=p;
			rear=p;
		}
		else{
			rear->next=p;
			rear=p;
		}
	}
	//free(p);�˴�����free(p)��Ϊp��rear��ָ��β�ڵ㣬�ͷ�p���ͷ�β�ڵ㣬pҲ����Ҫ�ͷ���Ϊp�����ж�������ռ䣬����������ʱֱ��������û�ж����������ÿռ�
	return top;
}
void inputfile(pstu head){
	FILE*fp;
	pstu p=head;
	if((fp=fopen("ѧ����Ϣ.txt","w+"))!=NULL){
		printf("�ļ������ɹ�!\n��������...\n");
	}
	else{
		printf("�ļ���ʧ��!\n�������!\n");
		exit(0);
	}
	while(p!=NULL){
		fprintf(fp,"%-20s	%-8d	%f\n",p->name,p->No,p->ach);
		p=p->next;
	}
	fclose(fp);
}
void main(){
	pstu head;
	int n;
	printf("������ѧ������:");
	scanf("%d",&n);
	head=CreatList(n);
	printf("�������,���ڿ�ʼд���ļ�!\n");
	inputfile(head);
	printf("�ļ�д��ɹ�,�������!\n");
}