#include<stdio.h>
#define N 3
void juzhen(int a[],int *p1,int *p2){
	int i,j=0,k=0;
	int *m=a,*n=a;
	for(i=0;i<N;i++){
		j=j+*(m+i*N+i);
		k=k+*(n+i*N+N-i-1);
	}
	*p1=j;
	*p2=k;
}
void main(){
	int a[N][N],i,j,x,y;
	printf("������һ��%dX%d�ľ���:\n",N,N);
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			scanf("%d",&a[i][j]);
	juzhen(a,&x,&y);
	printf("���Խ���Ԫ��֮��Ϊ:%d\n�ζԽ���Ԫ��֮��Ϊ:%d\n",x,y);
}