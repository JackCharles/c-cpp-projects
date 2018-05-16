#include<stdio.h>
#define n 5
void paixu(int a[]);
void main(){
	int i,a[n];
	printf("ÇëÊäÈë%d¸öÊı:",n);
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	paixu(a);
	for(i=0;i<n;i++)
		printf("%4d",a[i]);
	printf("\n");	
}
void paixu(int a[]){
	int i,j,r;
	for(i=0;i<n;i++){
		if(a[i]==0){
			r=a[i];
			for(j=i;j<n-1;j++)
				a[j]=a[j+1];
			a[n-1]=r;
		}
	}
}
