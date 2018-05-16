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
		printf("��������,���ʧ��!\n");
	else
	{
		printf("��������Ҫ��ӵ�����:");
		scanf("%d",&x);
		queue[inPointer]=x;
		inPointer=(inPointer+1)%size;
		count++;
		printf("��ӳɹ�!\n");
	}
}

int GetX()
{
	int x = 0;
	if(count<=0)
		printf("����Ϊ��,����ʧ��!\n");
	else
	{
		x=queue[outPointer];
		outPointer=(outPointer+1)%size;
		count--;
		printf("���ӳɹ�,");
	}
	return x;
}

void outPut()
{
	int i;
	printf("����Ϊ:");
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
		printf("��!\n");
}

void main()
{
	char n;
	inPointer=0;
	outPointer=0;
	count=0;

	printf("������������������\n");
	printf("��  ��ѡ�����: ��\n");
	printf("��  1......��� ��\n");
	printf("��  2......���� ��\n");
	printf("��  0......�˳� ��\n");
	printf("������������������\n");

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
					printf("����Ԫ��Ϊ:%d\n",GetX());
					outPut();
				}
				else
					GetX();
				break;
			default:printf("�������!\n");

		}
		printf("\n\n");
		printf("������������������\n");
		printf("��  ��ѡ�����: ��\n");
		printf("��  1......��� ��\n");
		printf("��  2......���� ��\n");
		printf("��  0......�˳� ��\n");
		printf("������������������\n");

		n=getch();
		system("cls");
	}
}