#include<stdio.h>
#include<string.h>
int  main()
{
    int a[40000];
    int N;
    int s=0;//进位
    long temp;//中间变量，每位数与i相称的结果
    int i,j=0;
    memset(a,-1,sizeof(a));
    printf("输入阶乘数:");
    scanf("%d",&N);

    a[0]=1;
    for(i=1; i<=N; i++)
    {
        s=0;
        for(j=0; a[j+1]!=-1; j++) //如果数组中不止一位，则计算到j-1位，最后一位单独处理
        {
            temp=a[j]*i+s;//每一位乘以i加上上一位的进位
            a[j]=temp%10;//取个位数
            s=temp/10;//进位数
        }


        temp=a[j]*i+s;//数组中只有一位或最后一位单独处理
        while(temp!=0)
        {
            a[j]=temp%10;
            temp=temp/10;
            j++;
        }

    }
    FILE *pf;
    pf=fopen("result.txt","w");

    printf("结果共有%d位:\n\n",j);
    for(j--; j>-1; j--) //倒序输出
    {
        fprintf(pf,"%d",a[j]);
        printf("%d",a[j]);
    }
    printf("\n\n");


    printf("按任意键结束!");
    getchar();
    getchar();
    return 0;
}
