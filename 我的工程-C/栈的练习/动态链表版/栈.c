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
	printf("������ѹջ����:");
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
	printf("���ڹ���%d�����ݵ�Ԫ!\n",count);
}

int StackPop()
{
	int x;
	if(top==NULL)
		printf("��ջ����ջʧ��!\n");
	else
	{
		p=top;
		x=top->data;
		top=top->next;
		free(p);
		count--;
		printf("��������Ϊ:%d\n����%d�����ݵ�Ԫ!\n",x,count);
	}
	return x;
}

void main()
{
	char n;

	printf("������������������\n");
	printf("��  ��ѡ�����: ��\n");
	printf("��  1......ѹջ ��\n");
	printf("��  2......��ջ ��\n");
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
				StackPush();
				break;
			case '2':
				StackPop();
				break;
			default:printf("�������!\n");

		}
		printf("\n\n");
		printf("������������������\n");
		printf("��  ��ѡ�����: ��\n");
		printf("��  1......ѹջ ��\n");
		printf("��  2......��ջ ��\n");
		printf("��  0......�˳� ��\n");
		printf("������������������\n");

		n=getch();
		system("cls");
	}
}