#include<stdio.h>
#include<string.h>
#define n 5
void main(){
	char name[n][20],temp[20];//n个name[20]
	int i,j,flag=1;
	printf("请输入%d个名字(可以空格键隔开):\n",n);
	for(i=0;i<n;i++)
		scanf("%s",name[i]);//代表name[i][20]将name[20]作为一个整体；
	i=1;
	while(flag==1){
		flag=-1;
		for(j=0;j<n-i;j++){
			if(strcmp(name[j],name[j+1])>0){
				strcpy(temp,name[j]);
				strcpy(name[j],name[j+1]);
				strcpy(name[j+1],temp);
				flag=1;
			}
		}
		i++;
	}
	printf("顺序输出为:\n");
	for(i=0;i<n;i++)
		puts(name[i]);
}