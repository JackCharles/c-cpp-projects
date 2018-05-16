
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
	printf("��������Ҫ��ӵ�����:");
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
	printf("������ӳɹ�,����%d�����ݵ�Ԫ!\n",count);
}

int GetNode()
{
	int x;
	if(outPointer==NULL)
		printf("����Ϊ��,����ʧ��!\n");
	else
	{
		p=outPointer;
		x=p->data;
		outPointer=outPointer->next;
		free(p);
		count--;
		printf("����Ԫ��Ϊ:%d\n����%d�����ݵ�Ԫ!\n",x,count);
	}
	return x;
}

void main()
{
	char n;

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
			PutNode();
			break;
		case '2':
			GetNode();
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