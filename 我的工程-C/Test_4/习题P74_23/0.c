#include<stdio.h>
void main ()
{
	char a[121],temp,b;//b是酒的类型,temp读掉输入的逗号
	int i,j,k,n,sum=0;//n是酒的变化数量,sum_A是当前酒窖A酒的数量
	for(i=0;i<121;i++)
		a[i]=' ';//初始化
	printf("请输入酒的数量变化及类型如(“2,A”表示买两瓶A型酒):\n");
	scanf("%d%c%c",&n,&temp,&b);

	for(i=1;i<121&&n!=0; ){//酒的顺序从1开始，舍去0位置
//**************************************************
		if(n>0)//买酒
		{	
			if(n<=120)//防止数据溢出
			{
				k=0;
				for(i=1;i<121&&k<n;i++)
				{
					if(a[i]==' ')
					{
						a[i]=b;
						k++;
					}
				}
				sum=sum+n;
				for(i=1;i<=sum;i++)
					printf("%2c",a[i]);
				printf("\n");
			}
			else
				printf("你的酒窖不够大，只能放置120瓶酒!");
		}
//*************************************************
		else if(n<0)//喝酒
		{	
			j=0;
			for(i=1;i<=sum;i++)
				if(a[i]==b)
					j++;//统计当前要喝的酒的数量
			if(j>=-n)//判断要喝的酒是否充足
			{
				k=0;
				for(i=1;i<=sum&&k<-n;i++)
				{	
					if(a[i]==b)
					{
						a[i]=' ';
						k++;
					}
				}
				for(i=1;i<=sum;i++)
					printf("%2c",a[i]);
			}
			else//当酒不够时发出警告
				printf("%c型酒不够了，请及时购买!",b);
		}
//***************************************************
			printf("\n");
		scanf("%d%c%c",&n,&temp,&b);
	}
}