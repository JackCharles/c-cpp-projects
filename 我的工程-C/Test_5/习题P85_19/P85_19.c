#include <stdio.h>
#define n 3
//******************************************
int Del(char x[],char y)
{
	int i,j,k=0;
	for(i=0;i<n-k;i++)
		if(x[i]==y)
		{
			for(j=i;j<n-k-1;j++)
				x[j]=x[j+1];
			k++;
		}
	return k;
}
//*******************************************
void main(){
	char x[n];
	char y='g';
	int a,i;
	scanf("%s",x);
	a=Del(x,y);
	printf("%d	",a);
	if(n-a<=0)
		printf(" ");
	else
		for(i=0;i<n-a;i++)
			printf("%2c",x[i]);
	printf("\n");
}
//**********************************************