#include<stdio.h>
#define n 2//nΪѧ����
float sum_sub1=0,sum_sub2=0,sum_sub3=0,sum_sub4=0;

struct StuInfo{
	int No;
	char name[20];
	int sub1,sub2,sub3,sub4,sum;
} Stu[n];

void inputInfo(struct StuInfo Stu[],int i){//////ѧ����Ϣ����
	printf("�������%d��ѧ����������ѧ�ţ�",i+1);
	scanf("%s%d",Stu[i].name,&Stu[i].No);
	printf("�������ѧ��4�ſγɼ�(sub1,sub2,sub3,sub4):");
	scanf("%d%d%d%d",&Stu[i].sub1,&Stu[i].sub2,&Stu[i].sub3,&Stu[i].sub4);
    Stu[i].sum=Stu[i].sub1+Stu[i].sub2+Stu[i].sub3+Stu[i].sub4;

}

void output(struct StuInfo Stu[],int i){////ѧ����Ϣ���
	printf("***********************************************\n");
	printf("����:%s\n",Stu[i].name);
	printf("ѧ��:%d\n",Stu[i].No);
	printf("sub1:%d\n",Stu[i].sub1);
	printf("sub2:%d\n",Stu[i].sub2);
	printf("sub3:%d\n",Stu[i].sub3);
	printf("sub4:%d\n",Stu[i].sub4);
	printf("�ܳɼ�:%d\n",Stu[i].sum);
	printf("***********************************************\n\n");
}
void Holeclass(struct StuInfo Stu[]){
	int i=0;
	for(i=0;i<2;i++){
	sum_sub1=sum_sub1+Stu[i].sub1;
	sum_sub2=sum_sub2+Stu[i].sub2;
	sum_sub3=sum_sub3+Stu[i].sub3;
	sum_sub4=sum_sub4+Stu[i].sub4;
	}
	printf("ȫ��sub1��ƽ���ɼ���:%f\n",sum_sub1/n);
	printf("ȫ��sub2��ƽ���ɼ���:%f\n",sum_sub2/n);
	printf("ȫ��sub3��ƽ���ɼ���:%f\n",sum_sub3/n);
	printf("ȫ��sub4��ƽ���ɼ���:%f\n",sum_sub4/n);
}
void main(){
	int i;
	for(i=0;i<n;i++){
		inputInfo(Stu,i);
		output(Stu,i);
}
		Holeclass(Stu);
}	
