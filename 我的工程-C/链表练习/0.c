#include<stdio.h>
#include<stdlib.h>
struct StuInf{
	char name[20];
	int No;
	float ach;
	struct StuInf*next;
};
typedef struct StuInf* pstu;//自定义类型(结构体指针类型)


pstu CreatList(int n){//n为学生数
	pstu p,top=NULL,rear=NULL;
	int i;
	for(i=1;i<=n;i++){
		p=(pstu)malloc(sizeof(struct StuInf));
		printf("请输入第%d个学生的姓名、学号、成绩:\n",i);
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
	//free(p);此处不能free(p)因为p和rear都指向尾节点，释放p即释放尾节点，p也不需要释放因为p是先判断在申请空间，条件不符合时直接跳出，没有额外申请无用空间
	return top;
}
void inputfile(pstu head){
	FILE*fp;
	pstu p=head;
	if((fp=fopen("学生信息.txt","w+"))!=NULL){
		printf("文件创建成功!\n操作继续...\n");
	}
	else{
		printf("文件打开失败!\n程序结束!\n");
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
	printf("请输入学生人数:");
	scanf("%d",&n);
	head=CreatList(n);
	printf("输入结束,现在开始写入文件!\n");
	inputfile(head);
	printf("文件写入成功,程序结束!\n");
}