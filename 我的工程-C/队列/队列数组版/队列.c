#include<stdio.h>
#include<stdlib.h>

#define size 5
int count;
int inPointer;
int outPointer;
int queue[size];

void PutX()
{
	int x;
	if(count>=size)
		printf("队列已满,入队失败!\n");
	else
	{
		printf("请输入需要入队的数据:");
		scanf("%d",&x);
		queue[inPointer]=x;
		inPointer=(inPointer+1)%size;
		count++;
		printf("入队成功!\n");
	}
}

int GetX()
{
	int x = 0;
	if(count<=0)
		printf("队列为空,出队失败!\n");
	else
	{
		x=queue[outPointer];
		outPointer=(outPointer+1)%size;
		count--;
		printf("出队成功,");
	}
	return x;
}

void outPut()
{
	int i;
	printf("队列为:");
	if(outPointer<inPointer)
		for(i=outPointer;i<inPointer;i++)
			printf("%d  ",queue[i]);
	else if(outPointer>inPointer)
	{
		for(i=outPointer;i<size;i++)
			printf("%d  ",queue[i]);
		for(i=0;i<inPointer;i++)
			printf("%d  ",queue[i]);
	}
	else if(count==size)
		for(i=0;i<size;i++)
			printf("%d  ",queue[i]);
	else if(count==0)
		printf("空!\n");
}

void main()
{
	char n;
	inPointer=0;
	outPointer=0;
	count=0;

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
				PutX();
				outPut();
				break;
			case '2':
				if(count>0)
				{
					printf("出队元素为:%d\n",GetX());
					outPut();
				}
				else
					GetX();
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