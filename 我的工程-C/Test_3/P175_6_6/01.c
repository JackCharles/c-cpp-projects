#include<stdio.h>
#define n 6
void shanchu(int a[]){
	int m,i,j,k=0;
	for(i=0;i<n-k;i++)
		for(j=i+1;j<n-k; ){
			if(a[i]==a[j]){
				for(m=j;m<n-k;m++)
					a[j]=a[j+1];
				k++;//此处主要是消除删去相同项后，末尾多余的项数对循环的干扰（如n-k只对前有效n-k项进行操作）。
				j=i+1;//如果第i项和第i+1相等，则从i+1项开始向前移一位，并继续从i+1项开始检测，防止i+1项仍和i项相等而错过。
			}
			else    
				j++;//当i+1项和i项不相等时，在判断i+2项及其以后
		}
	for(i=0;i<=n-k;i++)
	printf("%3d",a[i]);
} 
void main(){
	int a[n],i;
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	shanchu(a);
	printf("\n");
}