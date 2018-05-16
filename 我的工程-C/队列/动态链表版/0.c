
#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node*next;
}* PNODE,NODE;

PNODE inPointer=NULL;
PNODE outPointer=NULL;
PNODE p=NULL;
int count=0;

void PutNode()
{
	p=(PNODE)malloc(sizeof(NODE));
	printf("请输入你要添加的数据:");
	scanf("%d",&p->data);
	p->next=NULL;

	if(inPointer==NULL)
	{
		inPointer=p;
		outPointer=p;
	}
	else
	{
		inPointer->next=p;
		inPointer=p;
	}
	count++;
	printf("数据入队成功,共有%d个数据单元!\n",count);
}

int GetNode()
{
	int x;
	if(outPointer==NULL)
		printf("队列为空,出队失败!\n");
	else
	{
		p=outPointer;
		x=p->data;
		outPointer=outPointer->next;
		free(p);
		count--;
		printf("出队元素为:%d\n还有%d个数据单元!\n",x,count);
	}
	return x;
}

void main()
{
	char n;

	printf("┏━━━━━━━┓\n");
	printf("┃  请选择操作: ┃\n");
	printf("┃  1......入队 ┃\n");
	printf("┃  2......出队 ┃\n");
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
			PutNode();
			break;
		case '2':
			GetNode();
			break;
		default:printf("输入错误!\n");

		}
		printf("\n\n");
		printf("┏━━━━━━━┓\n");
		printf("┃  请选择操作: ┃\n");
		printf("┃  1......入队 ┃\n");
		printf("┃  2......出队 ┃\n");
		printf("┃  0......退出 ┃\n");
		printf("┗━━━━━━━┛\n");

		n=getch();
		system("cls");
	}
}