#include<stdio.h>

#define num_max 20
#define ope_max 30

float num[num_max];
char ope[ope_max];
int num_top,ope_top;

void num_push(float nNum)
{
	num[num_top]=nNum;
	num_top++;
}

float num_pop()
{
	float x=num[num_top-1];
	num_top--;
	return x;
}

void ope_push(char ch)
{
	ope[ope_top]=ch;
	ope_top++;
}

char ope_pop()
{
	char x=ope[ope_top-1];
	ope_top--;
	return x;
}

void top_operate()
{
	char op;
	float num1,num2,num;
	op=ope_pop();//��������������м��㣬���Ҹ���������ٴ���
	num1=num_pop();
	num2=num_pop();
	switch (op)
	{
        case '+':
            num=num2+num1;
            break;
        case '-':
            num=num2-num1;
            break;
        case '*':
            num=num2*num1;
            break;
        case '/':
            num=num2/num1;
            break;

	}
	num_push(num);
}

int main()
{
    int i;
    char buffer[50],ch;

    num_top=0;
    ope_top=0;
    ope_push('#');//��ʼ��

    printf("�������������������ʽ���ԡ�#������:");
    scanf("%s",buffer);

    for(i=0;buffer[i]!='#';i++)
    {
        ch=buffer[i];
        if(ch>='0'&&ch<='9')
            num_push(ch-'0');
        else
            switch(ch)
            {
                case '(':
                    ope_push(ch);
                    break;

                case ')':
                    while(ope[ope_top-1]!='(')
                        top_operate();
					ope_pop();
                    break;

                case '*':;

                case '/':
                    while(ope[ope_top-1]=='*'||ope[ope_top-1]=='/')
                        top_operate();
                    ope_push(ch);
                    break;

                case '+':;

                case '-':
                    while(ope[ope_top-1]!='('&&ope[ope_top-1]!='#')
                        top_operate();
                    ope_push(ch);
                    break;
            }

    }
    while(ope[ope_top-1]!='#')
        top_operate();
    printf("�����:%f\n",num[num_top-1]);
    return 0;
}
