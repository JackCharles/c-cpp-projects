#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stu
{
	char name[15];
	int NO;
	float ach[6];
	float sum;//总成绩
	float ave;//平均成绩
	char Fname[20];//传递文件名,仅第二项使用
	struct stu* next;
};
void input(int n1, int n2, char sub[][10]);
struct stu* ReadFile(int n2);
void output(int n2, char sub[][10], struct stu*head);
void paixu_NO(struct stu *p, int n2, char sub[][10]);
struct stu* paixu_Name(struct stu *head, int n2, char sub[][10]);
void search1(struct stu*head, int n2, char sub[][10]);
void search2(struct stu*head, int n2, char sub[][10]);
void EverySub(struct stu*head, int n2, char sub[][10]);
void EveryStu(struct stu*head, int n2);
struct stu* EveryStu1(struct stu*head, int n2, char sub[][10]);
void EveryStu2(struct stu*head, int n2, char sub[][10]);
void TongJi(struct stu*head, int n2, char sub[][10]);
struct stu*Add(struct stu*head, int n2, char sub[][10]);
int main()
{
	struct stu* head = NULL;
	int n1, n2, n3, i; //学生数,科目数,功能代号
	char sub[6][10];//学科名称
	printf("****************欢迎使用学生成绩管理系统************\n");
	printf("请输入学生数:");
	scanf("%d", &n1);
	printf("请输入科目数(不超过6科):");
	scanf("%d", &n2);
	while(n2 > 6)
	{
		printf("你输入的科目数超过6科,请重新输入:");
		scanf("%d", &n2);
	}//科目数纠错
	printf("请输入这%d科的科目名称(限10个字符):", n2);
	for(i = 0; i < n2; i++)
		scanf("%s", sub[i]);

	printf("┏┉┉┉┉┉┉┉┉┉┉┉请选择你要进行的操作(0-13)┉┉┉┉┉┉┉┉┉┉┓\n");
	printf("┋  01.Read from a file                                               ┋\n");
    printf("┋  02.Append record manually                                         ┋\n");
	printf("┋  03.Calculate total and average score of every course              ┋\n");
	printf("┋  04.Calculate total and average score of every student             ┋\n");
    printf("┋  05.Sort in descending order by total score of every student       ┋\n");
	printf("┋  06.Sort in ascending order by total score of every stuednet       ┋\n");
    printf("┋  07.Sort in ascending order by number                              ┋\n");
	printf("┋  08.Sort in dictionary order by name                               ┋\n");
    printf("┋  09.Search by number                                               ┋\n");
    printf("┋  10.Search by name                                                 ┋\n");
	printf("┋  11.Statistic analysis for every course                            ┋\n");
    printf("┋  12.List record                                                    ┋\n");
    printf("┋  13.Write to a file                                                ┋\n");
    printf("┋  00.Exit                                                           ┋\n");
	printf("┗┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┛\n");

	scanf("%d", &n3);
	system("cls");
	while(n3 != 0)
	{
		switch(n3)
		{
			case 1:
				head = ReadFile(n2);
				break;
			case 2:
				head = Add(head, n2, sub);
				break;
			case 3:
				EverySub(head, n2, sub);
				break;
			case 4:
				EveryStu(head, n2);
				break;
			case 5:
				head = EveryStu1(head, n2, sub);
				break;
			case 6:
				EveryStu2(head, n2, sub);
				break;
			case 7:
				paixu_NO(head, n2, sub);
				break;
			case 8:
				head = paixu_Name(head, n2, sub);
				break;
			case 9:
				search1(head, n2, sub);
				break;
			case 10:
				search2(head, n2, sub);
				break;
			case 11:
				TongJi(head, n2, sub);
				break;
			case 12:
				output(n2, sub, head);
				break;
			case 13:
				input(n1, n2, sub);
				break;
			default:
				printf("你选择的功能不存在,请重新选择!\n");
		}//switch
	printf("┏┉┉┉┉┉┉┉┉┉┉┉请选择你要进行的操作(0-13)┉┉┉┉┉┉┉┉┉┉┓\n");
	printf("┋  01.Read from a file                                               ┋\n");
    printf("┋  02.Append record manually                                         ┋\n");
	printf("┋  03.Calculate total and average score of every course              ┋\n");
	printf("┋  04.Calculate total and average score of every student             ┋\n");
    printf("┋  05.Sort in descending order by total score of every student       ┋\n");
	printf("┋  06.Sort in ascending order by total score of every stuednet       ┋\n");
    printf("┋  07.Sort in ascending order by number                              ┋\n");
	printf("┋  08.Sort in dictionary order by name                               ┋\n");
    printf("┋  09.Search by number                                               ┋\n");
    printf("┋  10.Search by name                                                 ┋\n");
	printf("┋  11.Statistic analysis for every course                            ┋\n");
    printf("┋  12.List record                                                    ┋\n");
    printf("┋  13.Write to a file                                                ┋\n");
    printf("┋  00.Exit                                                           ┋\n");
	printf("┗┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┛\n");
	scanf("%d", &n3);
	system("cls");
	}//while
	printf("感谢你的使用,再见!\n");
	return 0;
}//main
//1.从文件读取数据
struct stu* ReadFile(int n2)
{
	struct stu* head = NULL, *rear = NULL, *p = NULL;
	FILE*fp;
	char fname[20], str[100]; //str[100]用于读掉文件表头
	int i = 0, j;
	printf("你选择了从文件读取学生数据!\n");
	printf("请输入要读取的文件名(请确保读取的文件中有学生信息):");
	scanf("%s", fname);
	if((fp = fopen(fname, "r")) == NULL)
		printf("文件读取失败,请重新选择并输入正确的文件名称,或者选择13创建该文件!\n");
	else
	{
		fgets(str, sizeof(str), fp); //跳过第一行
		do///此处不用feof是因为feof要越过结束标志EOF才返回非0值,刚好遇见EOF则返回0,程序继续循环导致多读取一次无用信息
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			fscanf(fp, "%d%s", &p->NO, p->name);
			for(j = 0; j < n2; j++)
			{
				fscanf(fp, "%f", &p->ach[j]); //一个同学的n2科成绩
			}
			if(head == NULL)
			{
				head = p;
				rear = p;
			}
			else
			{
				rear->next = p;
				rear = p;
			}
			i++;
			fgetc(fp);//跳过\t
			fgetc(fp);//跳过\n
			str[99] = fgetc(fp); //读取下一行首个字符，str[99]是取的前面没有实际作用的一个变量
			fseek(fp, -1, 1); ///此处将文件指针向后移一位,因为str[99]让文件指针指到该行首字符之后，若文件没有结尾,
		}
		while(str[99] != '*' && str[99] != EOF); ///则该行学生信息读取会错乱；!='*'是因为11功能统计信息可能会输入到此文件，
		fclose(fp); ///统计信息第一个字符是'*',排除统计信息对学生信息读取的干扰
		strcpy(head->Fname, fname); ///此处文件名需带回，故放在结构体中带回
		rear->next = NULL;
		if(head == NULL || rear == NULL)
			printf("文件录入失败,请重试!");
		printf("你共录入%d个学生的(%d科)成绩!\n", i, n2);
	}
	return head;
}
//2.增量式手动输入（增加到链头）
struct stu*Add(struct stu*head, int n2, char sub[][10])
{
	int i, j, n, flag1, flag2; //n为增加的人数
	char Fname[20];
	struct stu*p = head, *r = NULL, *head0 = head;
	FILE*fp;
	if(head == NULL)
		printf("当前链表为空,请先选择1从文件读取或选择13创建文件后再增量输入!\n\n");
	else
	{
		printf("请输入要增加的人数:");
		scanf("%d", &n);
		for(i = 0; i < n; i++)
		{
			flag1 = 0;
			flag2 = 0;
			p = (struct stu*)malloc(sizeof(struct stu));
			printf("请输入增加的第%d个学生的学号(限两位数)和姓名(限15字符):", i + 1);
			scanf("%d%s", &(p->NO), p->name);
			r = head;
			while(r != NULL) //检测有无重复姓名
			{
				if(strcmp(p->name, r->name) == 0)
					flag1 = 1;
				r = r->next;
			}
			r = head;
			while(r != NULL) //检测学号有无重复
			{
				if(p->NO == r->NO)
					flag2 = 1;
				r = r->next;
			}
			if(flag1)
			{
				if(flag2)
				{
					printf("你输入的学号和姓名都有重复,请检查数据后重新输入学号(以便从学号区分):");
					scanf("%d", &(p->NO));
				}
				printf("此姓名有重复,但对应的学号不重复(可从学号区分),请继续...\n");
			}
			else if(flag2)
			{
				printf("你输入的学号重复,请核对信息后重新输入学号:");
				scanf("%d", &(p->NO));
			}
			printf("请输入%s学生的成绩:\n", p->name);
			for(j = 0; j < n2; j++)
			{
				printf("%-10s:", sub[j]);
				scanf("%f", &p->ach[j]);
			}
			p->next = head;
			head = p; ///向链头添加
		}//for
		printf("%d个学生信息添加成功,现在保存到文件\n", n);
		if((fp = fopen(head0->Fname, "w")) == NULL)
			printf("保存到文件失败,请重试!\n");
		else
		{
			fprintf(fp, "Number  Name           ");
			for(j = 0; j < n2; j++)
				fprintf(fp, "%-9s\t", sub[j]);
			fprintf(fp, "\n");
			for(p = head; p != NULL; p = p->next)
			{
				fprintf(fp, "%-2d\t%-15s", p->NO, p->name);
				for(j = 0; j < n2; j++)
					fprintf(fp, "%f\t", p->ach[j]);
				fprintf(fp, "\n");
			}
			fclose(fp);
			printf("保存到文件成功!\n");
		}
	}//if(head==NULL)
	return head;
}
//3.计算每门课程的总分和平均分
void EverySub(struct stu*head, int n2, char sub[][10])
{
	struct stu*p = head;
	float sum[6], ave[6]; //声明科目总和平均变量
	int i = 0, j;
	memset(sum, 0, sizeof(sum)); //初始化为0
	if(head == NULL)
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
	else
	{
		printf("你选择了计算每门课程总分和平均分的功能!\n");
		while(p != NULL)
		{
			for(j = 0; j < n2; j++)
				sum[j] += p->ach[j];
			p = p->next;
			i++;//统计学生数，开始输入的学生数在后续操作中可能会有变动，不用n2
		}//计算每门课程总分
		for(j = 0; j < n2; j++)
			ave[j] = sum[j] / i; //计算每门课程平均分
		for(j = 0; j < n2; j++) //输出
			printf("%-10s:\tSUM:%f\tAverage:%f\n", sub[j], sum[j], ave[j]);
		printf("共%d科考试成绩,请核对!\n", n2);
	}
}
//4.计算每个学生的总分和平均分
void EveryStu(struct stu*head, int n2)
{
	struct stu*p = head;
	int i = 0, j;
	if(head == NULL)
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
	else
	{
		printf("你选择了计算每个学生的总分和平均分的功能!\n");
		while(p != NULL) //计算每个学生的总分和平均数
		{
			p->sum = 0;
			for(j = 0; j <= n2 - 1; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
			i++;
		}
		for(p = head; p != NULL; p = p->next)
			printf("%-2d\t%-15s:SUM:%f\tAverage:%f\n", p->NO, p->name, p->sum, p->ave);
		printf("共%d个学生,请核对!\n", i);
	}
}
//5.按每个学生的总分由高到低排出名次表
struct stu* EveryStu1(struct stu*head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1;
	struct stu*p = NULL, *r = NULL, *p2 = NULL, *head2 = head, *rear2 = NULL;
	if(head != NULL) //纠错
	{
		printf("你选择了按每个学生的总分由高到低排出名次表!\n");
		/*while(head!=NULL) ///复制链表，子函数单独操作,避开对全局影响,保障程序健壮性
		{
		    p=(struct stu*)malloc(sizeof(struct stu));
		    p->NO=head->NO;
		    strcpy(p->name,head->name);
		    for(j=0; j<n2; j++) ///传入成绩
		        p->ach[j]=head->ach[j];
		    if(head2==NULL)
		        head2=rear2=p;
		    else
		    {
		        rear2->next=p;
		        rear2=p;
		    }
		    head=head->next;
		}
		rear2->next=NULL;///复制链表*/
		p = head2;

		while(p != NULL)
		{
			p->sum = 0; //计算每个学生的总分和平均数
			for(j = 0; j < n2; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //冒泡法排序，总成绩从大到小
		{
			flag = 0;
			p = head2;
			r = p->next;
			p2 = r->next;
			if(head2->sum < r->sum)
			{
				head2->next = r->next;
				r->next = head2;
				head2 = r;
				flag = 1;
			}
			else
				while(p2 != NULL)
				{
					if(r->sum < p2->sum)
					{
						r->next = p2->next;
						p2->next = r;
						p->next = p2;
						flag = 1;
					}
					p = p->next;
					r = p->next;
					p2 = r->next;
				}
		}
		printf("Number  Name           ");
		for(j = 0; j < n2; j++)
			printf("%-9s\t", sub[j]);
		printf("SUM      \tAverage");
		printf("\n");
		for(p = head2; p != NULL; p = p->next)
		{
			printf("%-2d\t%-15s", p->NO, p->name);
			for(j = 0; j < n2; j++)
				printf("%f\t", p->ach[j]);
			printf("%f\t%f\n", p->sum, p->ave);
			i++;//统计人数
		}
		printf("共%d个学生,请核对!\n", i);
	}
	else
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
	return head2;
}
//6.按每个学生的总分由低到高排出名次表
void EveryStu2(struct stu*head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1;
	struct stu*p = NULL, *r = NULL, *p2 = NULL, *head2 = NULL, *rear2 = NULL;
	if(head != NULL) //纠错
	{
		printf("你选择了按每个学生的总分由低到高排出名次表!\n");
		while(head != NULL) ///复制链表，子函数单独操作,避开对全局影响,保障程序健壮性
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			p->NO = head->NO;
			strcpy(p->name, head->name);
			for(j = 0; j < n2; j++) ///传入成绩
				p->ach[j] = head->ach[j];
			if(head2 == NULL)
				head2 = rear2 = p;
			else
			{
				rear2->next = p;
				rear2 = p;
			}
			head = head->next;
		}
		rear2->next = NULL; ///复制链表
		p = head2;
		while(p != NULL)
		{
			p->sum = 0; //计算每个学生的总分和平均数
			for(j = 0; j < n2; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //冒泡法排序，总成绩从小到大
		{
			flag = 0;
			p = head2;
			r = p->next;
			p2 = r->next;
			if(head2->sum > r->sum)
			{
				head2->next = r->next;
				r->next = head2;
				head2 = r;
				flag = 1;
			}
			else
				while(p2 != NULL)
				{
					if(r->sum > p2->sum)
					{
						r->next = p2->next;
						p2->next = r;
						p->next = p2;
						flag = 1;
					}
					p = p->next;
					r = p->next;
					p2 = r->next;
				}
		}
		printf("Number  Name           ");
		for(j = 0; j < n2; j++)
			printf("%-9s\t", sub[j]);
		printf("SUM      \tAverage");
		printf("\n");
		for(p = head2; p != NULL; p = p->next)
		{
			printf("%-2d\t%-15s", p->NO, p->name);
			for(j = 0; j < n2; j++)
				printf("%f\t", p->ach[j]);
			printf("%f\t%f\n", p->sum, p->ave);
			i++;
		}
		printf("共%d个学生,请核对!\n", i);
	}
	else
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
}
//7.学号按从小到大排出成绩
void paixu_NO(struct stu *head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1;
	struct stu *r = NULL, *p = NULL, *p2 = NULL, *head2 = NULL, *rear2 = NULL;
	if(head != NULL) //纠错
	{
		printf("你选择了按学号从小到大排序!\n");
		while(head != NULL) ///复制链表，子函数单独操作,避开对全局影响,保障程序健壮性
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			p->NO = head->NO;
			strcpy(p->name, head->name);
			for(j = 0; j < n2; j++) ///传入成绩
				p->ach[j] = head->ach[j];
			if(head2 == NULL)
				head2 = rear2 = p;
			else
			{
				rear2->next = p;
				rear2 = p;
			}
			head = head->next;
		}
		rear2->next = NULL; ///复制链表
		p = head2;
		while(p != NULL) //计算每个学生的总分和平均数
		{
			p->sum = 0;
			for(j = 0; j <= n2 - 1; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //冒泡法排序，学号从小到大
		{
			flag = 0;
			p = head2;
			r = p->next;
			p2 = r->next;
			if(head2->NO > r->NO)
			{
				head2->next = r->next;
				r->next = head2;
				head2 = r;
				flag = 1;
			}
			else
				while(p2 != NULL)
				{
					if(r->NO > p2->NO)
					{
						r->next = p2->next;
						p2->next = r;
						p->next = p2;
						flag = 1;
					}
					p = p->next;
					r = p->next;
					p2 = r->next;
				}
		}//冒泡
		printf("Number  Name           ");
		for(j = 0; j < n2; j++)
			printf("%-9s\t", sub[j]);
		printf("SUM      \tAverage");
		printf("\n");
		for(p = head2; p != NULL; p = p->next)
		{
			printf("%-2d\t%-15s", p->NO, p->name);
			for(j = 0; j < n2; j++)
				printf("%f\t", p->ach[j]);
			printf("%f\t%f\n", p->sum, p->ave);
			i++;
		}
		printf("共%d个学生,请核对!\n", i);
	}
	else
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
}
//8.以字典的顺序排序排序
struct stu* paixu_Name(struct stu *head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1;
	struct stu *r = NULL, *p = NULL, *p2 = NULL, *head2 = head, *rear2 = NULL;
	if(head != NULL) //纠错
	{
		printf("你选择了名字按字典顺序排序!\n");
		/*while(head!=NULL) ///复制链表，子函数单独操作,避开对全局影响,保障程序健壮性
		{
		    p=(struct stu*)malloc(sizeof(struct stu));
		    p->NO=head->NO;
		    strcpy(p->name,head->name);
		    for(j=0; j<n2; j++) ///传入成绩
		        p->ach[j]=head->ach[j];
		    if(head2==NULL)
		        head2=rear2=p;
		    else
		    {
		        rear2->next=p;
		        rear2=p;
		    }
		    head=head->next;
		}
		rear2->next=NULL;///复制链表*/
		p = head2;
		while(p != NULL)
		{
			p->sum = 0; //计算每个学生的总分和平均数
			for(j = 0; j <= n2 - 1; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //冒泡法排序,姓名按字典顺序
		{
			flag = 0;
			p = head2;
			r = p->next;
			p2 = r->next;
			if(strcmp(head2->name, r->name) > 0)
			{
				head2->next = r->next;
				r->next = head2;
				head2 = r;
				flag = 1;
			}
			else
				while(p2 != NULL)
				{
					if(strcmp(r->name, p2->name) > 0)
					{
						r->next = p2->next;
						p2->next = r;
						p->next = p2;
						flag = 1;
					}
					p = p->next;
					r = p->next;
					p2 = r->next;
				}
		}//冒泡
		printf("Number  Name           ");
		for(j = 0; j < n2; j++)
			printf("%-9s\t", sub[j]);
		printf("SUM      \tAverage");
		printf("\n");
		for(p = head2; p != NULL; p = p->next)
		{
			printf("%-2d\t%-15s", p->NO, p->name);
			for(j = 0; j < n2; j++)
				printf("%f\t", p->ach[j]);
			printf("%f\t%f\n", p->sum, p->ave);
			i++;
		}
		printf("共%d个学生,请核对!\n", i);
	}
	else
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
	return head2;
}
//9.按学号查询学生排名及其考试成绩
void search1(struct stu*head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1, n;
	struct stu*p = NULL, *r = NULL, *p2 = NULL, *head2 = NULL, *rear2 = NULL;
	if(head != NULL) //纠错
	{
		printf("你选择了按学号查询学生成绩!\n");
		while(head != NULL) ///复制链表，子函数单独操作,避开对全局影响,保障程序健壮性
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			p->NO = head->NO;
			strcpy(p->name, head->name);
			for(j = 0; j < n2; j++) ///传入成绩
				p->ach[j] = head->ach[j];
			if(head2 == NULL)
				head2 = rear2 = p;
			else
			{
				rear2->next = p;
				rear2 = p;
			}
			head = head->next;
		}
		rear2->next = NULL; ///复制链表
		p = head2;
		while(p != NULL)
		{
			p->sum = 0; //计算每个学生的总分和平均数
			for(j = 0; j < n2; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //冒泡法排序，总成绩从大到小
		{
			flag = 0;
			p = head2;
			r = p->next;
			p2 = r->next;
			if(head2->sum < r->sum)
			{
				head2->next = r->next;
				r->next = head2;
				head2 = r;
				flag = 1;
			}
			else
				while(p2 != NULL)
				{
					if(r->sum < p2->sum)
					{
						r->next = p2->next;
						p2->next = r;
						p->next = p2;
						flag = 1;
					}
					p = p->next;
					r = p->next;
					p2 = r->next;
				}
		}
		printf("请输入你要查询的学号(限两位数):");
		scanf("%d", &n);
		p = head2;
		while(p != NULL) //查找该学生的信息
		{
			i++;
			if(p->NO == n)
			{
				flag = 1;
				printf("Name:%s\t", p->name);
				printf("No:%d  ", p->NO);
				for(j = 0; j < n2; j++)
				{
					printf("%s:%f\t", sub[j], p->ach[j]);
				}
				printf("SUM:%f\t", p->sum);
				printf("Average:%f   第%d名\n", p->ave, i);
			}
			p = p->next;
		}
		if(flag == 0)
			printf("你输入的学号所对应的学生不存在,请重新输入或录入文件!\n");
	}
	else
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
}
//10.按姓名查询学生排名及其考试成绩；需要考虑学生重名的情况
void search2(struct stu*head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1, k = 0;
	char n[15];
	struct stu*p = NULL, *r = NULL, *p2 = NULL, *head2 = NULL, *rear2 = NULL;
	if(head != NULL) //纠错
	{
		printf("你选择了按姓名查询学生成绩!\n");
		while(head != NULL) ///复制链表，子函数单独操作,避开对全局影响,保障程序健壮性
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			p->NO = head->NO;
			strcpy(p->name, head->name);
			for(j = 0; j < n2; j++) ///传入成绩
				p->ach[j] = head->ach[j];
			if(head2 == NULL)
				head2 = rear2 = p;
			else
			{
				rear2->next = p;
				rear2 = p;
			}
			head = head->next;
		}
		rear2->next = NULL; ///复制链表
		p = head2;
		while(p != NULL)
		{
			p->sum = 0; //计算每个学生的总分和平均数
			for(j = 0; j < n2; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //冒泡法排序，总成绩从大到小
		{
			flag = 0;
			p = head2;
			r = p->next;
			p2 = r->next;
			if(head2->sum < r->sum)
			{
				head2->next = r->next;
				r->next = head2;
				head2 = r;
				flag = 1;
			}
			else
				while(p2 != NULL)
				{
					if(r->sum < p2->sum)
					{
						r->next = p2->next;
						p2->next = r;
						p->next = p2;
						flag = 1;
					}
					p = p->next;
					r = p->next;
					p2 = r->next;
				}
		}
		printf("请输入你要查询的学生姓名(限15个字符):");
		scanf("%s", n);
		p = head2;
		while(p != NULL) //查找该学生的信息
		{
			i++;
			if(strcmp(p->name, n) == 0)
			{
				flag = 1;
				k++;
				printf("Name:%s\t", p->name);
				printf("Number:%d\t", p->NO);
				for(j = 0; j < n2; j++)
				{
					printf("%s:%f\t", sub[j], p->ach[j]);
				}
				printf("SUM:%f\t", p->sum);
				printf("Average:%f   第%d名\n", p->ave, i);
			}
			p = p->next;
		}
		if(k > 1)
			printf("你所查找的学生%s有%d个,请从学号区分!\n", n, k);
		if(flag == 0)
			printf("你查找的学生不存在,请重新输入或录入文件!\n");
	}
	else
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
}
//11.对每门课程分别统计每个类别的人数以及所占的百分比
void TongJi(struct stu*head, int n2, char sub[][10])
{
	int A[6], B[6], C[6], D[6], E[6]; //n2科各段所有人数
	int j, i = 0; //i统计学生总人数
	char FileName[20];
	FILE*fp = NULL;
	struct stu*p = NULL;
	if(head == NULL)
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
	else
	{
		printf("你选择了对每门课程分别统计每个类别的人数以及所占的百分比并输入文件!\n");
		memset(A, 0, sizeof(A)); //初始化
		memset(B, 0, sizeof(B));
		memset(C, 0, sizeof(C));
		memset(D, 0, sizeof(D));
		memset(E, 0, sizeof(E));
		p = head;
		while(p != NULL) //分段统计
		{
			for(j = 0; j < n2; j++)
			{
				if(p->ach[j] >= 90)
					A[j]++;
				else if(p->ach[j] >= 80)
					B[j]++;
				else if(p->ach[j] >= 70)
					C[j]++;
				else if(p->ach[j] >= 60)
					D[j]++;
				else if(p->ach[j] < 60)
					E[j]++;
			}
			i++;
			p = p->next;
		}
		for(j = 0; j < n2; j++)
		{
			printf("%-10s:优秀(90-100):%d人,占全班%-.2f%%"  , sub[j], A[j], ((float)A[j]) / i * 100);
			printf("   良好(80-89):%d人,占全班%-.2f%%\n", B[j], ((float)B[j]) / i * 100);
			printf("\t   中等(70-79):%d人,占全班%-.2f%%  ", C[j], ((float)C[j]) / i * 100);
			printf("  及格(60-69):%d人,占全班%-.2f%%\n", D[j], ((float)D[j]) / i * 100);
			printf("\t   不及格(0-59):%d人,占全班%-.2f%%\n", E[j], ((float)E[j]) / i * 100);
		}
		printf("现在写入文件,请输入文件名(可写入统计学生信息的文件中,限20字符):");
		scanf("%s", FileName);
		if((fp = fopen(FileName, "a")) == NULL)
			printf("文件打开(创建)失败,请从新选择11再试一次!\n");
		else
		{
			fseek(fp, 0, SEEK_END); //如果是追加输入,指针移至文件末尾
			fprintf(fp, "****************以下为对每门课程分别统计每个类别的人数以及所占的百分比****************\n");
			for(j = 0; j < n2; j++)
			{
				fprintf(fp, "%-10s:优秀(90-100):%d人,占全班%-.2f%%\n", sub[j], A[j], ((float)A[j]) / i * 100);
				fprintf(fp, "\t   良好(80-89):%d人,占全班%-.2f%%\n", B[j], ((float)B[j]) / i * 100);
				fprintf(fp, "\t   中等(70-79):%d人,占全班%-.2f%%\n", C[j], ((float)C[j]) / i * 100);
				fprintf(fp, "\t   及格(60-69):%d人,占全班%-.2f%%\n", D[j], ((float)D[j]) / i * 100);
				fprintf(fp, "\t   不及格(0-59):%d人,占全班%-.2f%%\n", E[j], ((float)E[j]) / i * 100);
			}
			printf("文件写入完毕!\n");
		}
		fclose(fp);
	}
}
//12.输出每个学生成绩
void output(int n2, char sub[][10], struct stu*head)
{
	struct stu* p = NULL;
	int i = 0, j;
	printf("你选择了输出每个学生成绩的功能!\n");
	if(head != NULL) //纠错
	{
		for(p = head; p != NULL; p = p->next)
		{
			p->sum = 0;
			for(j = 0; j < n2; j++)
				p->sum += p->ach[j];
			p->ave = p->sum / n2; //处理成绩
		}
		printf("Number  Name           ");
		for(j = 0; j < n2; j++)
			printf("%-9s\t", sub[j]);
		printf("SUM      \tAverage");
		printf("\n");
		for(p = head; p != NULL; p = p->next)
		{
			printf("%-2d\t%-15s", p->NO, p->name);
			for(j = 0; j < n2; j++)
				printf("%f\t", p->ach[j]);
			printf("%f\t%f\n", p->sum, p->ave);
			i++;
		}
		printf("共%d个学生,请核对!\n", i);
	}
	else
		printf("当前链表为空,请选择1功能从文件导入!\n\n");
}
//13.学生信息键入函数
void input(int n1, int n2, char sub[][10])
{
	struct stu stuinf;
	FILE *fp;
	char filename[20];
	int i, j;
	printf("你选择了手动输入每个学生的个人信息和成绩并写入文件!\n\n");
	printf("请输入文件名(限20个字符):");
	scanf("%s", filename);
	if((fp = fopen(filename, "w")) != NULL)
		printf("文件创建成功,请输入数据!\n\n");
	else
	{
		printf("文件创建失败,程序结束!\n");
		exit(0);
	}//文件纠错

	fprintf(fp, "Number  Name           ");
	for(j = 0; j < n2; j++)
		fprintf(fp, "%-9s\t", sub[j]);
	fprintf(fp, "\n");

	for(i = 0; i < n1; i++)
	{
		printf("请输入第%d个学生的学号(两位数)和姓名(限15字符):", i + 1);
		scanf("%d%s", &stuinf.NO, stuinf.name);
		fprintf(fp, "%-2d\t%-15s", stuinf.NO, stuinf.name);
		printf("请输入%s同学的成绩:\n", stuinf.name);
		for(j = 0; j < n2; j++)
		{
			printf("%-9s:\t", sub[j]);
			scanf("%f", &stuinf.ach[j]);
			fprintf(fp, "%f\t", stuinf.ach[j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("信息录入完毕,如需后续添加请选择功能2!\n");
}
