#include<stdio.h>
#define n 2//n为学生数
float sum_sub1=0,sum_sub2=0,sum_sub3=0,sum_sub4=0;

struct StuInfo{
	int No;
	char name[20];
	int sub1,sub2,sub3,sub4,sum;
} Stu[n];

void inputInfo(struct StuInfo Stu[],int i){//////学生信息输入
	printf("请输入第%d个学生的姓名、学号：",i+1);
	scanf("%s%d",Stu[i].name,&Stu[i].No);
	printf("请输入该学生4门课成绩(sub1,sub2,sub3,sub4):");
	scanf("%d%d%d%d",&Stu[i].sub1,&Stu[i].sub2,&Stu[i].sub3,&Stu[i].sub4);
    Stu[i].sum=Stu[i].sub1+Stu[i].sub2+Stu[i].sub3+Stu[i].sub4;

}

void output(struct StuInfo Stu[],int i){////学生信息输出
	printf("***********************************************\n");
	printf("姓名:%s\n",Stu[i].name);
	printf("学号:%d\n",Stu[i].No);
	printf("sub1:%d\n",Stu[i].sub1);
	printf("sub2:%d\n",Stu[i].sub2);
	printf("sub3:%d\n",Stu[i].sub3);
	printf("sub4:%d\n",Stu[i].sub4);
	printf("总成绩:%d\n",Stu[i].sum);
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
	printf("全班sub1的平均成绩是:%f\n",sum_sub1/n);
	printf("全班sub2的平均成绩是:%f\n",sum_sub2/n);
	printf("全班sub3的平均成绩是:%f\n",sum_sub3/n);
	printf("全班sub4的平均成绩是:%f\n",sum_sub4/n);
}
void main(){
	int i;
	for(i=0;i<n;i++){
		inputInfo(Stu,i);
		output(Stu,i);
}
		Holeclass(Stu);
}	
