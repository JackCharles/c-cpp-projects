#include<stdio.h>
#include<string.h>
#define n 5
void main(){
	char name[n][20],temp[20];//n��name[20]
	int i,j,flag=1;
	printf("������%d������(���Կո������):\n",n);
	for(i=0;i<n;i++)
		scanf("%s",name[i]);//����name[i][20]��name[20]��Ϊһ�����壻
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
	printf("˳�����Ϊ:\n");
	for(i=0;i<n;i++)
		puts(name[i]);
}