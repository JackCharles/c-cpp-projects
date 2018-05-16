#include<stdio.h>
#include<stdlib.h>

typedef struct NODE
{
	int data;
	struct NODE*next;
}*PNODE,NODE;

PNODE top=NULL;
PNODE p=NULL;
int count=0; 

void StackPush()
{
	p=(PNODE)malloc(sizeof(NODE));
	printf("请输入压栈数据:");
	scanf("%d",&p->data);
	p->next=NULL;

	if(top==NULL)
		top=p;
	else
	{
		p->next=top;
		top=p;
	}
	count++;
	printf("现在共有%d个数据单元!\n",count);
}

int StackPop()
{
	int x;
	if(top==NULL)
		printf("空栈，弹栈失败!\n");
	else
	{
		p=top;
		x=top->data;
		top=top->next;
		free(p);
		count--;
		printf("弹出数据为:%d\n还有%d个数据单元!\n",x,count);
	}
	return x;
}

void main()
{
	char n;

	printf("┏━━━━━━━┓\n");
	printf("┃  请选择操作: ┃\n");
	printf("┃  1......压栈 ┃\n");
	printf("┃  2......弹栈 ┃\n");
	printf("┃  0......退出 ┃\n");
	printf("┗━━━━━━━┛\n");

	n=getch();
	system("cls");

	while(1)
	{
		switch(n)
		{
			case '0':
				exit(0);
				break;
			case '1':
				StackPush();
				break;
			case '2':
				StackPop();
				break;
			default:printf("输入错误!\n");

		}
		printf("\n\n");
		printf("┏━━━━━━━┓\n");
		printf("┃  请选择操作: ┃\n");
		printf("┃  1......压栈 ┃\n");
		printf("┃  2......弹栈 ┃\n");
		printf("┃  0......退出 ┃\n");
		printf("┗━━━━━━━┛\n");

		n=getch();
		system("cls");
	}
}