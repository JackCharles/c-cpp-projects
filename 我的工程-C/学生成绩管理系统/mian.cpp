#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stu
{
	char name[15];
	int NO;
	float ach[6];
	float sum;//�ܳɼ�
	float ave;//ƽ���ɼ�
	char Fname[20];//�����ļ���,���ڶ���ʹ��
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
	int n1, n2, n3, i; //ѧ����,��Ŀ��,���ܴ���
	char sub[6][10];//ѧ������
	printf("****************��ӭʹ��ѧ���ɼ�����ϵͳ************\n");
	printf("������ѧ����:");
	scanf("%d", &n1);
	printf("�������Ŀ��(������6��):");
	scanf("%d", &n2);
	while(n2 > 6)
	{
		printf("������Ŀ�Ŀ������6��,����������:");
		scanf("%d", &n2);
	}//��Ŀ������
	printf("��������%d�ƵĿ�Ŀ����(��10���ַ�):", n2);
	for(i = 0; i < n2; i++)
		scanf("%s", sub[i]);

	printf("��������������������������ѡ����Ҫ���еĲ���(0-13)����������������������\n");
	printf("��  01.Read from a file                                               ��\n");
    printf("��  02.Append record manually                                         ��\n");
	printf("��  03.Calculate total and average score of every course              ��\n");
	printf("��  04.Calculate total and average score of every student             ��\n");
    printf("��  05.Sort in descending order by total score of every student       ��\n");
	printf("��  06.Sort in ascending order by total score of every stuednet       ��\n");
    printf("��  07.Sort in ascending order by number                              ��\n");
	printf("��  08.Sort in dictionary order by name                               ��\n");
    printf("��  09.Search by number                                               ��\n");
    printf("��  10.Search by name                                                 ��\n");
	printf("��  11.Statistic analysis for every course                            ��\n");
    printf("��  12.List record                                                    ��\n");
    printf("��  13.Write to a file                                                ��\n");
    printf("��  00.Exit                                                           ��\n");
	printf("������������������������������������������������������������������������\n");

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
				printf("��ѡ��Ĺ��ܲ�����,������ѡ��!\n");
		}//switch
	printf("��������������������������ѡ����Ҫ���еĲ���(0-13)����������������������\n");
	printf("��  01.Read from a file                                               ��\n");
    printf("��  02.Append record manually                                         ��\n");
	printf("��  03.Calculate total and average score of every course              ��\n");
	printf("��  04.Calculate total and average score of every student             ��\n");
    printf("��  05.Sort in descending order by total score of every student       ��\n");
	printf("��  06.Sort in ascending order by total score of every stuednet       ��\n");
    printf("��  07.Sort in ascending order by number                              ��\n");
	printf("��  08.Sort in dictionary order by name                               ��\n");
    printf("��  09.Search by number                                               ��\n");
    printf("��  10.Search by name                                                 ��\n");
	printf("��  11.Statistic analysis for every course                            ��\n");
    printf("��  12.List record                                                    ��\n");
    printf("��  13.Write to a file                                                ��\n");
    printf("��  00.Exit                                                           ��\n");
	printf("������������������������������������������������������������������������\n");
	scanf("%d", &n3);
	system("cls");
	}//while
	printf("��л���ʹ��,�ټ�!\n");
	return 0;
}//main
//1.���ļ���ȡ����
struct stu* ReadFile(int n2)
{
	struct stu* head = NULL, *rear = NULL, *p = NULL;
	FILE*fp;
	char fname[20], str[100]; //str[100]���ڶ����ļ���ͷ
	int i = 0, j;
	printf("��ѡ���˴��ļ���ȡѧ������!\n");
	printf("������Ҫ��ȡ���ļ���(��ȷ����ȡ���ļ�����ѧ����Ϣ):");
	scanf("%s", fname);
	if((fp = fopen(fname, "r")) == NULL)
		printf("�ļ���ȡʧ��,������ѡ��������ȷ���ļ�����,����ѡ��13�������ļ�!\n");
	else
	{
		fgets(str, sizeof(str), fp); //������һ��
		do///�˴�����feof����ΪfeofҪԽ��������־EOF�ŷ��ط�0ֵ,�պ�����EOF�򷵻�0,�������ѭ�����¶��ȡһ��������Ϣ
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			fscanf(fp, "%d%s", &p->NO, p->name);
			for(j = 0; j < n2; j++)
			{
				fscanf(fp, "%f", &p->ach[j]); //һ��ͬѧ��n2�Ƴɼ�
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
			fgetc(fp);//����\t
			fgetc(fp);//����\n
			str[99] = fgetc(fp); //��ȡ��һ���׸��ַ���str[99]��ȡ��ǰ��û��ʵ�����õ�һ������
			fseek(fp, -1, 1); ///�˴����ļ�ָ�������һλ,��Ϊstr[99]���ļ�ָ��ָ���������ַ�֮�����ļ�û�н�β,
		}
		while(str[99] != '*' && str[99] != EOF); ///�����ѧ����Ϣ��ȡ����ң�!='*'����Ϊ11����ͳ����Ϣ���ܻ����뵽���ļ���
		fclose(fp); ///ͳ����Ϣ��һ���ַ���'*',�ų�ͳ����Ϣ��ѧ����Ϣ��ȡ�ĸ���
		strcpy(head->Fname, fname); ///�˴��ļ�������أ��ʷ��ڽṹ���д���
		rear->next = NULL;
		if(head == NULL || rear == NULL)
			printf("�ļ�¼��ʧ��,������!");
		printf("�㹲¼��%d��ѧ����(%d��)�ɼ�!\n", i, n2);
	}
	return head;
}
//2.����ʽ�ֶ����루���ӵ���ͷ��
struct stu*Add(struct stu*head, int n2, char sub[][10])
{
	int i, j, n, flag1, flag2; //nΪ���ӵ�����
	char Fname[20];
	struct stu*p = head, *r = NULL, *head0 = head;
	FILE*fp;
	if(head == NULL)
		printf("��ǰ����Ϊ��,����ѡ��1���ļ���ȡ��ѡ��13�����ļ�������������!\n\n");
	else
	{
		printf("������Ҫ���ӵ�����:");
		scanf("%d", &n);
		for(i = 0; i < n; i++)
		{
			flag1 = 0;
			flag2 = 0;
			p = (struct stu*)malloc(sizeof(struct stu));
			printf("���������ӵĵ�%d��ѧ����ѧ��(����λ��)������(��15�ַ�):", i + 1);
			scanf("%d%s", &(p->NO), p->name);
			r = head;
			while(r != NULL) //��������ظ�����
			{
				if(strcmp(p->name, r->name) == 0)
					flag1 = 1;
				r = r->next;
			}
			r = head;
			while(r != NULL) //���ѧ�������ظ�
			{
				if(p->NO == r->NO)
					flag2 = 1;
				r = r->next;
			}
			if(flag1)
			{
				if(flag2)
				{
					printf("�������ѧ�ź����������ظ�,�������ݺ���������ѧ��(�Ա��ѧ������):");
					scanf("%d", &(p->NO));
				}
				printf("���������ظ�,����Ӧ��ѧ�Ų��ظ�(�ɴ�ѧ������),�����...\n");
			}
			else if(flag2)
			{
				printf("�������ѧ���ظ�,��˶���Ϣ����������ѧ��:");
				scanf("%d", &(p->NO));
			}
			printf("������%sѧ���ĳɼ�:\n", p->name);
			for(j = 0; j < n2; j++)
			{
				printf("%-10s:", sub[j]);
				scanf("%f", &p->ach[j]);
			}
			p->next = head;
			head = p; ///����ͷ���
		}//for
		printf("%d��ѧ����Ϣ��ӳɹ�,���ڱ��浽�ļ�\n", n);
		if((fp = fopen(head0->Fname, "w")) == NULL)
			printf("���浽�ļ�ʧ��,������!\n");
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
			printf("���浽�ļ��ɹ�!\n");
		}
	}//if(head==NULL)
	return head;
}
//3.����ÿ�ſγ̵��ֺܷ�ƽ����
void EverySub(struct stu*head, int n2, char sub[][10])
{
	struct stu*p = head;
	float sum[6], ave[6]; //������Ŀ�ܺ�ƽ������
	int i = 0, j;
	memset(sum, 0, sizeof(sum)); //��ʼ��Ϊ0
	if(head == NULL)
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
	else
	{
		printf("��ѡ���˼���ÿ�ſγ��ֺܷ�ƽ���ֵĹ���!\n");
		while(p != NULL)
		{
			for(j = 0; j < n2; j++)
				sum[j] += p->ach[j];
			p = p->next;
			i++;//ͳ��ѧ��������ʼ�����ѧ�����ں��������п��ܻ��б䶯������n2
		}//����ÿ�ſγ��ܷ�
		for(j = 0; j < n2; j++)
			ave[j] = sum[j] / i; //����ÿ�ſγ�ƽ����
		for(j = 0; j < n2; j++) //���
			printf("%-10s:\tSUM:%f\tAverage:%f\n", sub[j], sum[j], ave[j]);
		printf("��%d�ƿ��Գɼ�,��˶�!\n", n2);
	}
}
//4.����ÿ��ѧ�����ֺܷ�ƽ����
void EveryStu(struct stu*head, int n2)
{
	struct stu*p = head;
	int i = 0, j;
	if(head == NULL)
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
	else
	{
		printf("��ѡ���˼���ÿ��ѧ�����ֺܷ�ƽ���ֵĹ���!\n");
		while(p != NULL) //����ÿ��ѧ�����ֺܷ�ƽ����
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
		printf("��%d��ѧ��,��˶�!\n", i);
	}
}
//5.��ÿ��ѧ�����ܷ��ɸߵ����ų����α�
struct stu* EveryStu1(struct stu*head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1;
	struct stu*p = NULL, *r = NULL, *p2 = NULL, *head2 = head, *rear2 = NULL;
	if(head != NULL) //����
	{
		printf("��ѡ���˰�ÿ��ѧ�����ܷ��ɸߵ����ų����α�!\n");
		/*while(head!=NULL) ///���������Ӻ�����������,�ܿ���ȫ��Ӱ��,���ϳ���׳��
		{
		    p=(struct stu*)malloc(sizeof(struct stu));
		    p->NO=head->NO;
		    strcpy(p->name,head->name);
		    for(j=0; j<n2; j++) ///����ɼ�
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
		rear2->next=NULL;///��������*/
		p = head2;

		while(p != NULL)
		{
			p->sum = 0; //����ÿ��ѧ�����ֺܷ�ƽ����
			for(j = 0; j < n2; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //ð�ݷ������ܳɼ��Ӵ�С
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
			i++;//ͳ������
		}
		printf("��%d��ѧ��,��˶�!\n", i);
	}
	else
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
	return head2;
}
//6.��ÿ��ѧ�����ܷ��ɵ͵����ų����α�
void EveryStu2(struct stu*head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1;
	struct stu*p = NULL, *r = NULL, *p2 = NULL, *head2 = NULL, *rear2 = NULL;
	if(head != NULL) //����
	{
		printf("��ѡ���˰�ÿ��ѧ�����ܷ��ɵ͵����ų����α�!\n");
		while(head != NULL) ///���������Ӻ�����������,�ܿ���ȫ��Ӱ��,���ϳ���׳��
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			p->NO = head->NO;
			strcpy(p->name, head->name);
			for(j = 0; j < n2; j++) ///����ɼ�
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
		rear2->next = NULL; ///��������
		p = head2;
		while(p != NULL)
		{
			p->sum = 0; //����ÿ��ѧ�����ֺܷ�ƽ����
			for(j = 0; j < n2; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //ð�ݷ������ܳɼ���С����
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
		printf("��%d��ѧ��,��˶�!\n", i);
	}
	else
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
}
//7.ѧ�Ű���С�����ų��ɼ�
void paixu_NO(struct stu *head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1;
	struct stu *r = NULL, *p = NULL, *p2 = NULL, *head2 = NULL, *rear2 = NULL;
	if(head != NULL) //����
	{
		printf("��ѡ���˰�ѧ�Ŵ�С��������!\n");
		while(head != NULL) ///���������Ӻ�����������,�ܿ���ȫ��Ӱ��,���ϳ���׳��
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			p->NO = head->NO;
			strcpy(p->name, head->name);
			for(j = 0; j < n2; j++) ///����ɼ�
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
		rear2->next = NULL; ///��������
		p = head2;
		while(p != NULL) //����ÿ��ѧ�����ֺܷ�ƽ����
		{
			p->sum = 0;
			for(j = 0; j <= n2 - 1; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //ð�ݷ�����ѧ�Ŵ�С����
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
		}//ð��
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
		printf("��%d��ѧ��,��˶�!\n", i);
	}
	else
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
}
//8.���ֵ��˳����������
struct stu* paixu_Name(struct stu *head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1;
	struct stu *r = NULL, *p = NULL, *p2 = NULL, *head2 = head, *rear2 = NULL;
	if(head != NULL) //����
	{
		printf("��ѡ�������ְ��ֵ�˳������!\n");
		/*while(head!=NULL) ///���������Ӻ�����������,�ܿ���ȫ��Ӱ��,���ϳ���׳��
		{
		    p=(struct stu*)malloc(sizeof(struct stu));
		    p->NO=head->NO;
		    strcpy(p->name,head->name);
		    for(j=0; j<n2; j++) ///����ɼ�
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
		rear2->next=NULL;///��������*/
		p = head2;
		while(p != NULL)
		{
			p->sum = 0; //����ÿ��ѧ�����ֺܷ�ƽ����
			for(j = 0; j <= n2 - 1; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //ð�ݷ�����,�������ֵ�˳��
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
		}//ð��
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
		printf("��%d��ѧ��,��˶�!\n", i);
	}
	else
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
	return head2;
}
//9.��ѧ�Ų�ѯѧ���������俼�Գɼ�
void search1(struct stu*head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1, n;
	struct stu*p = NULL, *r = NULL, *p2 = NULL, *head2 = NULL, *rear2 = NULL;
	if(head != NULL) //����
	{
		printf("��ѡ���˰�ѧ�Ų�ѯѧ���ɼ�!\n");
		while(head != NULL) ///���������Ӻ�����������,�ܿ���ȫ��Ӱ��,���ϳ���׳��
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			p->NO = head->NO;
			strcpy(p->name, head->name);
			for(j = 0; j < n2; j++) ///����ɼ�
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
		rear2->next = NULL; ///��������
		p = head2;
		while(p != NULL)
		{
			p->sum = 0; //����ÿ��ѧ�����ֺܷ�ƽ����
			for(j = 0; j < n2; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //ð�ݷ������ܳɼ��Ӵ�С
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
		printf("��������Ҫ��ѯ��ѧ��(����λ��):");
		scanf("%d", &n);
		p = head2;
		while(p != NULL) //���Ҹ�ѧ������Ϣ
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
				printf("Average:%f   ��%d��\n", p->ave, i);
			}
			p = p->next;
		}
		if(flag == 0)
			printf("�������ѧ������Ӧ��ѧ��������,�����������¼���ļ�!\n");
	}
	else
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
}
//10.��������ѯѧ���������俼�Գɼ�����Ҫ����ѧ�����������
void search2(struct stu*head, int n2, char sub[][10])
{
	int i = 0, j, flag = 1, k = 0;
	char n[15];
	struct stu*p = NULL, *r = NULL, *p2 = NULL, *head2 = NULL, *rear2 = NULL;
	if(head != NULL) //����
	{
		printf("��ѡ���˰�������ѯѧ���ɼ�!\n");
		while(head != NULL) ///���������Ӻ�����������,�ܿ���ȫ��Ӱ��,���ϳ���׳��
		{
			p = (struct stu*)malloc(sizeof(struct stu));
			p->NO = head->NO;
			strcpy(p->name, head->name);
			for(j = 0; j < n2; j++) ///����ɼ�
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
		rear2->next = NULL; ///��������
		p = head2;
		while(p != NULL)
		{
			p->sum = 0; //����ÿ��ѧ�����ֺܷ�ƽ����
			for(j = 0; j < n2; j++)
				p->sum = p->sum + p->ach[j];
			p->ave = p->sum / n2;
			p = p->next;
		}
		while(flag) //ð�ݷ������ܳɼ��Ӵ�С
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
		printf("��������Ҫ��ѯ��ѧ������(��15���ַ�):");
		scanf("%s", n);
		p = head2;
		while(p != NULL) //���Ҹ�ѧ������Ϣ
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
				printf("Average:%f   ��%d��\n", p->ave, i);
			}
			p = p->next;
		}
		if(k > 1)
			printf("�������ҵ�ѧ��%s��%d��,���ѧ������!\n", n, k);
		if(flag == 0)
			printf("����ҵ�ѧ��������,�����������¼���ļ�!\n");
	}
	else
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
}
//11.��ÿ�ſγ̷ֱ�ͳ��ÿ�����������Լ���ռ�İٷֱ�
void TongJi(struct stu*head, int n2, char sub[][10])
{
	int A[6], B[6], C[6], D[6], E[6]; //n2�Ƹ�����������
	int j, i = 0; //iͳ��ѧ��������
	char FileName[20];
	FILE*fp = NULL;
	struct stu*p = NULL;
	if(head == NULL)
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
	else
	{
		printf("��ѡ���˶�ÿ�ſγ̷ֱ�ͳ��ÿ�����������Լ���ռ�İٷֱȲ������ļ�!\n");
		memset(A, 0, sizeof(A)); //��ʼ��
		memset(B, 0, sizeof(B));
		memset(C, 0, sizeof(C));
		memset(D, 0, sizeof(D));
		memset(E, 0, sizeof(E));
		p = head;
		while(p != NULL) //�ֶ�ͳ��
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
			printf("%-10s:����(90-100):%d��,ռȫ��%-.2f%%"  , sub[j], A[j], ((float)A[j]) / i * 100);
			printf("   ����(80-89):%d��,ռȫ��%-.2f%%\n", B[j], ((float)B[j]) / i * 100);
			printf("\t   �е�(70-79):%d��,ռȫ��%-.2f%%  ", C[j], ((float)C[j]) / i * 100);
			printf("  ����(60-69):%d��,ռȫ��%-.2f%%\n", D[j], ((float)D[j]) / i * 100);
			printf("\t   ������(0-59):%d��,ռȫ��%-.2f%%\n", E[j], ((float)E[j]) / i * 100);
		}
		printf("����д���ļ�,�������ļ���(��д��ͳ��ѧ����Ϣ���ļ���,��20�ַ�):");
		scanf("%s", FileName);
		if((fp = fopen(FileName, "a")) == NULL)
			printf("�ļ���(����)ʧ��,�����ѡ��11����һ��!\n");
		else
		{
			fseek(fp, 0, SEEK_END); //�����׷������,ָ�������ļ�ĩβ
			fprintf(fp, "****************����Ϊ��ÿ�ſγ̷ֱ�ͳ��ÿ�����������Լ���ռ�İٷֱ�****************\n");
			for(j = 0; j < n2; j++)
			{
				fprintf(fp, "%-10s:����(90-100):%d��,ռȫ��%-.2f%%\n", sub[j], A[j], ((float)A[j]) / i * 100);
				fprintf(fp, "\t   ����(80-89):%d��,ռȫ��%-.2f%%\n", B[j], ((float)B[j]) / i * 100);
				fprintf(fp, "\t   �е�(70-79):%d��,ռȫ��%-.2f%%\n", C[j], ((float)C[j]) / i * 100);
				fprintf(fp, "\t   ����(60-69):%d��,ռȫ��%-.2f%%\n", D[j], ((float)D[j]) / i * 100);
				fprintf(fp, "\t   ������(0-59):%d��,ռȫ��%-.2f%%\n", E[j], ((float)E[j]) / i * 100);
			}
			printf("�ļ�д�����!\n");
		}
		fclose(fp);
	}
}
//12.���ÿ��ѧ���ɼ�
void output(int n2, char sub[][10], struct stu*head)
{
	struct stu* p = NULL;
	int i = 0, j;
	printf("��ѡ�������ÿ��ѧ���ɼ��Ĺ���!\n");
	if(head != NULL) //����
	{
		for(p = head; p != NULL; p = p->next)
		{
			p->sum = 0;
			for(j = 0; j < n2; j++)
				p->sum += p->ach[j];
			p->ave = p->sum / n2; //����ɼ�
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
		printf("��%d��ѧ��,��˶�!\n", i);
	}
	else
		printf("��ǰ����Ϊ��,��ѡ��1���ܴ��ļ�����!\n\n");
}
//13.ѧ����Ϣ���뺯��
void input(int n1, int n2, char sub[][10])
{
	struct stu stuinf;
	FILE *fp;
	char filename[20];
	int i, j;
	printf("��ѡ�����ֶ�����ÿ��ѧ���ĸ�����Ϣ�ͳɼ���д���ļ�!\n\n");
	printf("�������ļ���(��20���ַ�):");
	scanf("%s", filename);
	if((fp = fopen(filename, "w")) != NULL)
		printf("�ļ������ɹ�,����������!\n\n");
	else
	{
		printf("�ļ�����ʧ��,�������!\n");
		exit(0);
	}//�ļ�����

	fprintf(fp, "Number  Name           ");
	for(j = 0; j < n2; j++)
		fprintf(fp, "%-9s\t", sub[j]);
	fprintf(fp, "\n");

	for(i = 0; i < n1; i++)
	{
		printf("�������%d��ѧ����ѧ��(��λ��)������(��15�ַ�):", i + 1);
		scanf("%d%s", &stuinf.NO, stuinf.name);
		fprintf(fp, "%-2d\t%-15s", stuinf.NO, stuinf.name);
		printf("������%sͬѧ�ĳɼ�:\n", stuinf.name);
		for(j = 0; j < n2; j++)
		{
			printf("%-9s:\t", sub[j]);
			scanf("%f", &stuinf.ach[j]);
			fprintf(fp, "%f\t", stuinf.ach[j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("��Ϣ¼�����,������������ѡ����2!\n");
}
