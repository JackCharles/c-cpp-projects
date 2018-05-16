#include<stdio.h>
#define m 2//m为学科数量
#define n 3//n为学生数
struct onesub_ach{
	char sub_name[20];//学科名称
	int mid_ach;//期中成绩
	int final_ach;//期末成绩
	int usual_ach;//平时成绩
	float sub_ach;//课程成绩
	};
struct stu_ach{
	char name[20];//学生姓名
	int num;//学生学号
	struct onesub_ach sub[m];//学生科目数
	}stu[n];//学生个人成绩单

void ach_input(struct onesub_ach sub[],int i){//输入一科成绩
	printf("请输入第%d学科名称:",i+1);
	scanf("%s",sub[i].sub_name);
	printf("请输入该学科平时成绩，期中成绩，期末成绩:");
	scanf("%d%d%d",&(sub[i].usual_ach),&(sub[i].mid_ach),&(sub[i].final_ach));
	sub[i].sub_ach=0.1*(sub[i].usual_ach)+0.3*(sub[i].mid_ach)+0.6*(sub[i].final_ach);//计算课程成绩
}

void input(struct stu_ach stu[],int i){//一个学生的信息
	int j;//学科序数
	printf("\n请输入第%d个学生的姓名和学号:",i+1);
	scanf("%s%d",stu[i].name,&stu[i].num);
	for(j=0;j<m;j++)
		ach_input((stu[i].sub),j);
}

void output_onestu_achlist(struct stu_ach stu[],int i){//打印第i个学生的成绩
	int j;
	printf("姓名:	%s\n",stu[i].name);
	printf("学号:	%d\n",stu[i].num);
	printf("课程成绩:\n");
	for(j=0;j<m;j++)
		printf("%s:	%f\n",(stu[i].sub[j].sub_name),(stu[i].sub[j].sub_ach));
}

void output_onesub_achlist(struct stu_ach stu[],int j){//打印第j门课程成绩单
	int i;
	printf("课程名称:	%s\n",stu[1].sub[j].sub_name);//找到课程名称
	for(i=0;i<n;i++)
		printf("%s:	%f\n",stu[i].name,stu[i].sub[j].sub_ach);
}

void output_onesub_notpass(struct stu_ach stu[],int j){//打印第j门课程不及格学生成绩单
	int i,flag=1;
	for(i=0;i<n;i++)
		if(stu[i].sub[j].sub_ach<60){
			flag=-1;
			printf("%s:	%f\n",stu[i].name,stu[i].sub[j].sub_ach);
		}
		if(flag==1)
			printf("该课程没有不及格同学!\n");
}


	void main(){
		int i,flag;//i为学生序数
		for(i=0;i<n;i++)
			input(stu,i);
		printf("\n\n请选择你要输出的成绩单:\n1.某个学生的成绩单	2.某课程的成绩单	3.某课程不及格学生及其成绩单\n");
		scanf("%d",&flag);
		if(flag==1){
			printf("请输入你要查看的学生的序号（从1开始,输入0结束）:");
			scanf("%d",&i);
			for( ;i!=0; ){
				if(i<=n&&i>0){
					output_onestu_achlist(stu,i-1);
					printf("如果你想继续查看,请继续输入（从1开始,输入0结束）:");
				}
				else
					printf("你输入的学生序号不存在，请重新输入（从1开始,输入0结束）:");
				scanf("%d",&i);
			}
		}
		else if(flag==2){
			printf("请输入你要查看的科目序号（从1开始,输入0结束）:");
			scanf("%d",&i);
			for( ;i!=0; ){
				if(i<=m&&i>0){
					output_onesub_achlist(stu,i-1);
					printf("如果你想继续查看,请继续输入（从1开始,输入0结束）:");
				}
				else
					printf("你输入的科目序号不存在，请重新输入（从1开始,输入0结束）:");
				scanf("%d",&i);
			}
		}
		else if(flag==3){
			printf("请输入你要查看的科目序号（从1开始,输入0结束）:");
			scanf("%d",&i);
			for( ;i!=0; ){
				if(i<=m&&i>0){
					output_onesub_notpass(stu,i-1);
					printf("如果你想继续查看,请继续输入（从1开始,输入0结束）:");
				}
				else
					printf("你输入的科目序号不存在，请重新输入（从1开始,输入0结束）:");
				scanf("%d",&i);
			}
		}
		else
			printf("输入错误,谢谢使用!\n");
	}//main//