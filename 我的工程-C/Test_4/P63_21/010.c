#include<stdio.h>


void paixu(int n,int a[]){
	int i,j,k,temp;

	for(i=1;i<n;i++){
		for(j=0;j<n;j++)
			if(a[i]<a[j]){
				temp=a[i];
				for(k=i;k>=j;k--)
					a[k]=a[k-1];
				a[j]=temp;
				break;
			}
	}
}


void main(){
	int i,n,a[]={-5,265,3,63,5,25,2,35,2,96,52,45,12};


	n=sizeof(a)/sizeof(int);
	//sizeof(a)指的是数组内存空间长度，不是元素个数。(a是一个指向首地址数组指针，sizeof(a)返回整个数组长度，即多少个字节)
	//可以用“数组内存空间长度”/“每个元素所占的内存空间长度”计算元素个数。
	paixu(n,a);
	for(i=0;i<n;i++)
		printf("%3d",a[i]);
	printf("\n");
}
