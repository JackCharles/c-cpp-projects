#include<stdio.h>
#include<string.h>
int  main()
{
    int a[40000];
    int N;
    int s=0;//��λ
    long temp;//�м������ÿλ����i��ƵĽ��
    int i,j=0;
    memset(a,-1,sizeof(a));
    printf("����׳���:");
    scanf("%d",&N);

    a[0]=1;
    for(i=1; i<=N; i++)
    {
        s=0;
        for(j=0; a[j+1]!=-1; j++) //��������в�ֹһλ������㵽j-1λ�����һλ��������
        {
            temp=a[j]*i+s;//ÿһλ����i������һλ�Ľ�λ
            a[j]=temp%10;//ȡ��λ��
            s=temp/10;//��λ��
        }


        temp=a[j]*i+s;//������ֻ��һλ�����һλ��������
        while(temp!=0)
        {
            a[j]=temp%10;
            temp=temp/10;
            j++;
        }

    }
    FILE *pf;
    pf=fopen("result.txt","w");

    printf("�������%dλ:\n\n",j);
    for(j--; j>-1; j--) //�������
    {
        fprintf(pf,"%d",a[j]);
        printf("%d",a[j]);
    }
    printf("\n\n");


    printf("�����������!");
    getchar();
    getchar();
    return 0;
}
